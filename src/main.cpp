#include <GL/gl3w.h>

#include <set>
#include <span>
#include <queue>
#include <mutex>
#include <memory>
#include <iostream>

#include <glm/glm.hpp>
#include <fmt/format.h>
#include <entt/entt.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <util/Utils.hpp>
#include <core/Window.hpp>
#include <core/Device.hpp>
#include <core/Surface.hpp>
#include <core/AppPlatform.hpp>

#include "input.hpp"
#include "camera.hpp"
#include "raytrace.hpp"
#include "transform.hpp"
#include "CraftServer.hpp"
#include "TextureAtlas.hpp"
#include "world/biome/Biome.hpp"
#include "world/biome/Biomes.hpp"
#include "world/gen/surface/SurfaceBuilder.hpp"
#include "world/gen/surface/ConfiguredSurfaceBuilders.hpp"
#include "world/gen/carver/Carvers.hpp"
#include "world/gen/carver/ConfiguredCarvers.hpp"
#include "world/gen/feature/Features.hpp"
#include "world/gen/feature/structure/Structures.hpp"
#include "world/gen/feature/structure/StructureFeatures.hpp"
#include "world/gen/feature/ConfiguredFeatures.hpp"
#include "world/gen/placement/Placements.hpp"

#include "client/world/ClientWorld.hpp"
#include "client/render/ViewFrustum.hpp"
#include "client/render/chunk/ChunkRenderDispatcher.hpp"
#include "block/BlockGraphics.hpp"

struct CameraConstants {
    glm::mat4 transform;
    glm::vec4 position;
};

struct CameraUniform {
    GLuint handle;
    void* pointer;
};

struct App {
    std::shared_ptr<Window> window{};
    std::shared_ptr<Device> device{};
    std::shared_ptr<Surface> surface{};
    std::unique_ptr<TextureAtlas> atlas{};
    std::unique_ptr<ResourcePackManager> resources{};

    float cooldown = 0.25f;
    int viewDistance = 11;
    PacketManager<App> handler{};
    std::unique_ptr<ClientWorld> world{};
    std::unique_ptr<CraftServer> server{};
    std::unique_ptr<ViewFrustum> frustum{};
    std::unique_ptr<Connection> connection{};
    std::unique_ptr<ChunkRenderDispatcher> dispatcher{};

    Camera camera{};
    Transform transform{};
    std::vector<CameraUniform> uniforms{};
    std::vector<ChunkRenderData*> chunkToRenders{};
    std::optional<RayTraceResult> rayTraceResult{};
    std::chrono::high_resolution_clock::time_point startTime{};

    GLuint opaque_pipeline;
    GLuint cutout_pipeline;
    GLuint transparent_pipeline;

    bool joined = false;

    App(const char* title, uint32_t width, uint32_t height) {
        handler.bind<SEncryptionRequestPacket, &App::processEncryptionRequest>();
        handler.bind<SEnableCompressionPacket, &App::processEnableCompression>();
        handler.bind<SLoginSuccessPacket, &App::processLoginSuccess>();
        handler.bind<SLoadChunkPacket, &App::processLoadChunk>();
        handler.bind<SUnloadChunkPacket, &App::processUnloadChunk>();
        handler.bind<SChangeBlockPacket, &App::processChangeBlock>();
        handler.bind<SSpawnPlayerPacket, &App::processSpawnPlayer>();

        /**************************************************************************************************************/

        window = std::make_unique<Window>(title, width, height);
        device = std::make_unique<Device>(*window);
        surface = std::make_unique<Surface>(*window, *device);
        resources = std::make_unique<ResourcePackManager>();

        createUniforms();

        /**************************************************************************************************************/

        resources->addResourcePack(std::make_unique<PhysFsResourcePack>("/resource_packs/vanilla"));

        atlas = std::make_unique<TextureAtlas>();
        atlas->loadMetaFile(*resources);
        atlas->loadTexture();

        BlockGraphics::mTerrainTextureAtlas = atlas.get();

        /**************************************************************************************************************/

        Materials::registerMaterials();
        BlockGraphics::initBlocks(*resources);
        Blocks::registerBlocks();
        BlockTags::registerTags();
        SurfaceBuilder::registerBuilders();
        SurfaceBuilderConfig::registerConfigs();
        ConfiguredSurfaceBuilders::configureSurfaceBuilders();
        Carvers::registerCarvers();
        ConfiguredCarvers::configureCarvers();
        Features::registerFeatures();
        Placements::registerPlacements();
        ConfiguredFeatures::configureFeatures();
        Structures::registerStructures();
        StructureFeatures::configureStructures();
        Biomes::registerBiomes();

        /**************************************************************************************************************/

        opaque_pipeline = device->createShader(
            AppPlatform::readFile("default.vert").value(),
            AppPlatform::readFile("default.frag").value()
        );
        cutout_pipeline = device->createShader(
            AppPlatform::readFile("default.vert").value(),
            AppPlatform::readFile("cutout.frag").value()
        );
        transparent_pipeline = device->createShader(
            AppPlatform::readFile("default.vert").value(),
            AppPlatform::readFile("transparent.frag").value()
        );

        /**************************************************************************************************************/

        world = std::make_unique<ClientWorld>(viewDistance);
        server = std::make_unique<CraftServer>(viewDistance);
        frustum = std::make_unique<ViewFrustum>(viewDistance);
        dispatcher = std::make_unique<ChunkRenderDispatcher>();

        connection = std::make_unique<Connection>(server->getLocalAddress());
        connection->send(CHandshakePacket{720, ProtocolType::HANDSHAKING});
        connection->send(CLoginStartPacket{});

        while (!joined) {
            handler.handlePackets(*this, *connection);
        }
    }

    void createUniforms() {
        uniforms.resize(surface->getFramesCount());
        for (auto& uniform : uniforms) {
            glCreateBuffers(1, &uniform.handle);
            glNamedBufferStorage(uniform.handle, sizeof(CameraConstants), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
            uniform.pointer = glMapNamedBufferRange(uniform.handle, 0, sizeof(CameraConstants), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        }
    }

    void update(float dt) {
        Input::get().update();

        handler.handlePackets(*this, *connection);

        const auto center = window->getWindowSize() / 2;
        const auto delta = Input::get().getMousePosition() - center;
        window->setMousePosition(center);

        transform.rotation += getRotationDelta(transform, delta, dt);
        transform.rotation.y = glm::clamp(transform.rotation.y, -90.0f, 90.0f);

        transform.position += getVelocity(Input::get(), transform, dt);

        /**************************************************************************************************************/

        if (cooldown > 0) {
            cooldown -= dt;
        }

        /**************************************************************************************************************/

        RayTraceContext rtc {
            .position = transform.position + glm::vec3(0, 1.68, 0),
            .direction = transform.forward(),
            .ignoreLiquid = true
        };

        rayTraceResult = rayTraceBlocks(*world, rtc);
        if (cooldown <= 0 && rayTraceResult.has_value()) {
            if (Input::get().isMouseButtonPressed(Input::MouseButton::Left)) {
                cooldown = 0.25f;

                connection->send(CPlayerDiggingPacket{
                    .pos = rayTraceResult->pos,
                    .dir = rayTraceResult->dir
                });
            } else if (Input::get().isMouseButtonPressed(Input::MouseButton::Right)) {
                cooldown = 0.25f;

//                connection->send(SChangeBlockPacket{
//                    .pos = rayTraceResult->pos + rayTraceResult->dir,
//                    .data = Blocks::TORCH->getDefaultState()
//                });
            }
        }
    }

    void render(const FrameInfo& frame) {
        setupCamera(frame);
        setupTerrain();
        renderTerrain();
    }

    int run() {
        using namespace std::chrono_literals;

        const auto size = window->getWindowSize();

        window->setMousePosition(size / 2);
        camera.setSize(size.x, size.y);

        startTime = std::chrono::high_resolution_clock::now();
        while (!window->shouldClose()) {
            window->pumpEvents();

            const auto time = std::chrono::high_resolution_clock::now();
            const auto dt = float(std::chrono::duration<double>(time - startTime).count());
            startTime = time;

            update(dt);

            auto frame = surface->begin({0, 0, 0, 1});

            render(frame);

            surface->present();
            window->swapBuffers();

//            fmt::print("fps: {}\n", 1.0f / dt);
        }

        return 0;
    }

private:
    void processEncryptionRequest(Connection& connection, const SEncryptionRequestPacket& packet) {
        connection.send(CEncryptionResponsePacket{});
    }
    void processEnableCompression(Connection& _, const SEnableCompressionPacket& packet) {}

    void processLoginSuccess(Connection& _, const SLoginSuccessPacket& packet) {}

    void processLoadChunk(Connection& _, const SLoadChunkPacket& packet) {
        world->loadChunk(packet.x, packet.z, packet.chunk);

        for (int x = packet.x - 1; x <= packet.x + 1; ++x) {
            for (int z = packet.z - 1; z <= packet.z + 1; ++z) {
                frustum->chunks[world->provider->chunkArray.getIndex(x, z)].needRender = true;
            }
        }
    }

    void processUnloadChunk(Connection& _, const SUnloadChunkPacket& packet) {
        world->unloadChunk(packet.x, packet.z);
    }

    void processChangeBlock(Connection& _, const SChangeBlockPacket& packet) {
        const auto pos = packet.pos;

        for (int x = (pos.x - 1) >> 4; x <= (pos.x + 1) >> 4; x++) {
            for (int z = (pos.z - 1) >> 4; z <= (pos.z + 1) >> 4; z++) {
                frustum->chunks[world->provider->chunkArray.getIndex(x, z)].needRender = true;
            }
        }
    }

    void processSpawnPlayer(Connection& _, const SSpawnPlayerPacket& packet) {
        joined = true;

        const auto pos = glm::ivec3(glm::floor(packet.pos));
        world->provider->chunkArray.setCenter(pos.x >> 4, pos.z >> 4);

        transform = {
            .position = packet.pos,
            .rotation = {0, 10}
        };
    }

private:
    void setupCamera(const FrameInfo& frame) {
        const auto projection_matrix = camera.getProjection();
        const auto transform_matrix = transform.getTransformMatrix({0.0f, 1.68f, 0.0f});
        const auto camera_matrix = projection_matrix * transform_matrix;

        CameraConstants constants {
            .transform = camera_matrix,
            .position = glm::vec4(transform.position, 0.0f)
        };

        std::memcpy(uniforms[frame.index].pointer, &constants, sizeof(CameraConstants));
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms[frame.index].handle);

        frustum->ExtractPlanes(glm::transpose(camera_matrix), true);
    }

    void setupTerrain() {
        chunkToRenders.clear();

        const auto pos = glm::ivec3(glm::floor(transform.position));

        const auto chunk_x = pos.x >> 4;
        const auto chunk_z = pos.z >> 4;

        connection->send(PositionPacket{
            .pos = transform.position
        });

        world->provider->chunkArray.setCenter(chunk_x, chunk_z);

        for (int x = chunk_x - viewDistance; x <= chunk_x + viewDistance; ++x) {
            for (int z = chunk_z - viewDistance; z <= chunk_z + viewDistance; ++z) {
                const auto from = glm::vec3{x << 4, 0, z << 4};
                const auto to = from + glm::vec3{16, 256, 16};

                if (frustum->TestAABB(from, to)) {
                    const auto i = static_cast<size_t>(world->provider->chunkArray.getIndex(x, z));

                    if (std::exchange(frustum->chunks[i].needRender, false)) {
                        const auto dx = chunk_x - x;
                        const auto dz = chunk_z - z;
                        const auto immediate = (dx * dx + dz * dz) <= 1;

                        dispatcher->rebuildChunk(*world, frustum->chunks[i], x, z, immediate);
                    }

                    chunkToRenders.emplace_back(&frustum->chunks[i]);
                }
            }
        }
    }

    void renderTerrain() {
        dispatcher->runChunkUploads();

        glBindTexture(GL_TEXTURE_2D, atlas->texture);
        glActiveTexture(GL_TEXTURE0);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);
        glDisable(GL_BLEND);

        glUseProgram(opaque_pipeline);
        renderLayer(RenderLayer::Opaque);

        glUseProgram(cutout_pipeline);
        renderLayer(RenderLayer::Cutout);

        glEnable(GL_BLEND);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

        glUseProgram(transparent_pipeline);
        renderLayer(RenderLayer::Transparent);
    }

    void renderLayer(RenderLayer layer) {
        for (auto chunk : chunkToRenders) {
            const auto [offset, count] = chunk->layers[static_cast<size_t>(layer)];

            if (count != 0) {
                glBindVertexArray(chunk->mesh.vao);

                glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, static_cast<std::byte*>(nullptr) + offset * sizeof(int32_t));
            }
        }
    }

    static auto getVelocity(Input& input, const Transform& transform, float dt) -> glm::vec3 {
        const auto speed = input.isKeyPressed(Input::Key::Shift) ? 100.0f : 10.0f;
        const auto states = std::array{
            input.isKeyPressed(Input::Key::Up) ? 1 : 0,
            input.isKeyPressed(Input::Key::Left) ? 1 : 0,
            input.isKeyPressed(Input::Key::Down) ? 1 : 0,
            input.isKeyPressed(Input::Key::Right) ? 1 : 0
        };
        const auto direction = glm::vec3(states[3] - states[1], 0, states[2] - states[0]);
        return direction * glm::mat3(transform.getRotationMatrix()) * speed * dt;
    }

    static auto getRotationDelta(const Transform& transform, glm::ivec2 delta, float dt) -> glm::vec2 {
        if (delta.x != 0 || delta.y != 0) {
            const auto d4 = 0.5f * 0.6F + 0.2F;
            const auto d5 = d4 * d4 * d4 * 8.0f;
            return glm::vec2(delta) * d5 * dt * 9.0f;
        }
        return {};
    }
};

struct AppServer {
    int viewDistance = 11;
    std::unique_ptr<ResourcePackManager> resources{};

    AppServer() {
        resources = std::make_unique<ResourcePackManager>();
        resources->addResourcePack(std::make_unique<PhysFsResourcePack>("/resource_packs/vanilla"));

        /**************************************************************************************************************/

        Materials::registerMaterials();
//        BlockGraphics::initBlocks(*resources);
        Blocks::registerBlocks();
        BlockTags::registerTags();
        SurfaceBuilder::registerBuilders();
        SurfaceBuilderConfig::registerConfigs();
        ConfiguredSurfaceBuilders::configureSurfaceBuilders();
        Carvers::registerCarvers();
        ConfiguredCarvers::configureCarvers();
        Features::registerFeatures();
        Placements::registerPlacements();
        ConfiguredFeatures::configureFeatures();
        Structures::registerStructures();
        StructureFeatures::configureStructures();
        Biomes::registerBiomes();

        /**************************************************************************************************************/
    }

    int run() {
        bool running = true;
        std::string cmd{};
        while (running) {
            fmt::print("Run dedicated server!\n");
            CraftServer server{viewDistance};
            while (true) {
                if (std::getline(std::cin, cmd)) {
                    if (cmd == "restart") {
                        break;
                    } else if (cmd == "exit") {
                        running = false;
                        break;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            fmt::print("Stop dedicated server!\n");
        }
        return 0;
    }
};

int main() {
    if constexpr (Utils::is_server()) {
        AppServer app{};
        return app.run();
    } else {
        App app{"Bedcraft", 800, 600};
        return app.run();
    }
}


//auto parse_command(std::string_view cmd, size_t& offset) -> std::optional<std::string> {
//    if (offset == std::string_view::npos) {
//        return std::nullopt;
//    }
//    const auto off = std::exchange(offset, cmd.find(' ', offset));
//    return offset != std::string_view::npos
//            ? std::string(cmd.substr(off, offset - off))
//            : std::string(cmd.substr(off));
//}