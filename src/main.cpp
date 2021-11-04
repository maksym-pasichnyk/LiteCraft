#include <GL/gl3w.h>

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

#include "CraftServer.hpp"
#include "TextureAtlas.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "raytrace.hpp"
#include "transform.hpp"

#include <block/Blocks.hpp>
#include <block/States.hpp>
#include <block/BlockGraphics.hpp>

#include <world/biome/Biome.hpp>
#include <world/biome/Biomes.hpp>
#include <world/chunk/ChunkStatus.hpp>
#include <world/gen/pools/JigsawPools.hpp>
#include <world/gen/surface/SurfaceBuilders.hpp>
#include <world/gen/feature/processor/ProcessorLists.hpp>

#include <client/render/ModelComponent.hpp>
#include <client/render/ViewFrustum.hpp>
#include <client/render/chunk/ChunkRenderDispatcher.hpp>
#include <client/render/model/Models.hpp>
#include <client/world/ClientWorld.hpp>

#include <configs.hpp>

struct CameraConstants {
    glm::mat4 transform;
    glm::vec4 position;
};

struct CameraUniform {
    GLuint handle;
    void* pointer;
};

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

struct VelocityComponent {
    glm::vec3 velocity;
};
struct PlayerComponent {
    int controller;
    float cooldown;
    Transform camera;
};
struct GravityComponent {};
struct CollisionComponent {
    std::vector<AABB> boxes;
};

struct App {
    entt::registry ecs;

    std::shared_ptr<Window> window{};
    std::shared_ptr<Device> device{};
    std::shared_ptr<Surface> surface{};
    std::unique_ptr<TextureAtlas> atlas{};
    std::unique_ptr<ResourceManager> resources{};

    int renderDistance = -1;
    PacketManager<App> handler{};
    std::unique_ptr<ClientWorld> world{};
    std::unique_ptr<CraftServer> server{};
    std::unique_ptr<ViewFrustum> frustum{};
    std::unique_ptr<Connection> connection{};
    std::unique_ptr<ChunkRenderDispatcher> dispatcher{};

    Camera camera{};
    std::vector<CameraUniform> uniforms{};
    std::vector<ChunkRenderData*> chunkToRenders{};
//    std::optional<RayTraceResult> rayTraceResult{};
    std::chrono::high_resolution_clock::time_point startTime{};

    GLuint opaque_pipeline;
    GLuint cutout_pipeline;
    GLuint transparent_pipeline;

    GLuint entity_pipeline;

    App(const char* title, uint32_t width, uint32_t height) {
        handler.bind<SEncryptionRequestPacket, &App::processEncryptionRequest>();
        handler.bind<SEnableCompressionPacket, &App::processEnableCompression>();
        handler.bind<SLoginSuccessPacket, &App::processLoginSuccess>();
        handler.bind<SLoadChunkPacket, &App::processLoadChunk>();
        handler.bind<SUnloadChunkPacket, &App::processUnloadChunk>();
        handler.bind<SChangeBlockPacket, &App::processChangeBlock>();
        handler.bind<SSpawnPlayerPacket, &App::processSpawnPlayer>();
        handler.bind<SPlayerPositionLookPacket, &App::processPlayerPositionLook>();
        handler.bind<SJoinGamePacket, &App::processJoinGame>();

        /**************************************************************************************************************/

        window = std::make_unique<Window>(title, width, height);
        device = std::make_unique<Device>(*window);
        surface = std::make_unique<Surface>(*window, *device);
        resources = std::make_unique<ResourceManager>();

        createUniforms();

        /**************************************************************************************************************/

        resources->emplace(std::make_unique<PhysFsResourcePack>("/resource_packs/vanilla"));
        resources->emplace(std::make_unique<FolderResourcePack>(std::filesystem::current_path()));

        atlas = std::make_unique<TextureAtlas>();
        atlas->loadMetaFile(*resources);
        atlas->loadTexture();

        BlockGraphics::mTerrainTextureAtlas = atlas.get();

        /**************************************************************************************************************/
        ChunkStatus::init();

        Materials::init();
        BlockGraphics::init(*resources);

        Blocks::init();
        States::init();
        BlockTags::init();

        Carvers::init();
        Features::init();
        Placements::init();
        Structures::init();
        SurfaceBuilders::init();

        ConfiguredCarvers::init(*resources);
        ConfiguredFeatures::init(*resources);
        ProcessorLists::init();
        JigsawPools::init(*resources);
        StructureFeatures::init(*resources);
        ConfiguredSurfaceBuilders::init(*resources);

        Biomes::init(*resources);
        Models::init(*resources);

        /**************************************************************************************************************/

        entity_pipeline = device->createShader(
            resources->load("shaders/entity.vert").value(),
            resources->load("shaders/entity.frag").value()
        );
        opaque_pipeline = device->createShader(
            resources->load("shaders/default.vert").value(),
            resources->load("shaders/default.frag").value()
        );
        cutout_pipeline = device->createShader(
            resources->load("shaders/default.vert").value(),
            resources->load("shaders/cutout.frag").value()
        );
        transparent_pipeline = device->createShader(
            resources->load("shaders/default.vert").value(),
            resources->load("shaders/transparent.frag").value()
        );

        /**************************************************************************************************************/

        renderDistance = 12;
        const auto viewDistance = std::max(2, renderDistance - 1);
        world = std::make_unique<ClientWorld>(viewDistance);
        server = std::make_unique<CraftServer>(viewDistance + 1, *resources);
        frustum = std::make_unique<ViewFrustum>(renderDistance);
        dispatcher = std::make_unique<ChunkRenderDispatcher>();

        connection = std::make_unique<Connection>(entt::null, server->getLocalAddress());
        connection->send(CHandshakePacket{720, ProtocolType::HANDSHAKING});
        connection->send(CLoginStartPacket{});

        const auto stride = renderDistance * 2 + 1;
        while (world->provider->chunkArray.getLoaded() != stride * stride) {
            handler.handlePackets(*this, *connection);
        }

        fmt::print("server: {}\n", server->getLocalAddress());
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
        auto delta = Input::get().getMousePosition() - center;
        window->setMousePosition(center);

        /**************************************************************************************************************/

        ecs.view<PlayerComponent, Transform, VelocityComponent>().each([dt, delta](auto& p, auto& tr, auto& vel) {
            p.camera.rotation -= getRotationDelta(p.camera, delta, dt);
            p.camera.rotation.y = glm::clamp(p.camera.rotation.y, -90.0f, 90.0f);

            tr.rotation.x = p.camera.rotation.x;

            const auto speed = Input::get().isKeyPressed(Input::Key::Shift) ? 50.0f : 5.0f;
            const auto states = std::array{
                Input::get().isKeyPressed(Input::Key::Up) ? -1 : 0,
                Input::get().isKeyPressed(Input::Key::Left) ? -1 : 0,
                Input::get().isKeyPressed(Input::Key::Down) ? 1 : 0,
                Input::get().isKeyPressed(Input::Key::Right) ? 1 : 0
            };
            const auto direction = glm::vec4(states[1] + states[3], 0, states[0] + states[2], 1);

            vel.velocity.x = 0;
            vel.velocity.z = 0;
            if (Input::get().isKeyPressed(Input::Key::Up)) {
                vel.velocity += tr.forward() * speed * dt;
            }
            if (Input::get().isKeyPressed(Input::Key::Down)) {
                vel.velocity -= tr.forward() * speed * dt;
            }
            if (Input::get().isKeyPressed(Input::Key::Left)) {
                vel.velocity -= tr.right() * speed * dt;
            }
            if (Input::get().isKeyPressed(Input::Key::Right)) {
                vel.velocity += tr.right() * speed * dt;
            }

            if (Input::get().isKeyDown(Input::Key::Jump)) {
                vel.velocity.y += 5.0f * dt;
            }
        });
        ecs.view<VelocityComponent, GravityComponent>().each([dt](auto& vel) {
            vel.velocity.y += -9.8f * dt * dt;
        });
        ecs.view<Transform, VelocityComponent, CollisionComponent>().each([this](auto& tr, auto& vel, const auto& col) {
            vel.velocity = resolve_collision(*world, tr.position, vel.velocity);
        });
        ecs.view<PlayerComponent, Transform, VelocityComponent>().each([](auto& p, auto& tr, auto& vel) {
            tr.position += vel.velocity;
            vel.velocity.x *= 0.5f;
            vel.velocity.z *= 0.5f;

            p.camera.position = tr.transformPoint(glm::vec3{0.0f, 1.68f, 0.0f});
        });
        ecs.view<PlayerComponent>().each([this, dt](auto& p) {
            if (p.cooldown > 0) {
                p.cooldown -= dt;
                return;
            }
            RayTraceContext ctx {
                .position = p.camera.position,
                .direction = p.camera.forward(),
                .ignoreLiquid = true
            };

            if (const auto result = rayTraceBlocks(*world, ctx)) {
                if (Input::get().isMouseButtonPressed(Input::MouseButton::Left)) {
                    p.cooldown = 0.25f;

                    connection->send(CPlayerDiggingPacket{
                        .pos = result->pos,
                        .dir = result->dir
                    });
                } else if (Input::get().isMouseButtonPressed(Input::MouseButton::Right)) {
                    p.cooldown = 0.25f;

//                    connection->send(SChangeBlockPacket{
//                        .pos = result->pos + result->dir,
//                        .block = States::TORCH
//                    });
                }
            }
        });

        /**************************************************************************************************************/
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
            const auto dt = static_cast<float>(std::chrono::duration<double>(time - startTime).count());
            startTime = time;

            update(dt);

            auto frame = surface->begin({0, 0, 0, 1});

            render(frame);

            surface->present();
            window->swapBuffers();
        }

        return 0;
    }

private:
    /**************************************************************************************************************/

    static auto check_collide(IBlockReader auto& blocks, float x, float y, float z) -> bool {
        const auto ix = glm::floor(x);
        const auto iy = glm::floor(y);
        const auto iz = glm::floor(z);
        return !blocks.getData(ix, iy, iz).isAir();
    }

    static auto check_down_velocity(IBlockReader auto& blocks, glm::vec3 position, float velocity, float half_collider_width = 0.5f) -> float {
        if (check_collide(blocks, position.x - half_collider_width, position.y + velocity, position.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, position.x + half_collider_width, position.y + velocity, position.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, position.x + half_collider_width, position.y + velocity, position.z + half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, position.x - half_collider_width, position.y + velocity, position.z + half_collider_width)) {
            return 0;
        }
        return velocity;
    }

    static auto check_up_velocity(IBlockReader auto& blocks, glm::vec3 entity_pos, float vel, float half_collider_width = 0.5f, float collider_height = 1.8f) -> float {
        if (check_collide(blocks, entity_pos.x - half_collider_width, entity_pos.y + collider_height + vel, entity_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, entity_pos.x + half_collider_width, entity_pos.y + collider_height + vel, entity_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, entity_pos.x + half_collider_width, entity_pos.y + collider_height + vel, entity_pos.z + half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, entity_pos.x - half_collider_width, entity_pos.y + collider_height + vel, entity_pos.z + half_collider_width)) {
            return 0;
        }
        return vel;
    }

    static auto check_front_velocity(IBlockReader auto& blocks, const glm::vec3& position, glm::vec3 velocity, float half_collider_width = 0.5f, float collider_height = 1.8f) -> float {
        const auto new_pos = position + velocity;
        if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y, new_pos.z + half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y, new_pos.z + half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y + collider_height, new_pos.z + half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y + collider_height, new_pos.z + half_collider_width)) {
            return 0;
        }
        return velocity.z;
    }

    static auto check_back_velocity(IBlockReader auto& blocks, glm::vec3 position, glm::vec3 velocity, float half_collider_width = 0.5f, float collider_height = 1.8f) -> float {
        const auto new_pos = position + velocity;
        if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y, new_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y, new_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y + collider_height, new_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y + collider_height, new_pos.z - half_collider_width)) {
            return 0;
        }
        return velocity.z;
    }

    static auto check_left_velocity(IBlockReader auto& blocks, glm::vec3 position, glm::vec3 velocity, float half_collider_width = 0.5f, float collider_height = 1.8f) -> float {
        const auto new_pos = position + velocity;
        if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y, new_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y, new_pos.z + half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y + collider_height, new_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y + collider_height, new_pos.z + half_collider_width)) {
            return 0;
        }
        return velocity.x;
    }

    static auto check_right_velocity(IBlockReader auto& blocks, glm::vec3 position, glm::vec3 velocity, float half_collider_width = 0.5f, float collider_height = 1.8f) -> float {
        const auto new_pos = position + velocity;
        if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y, new_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y, new_pos.z + half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y + collider_height, new_pos.z - half_collider_width)) {
            return 0;
        }
        if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y + collider_height, new_pos.z + half_collider_width)) {
            return 0;
        }
        return velocity.x;
    }

    static auto resolve_collision(IBlockReader auto& blocks, const glm::vec3& pos, const glm::vec3& vel) -> glm::vec3 {
        auto velocity = vel;
        if (velocity.y > 0) {
            velocity.y = check_up_velocity(blocks, pos, velocity.y);
        } else if (velocity.y < 0) {
            velocity.y = check_down_velocity(blocks, pos, velocity.y);
        }
        if (velocity.z > 0) {
            velocity.z = check_front_velocity(blocks, pos, velocity);
        } else if (velocity.z < 0) {
            velocity.z = check_back_velocity(blocks, pos, velocity);
        }
        if (velocity.x > 0) {
            velocity.x = check_right_velocity(blocks, pos, velocity);
        } else if (velocity.x < 0) {
            velocity.x = check_left_velocity(blocks, pos, velocity);
        }
        return velocity;
    }

    /**************************************************************************************************************/

    void processEncryptionRequest(Connection& connection, const SEncryptionRequestPacket& packet) {
        connection.send(CEncryptionResponsePacket{});
    }
    void processEnableCompression(Connection& _, const SEnableCompressionPacket& packet) {}

    void processLoginSuccess(Connection& _, const SLoginSuccessPacket& packet) {}

    void processLoadChunk(Connection& _, const SLoadChunkPacket& packet) {
        world->loadChunk(packet.x, packet.z, packet.chunk);

        for (int x = packet.x - 1; x <= packet.x + 1; ++x) {
            for (int z = packet.z - 1; z <= packet.z + 1; ++z) {
                const auto ix = ChunkArray::floorMod(x, frustum->stride);
                const auto iz = ChunkArray::floorMod(z, frustum->stride);
                const auto i = static_cast<size_t>(ix + iz * frustum->stride);

                frustum->chunks[i].needRender = true;
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
                const auto ix = ChunkArray::floorMod(x, frustum->stride);
                const auto iz = ChunkArray::floorMod(z, frustum->stride);
                const auto i = static_cast<size_t>(ix + iz * frustum->stride);

                frustum->chunks[i].needRender = true;
            }
        }
    }

    void processJoinGame(Connection& _, const SJoinGamePacket& packet) {
        if (connection->player == entt::null) {
            connection->player = ecs.create();

            ecs.emplace<Transform>(connection->player, glm::vec3{}, glm::vec2{});
//            ecs.emplace<ModelComponent>(connection->player, *Models::models.get("geometry.humanoid").value());
            ecs.emplace<PlayerComponent>(connection->player, 0, 0.0f, Transform{});
            ecs.emplace<GravityComponent>(connection->player);
            ecs.emplace<VelocityComponent>(connection->player);
            ecs.emplace<CollisionComponent>(connection->player);
        }
    }

    void processPlayerPositionLook(Connection& _, const SPlayerPositionLookPacket& packet) {
        ecs.replace<Transform>(connection->player, packet.pos, packet.rot);
    }

    void processSpawnPlayer(Connection& _, const SSpawnPlayerPacket& packet) {
        auto player = ecs.create();
        ecs.emplace<Transform>(player, packet.pos, glm::vec2{});
        ecs.emplace<ModelComponent>(player, *Models::models.get("geometry.humanoid").value());
//        ecs.emplace<GravityComponent>(player);
        ecs.emplace<VelocityComponent>(player);
//        ecs.emplace<CollisionComponent>(player);
    }

private:
    void setupCamera(const FrameInfo& frame) {
        auto& transform = ecs.get<PlayerComponent>(connection->player).camera;

        const auto projection = camera.getProjection();
        const auto view = glm::inverse(transform.localToWorldMatrix());
        const auto camera_matrix = projection * view;

        const auto constants = CameraConstants{
            .transform = camera_matrix,
            .position = glm::vec4(transform.position, 0.0f)
        };

        std::memcpy(uniforms[frame.index].pointer, &constants, sizeof(CameraConstants));
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniforms[frame.index].handle);

        frustum->ExtractPlanes(glm::transpose(camera_matrix), true);
    }

    void setupTerrain() {
        auto& transform = ecs.get<Transform>(connection->player);

        chunkToRenders.clear();

        const auto pos = glm::ivec3(glm::floor(transform.position));

        const auto chunk_x = pos.x >> 4;
        const auto chunk_z = pos.z >> 4;

        connection->send(PositionPacket{
            .pos = transform.position
        });

        world->provider->chunkArray.setCenter(chunk_x, chunk_z);

        for (int x = chunk_x - renderDistance; x <= chunk_x + renderDistance; ++x) {
            for (int z = chunk_z - renderDistance; z <= chunk_z + renderDistance; ++z) {
                const auto from = glm::vec3{x << 4, 0, z << 4};
                const auto to = from + glm::vec3{16, 256, 16};

//                if (frustum->TestAABB(from, to)) {
                    const auto ix = ChunkArray::floorMod(x, frustum->stride);
                    const auto iz = ChunkArray::floorMod(z, frustum->stride);
                    const auto i = static_cast<size_t>(ix + iz * frustum->stride);

                    if (std::exchange(frustum->chunks[i].needRender, false)) {
                        const auto dx = chunk_x - x;
                        const auto dz = chunk_z - z;
                        const auto immediate = (dx * dx + dz * dz) <= 1;

                        dispatcher->rebuildChunk(*world, frustum->chunks[i], x, z, immediate);
                    }

                    chunkToRenders.emplace_back(&frustum->chunks[i]);
//                }
            }
        }

//        fmt::print("Chunks[C] W: {}, {}\n",
//            world->provider->chunkArray.chunks.size(),
//            world->provider->chunkArray.getLoaded()
//        );
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

        glDisable(GL_BLEND);
        glUseProgram(entity_pipeline);

        ecs.view<Transform, ModelComponent>().each([](const auto& tr, const auto& mr) {
            // todo: animation
            const auto m = tr.localToWorldMatrix();

            glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(m));
            glBindVertexArray(mr.mesh->vao);
            glDrawElements(GL_TRIANGLES, mr.mesh->index_count, GL_UNSIGNED_INT, nullptr);
        });
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
    int renderDistance = 11;
    std::unique_ptr<ResourceManager> resources{};

    AppServer() {
        resources = std::make_unique<ResourceManager>();
        resources->emplace(std::make_unique<PhysFsResourcePack>("/resource_packs/vanilla"));

        /**************************************************************************************************************/

        Materials::init();
//        BlockGraphics::init(*resources);
        Blocks::init();
        BlockTags::init();
        SurfaceBuilders::init();
        ConfiguredSurfaceBuilders::init(*resources);
        Carvers::init();
        ConfiguredCarvers::init(*resources);
        Features::init();
        Placements::init();
        ConfiguredFeatures::init(*resources);
        Structures::init();
        StructureFeatures::init(*resources);
        Biomes::init(*resources);

        /**************************************************************************************************************/
    }

    int run() {
        bool running = true;
        std::string cmd{};
        while (running) {
            fmt::print("Run dedicated server!\n");
            CraftServer server{renderDistance, *resources};
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