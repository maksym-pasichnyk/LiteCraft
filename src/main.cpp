#include <GL/gl3w.h>

#include <set>
#include <span>
#include <queue>
#include <mutex>
#include <random>
#include <memory>

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <fmt/format.h>

#include <core/Window.hpp>
#include <core/Device.hpp>
#include <core/Surface.hpp>
#include <core/AppPlatform.hpp>

#include "input.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "raytrace.hpp"
#include "transform.hpp"
#include "CraftServer.hpp"
#include "TextureAtlas.hpp"
#include "PacketManager.hpp"
#include "NetworkManager.hpp"
#include "world/chunk/Chunk.hpp"
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
#include "client/render/model/ModelFormat.hpp"
#include "client/render/chunk/ChunkRenderDispatcher.hpp"

#include "block/Block.hpp"
#include "block/Blocks.hpp"
#include "block/BlockReader.hpp"
#include "block/BlockGraphics.hpp"
#include "block/material/Materials.hpp"

struct CameraConstants {
    glm::mat4 transform;
    glm::vec4 position;
};

struct CameraUniform {
    GLuint handle;
    void* pointer;
};

struct Transform {
    glm::vec2 rotation{};
    glm::vec3 position{};

    auto getRotationMatrix() const -> glm::mat4 {
        return getRotationMatrix(rotation);
    }

    auto getTransformMatrix() const -> glm::mat4 {
        return glm::translate(getRotationMatrix(), -position);
    }

    auto getTransformMatrix(glm::vec3 offset) const -> glm::mat4 {
        return glm::translate(getRotationMatrix(), -(position + offset));
    }

    auto up() const -> glm::vec3 {
        return glm::vec3(0, 1, 0) * glm::mat3(getRotationMatrix());
    }

    auto forward() const -> glm::vec3 {
        return glm::vec3(0, 0, -1) * glm::mat3(getRotationMatrix());
    }

    auto right() const -> glm::vec3 {
        return glm::vec3(1, 0, 0) * glm::mat3(getRotationMatrix());
    }

    static auto getRotationMatrix(const glm::vec2& rotation) -> glm::mat4 {
        const auto ry = glm::radians(rotation.x);
        const auto rp = glm::radians(rotation.y);

        const auto [sy, cy] = std::pair{ glm::sin(ry), glm::cos(ry) };
        const auto [sp, cp] = std::pair{ glm::sin(rp), glm::cos(rp) };

        return {
            cy, sp * sy, -cp * sy, 0,
            0, cp, sp, 0,
            sy, -sp * cy, cp * cy, 0,
            0, 0, 0, 1
        };
    }
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
    std::unique_ptr<NetworkConnection> connection{};
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

    App(const char* title, uint32_t width, uint32_t height) {
        handler.bind<SLoadChunkPacket, &App::processLoadChunk>();
        handler.bind<SUnloadChunkPacket, &App::processUnloadChunk>();
        handler.bind<SChangeBlockPacket, &App::processChangeBlock>();

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

        transform = {
            .rotation = {0, 10},
            .position = {0, 80, 10}
        };

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
        dispatcher = std::make_unique<ChunkRenderDispatcher>(world.get());

        connection = std::make_unique<NetworkConnection>(server->getLocalAddress());
        connection->send(SSpawnPlayerPacket{
            .pos = transform.position
        });

        const auto pos = glm::ivec3(glm::floor(transform.position));
        world->provider->chunkArray.setCenter(pos.x >> 4, pos.z >> 4);
    }

    void createUniforms() {
        uniforms.resize(surface->getFramesCount());
        for (auto& uniform : uniforms) {
            glCreateBuffers(1, &uniform.handle);
            glNamedBufferStorage(uniform.handle, sizeof(CameraConstants), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
            uniform.pointer = glMapNamedBufferRange(uniform.handle, 0, sizeof(CameraConstants), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        }
    }

    void processLoadChunk(NetworkConnection& _, const SLoadChunkPacket& packet) {
        world->loadChunk(packet.x, packet.z, packet.chunk);

        for (int x = packet.x - 1; x <= packet.x + 1; ++x) {
            for (int z = packet.z - 1; z <= packet.z + 1; ++z) {
                frustum->chunks[world->provider->chunkArray.getIndex(x, z)].needRender = true;
            }
        }
    }

    void processUnloadChunk(NetworkConnection& _, const SUnloadChunkPacket& packet) {
        world->unloadChunk(packet.x, packet.z);
    }

    void processChangeBlock(NetworkConnection& _, const SChangeBlockPacket& packet) {
        const auto pos = packet.pos;

        for (int x = (pos.x - 1) >> 4; x <= (pos.x + 1) >> 4; x++) {
            for (int z = (pos.z - 1) >> 4; z <= (pos.z + 1) >> 4; z++) {
                frustum->chunks[world->provider->chunkArray.getIndex(x, z)].needRender = true;
            }
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

                connection->send(SChangeBlockPacket{
                    .pos = rayTraceResult->pos + rayTraceResult->dir,
                    .data = Blocks::TORCH->getDefaultState()
                });
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

                        dispatcher->rebuildChunk(frustum->chunks[i], x, z, immediate);
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

int main() {
    App app{"Bedcraft", 800, 600};
    return app.run();
}