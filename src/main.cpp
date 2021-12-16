#include <span>
#include <queue>
#include <mutex>
#include <memory>
#include <iostream>

#include <glm/glm.hpp>
#include <entt/entt.hpp>
#include <spdlog/spdlog.h>
#include <glm/gtx/euler_angles.hpp>

#include <util/Utils.hpp>
#include <core/AppPlatform.hpp>

#include "CraftServer.hpp"
#include "TextureAtlas.hpp"
#include "camera.hpp"
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

#include <Blaze.hpp>
#include <Display.hpp>
#include <Input.hpp>
#include <Material.hpp>
#include <Time.hpp>
#include <imgui.h>

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};
struct CameraConstants {
    glm::mat4 transform;
    glm::vec4 position;
};
struct PlayerComponent {
    int controller;
    float cooldown;
    Transform camera;
};
struct GravityComponent {};
struct VelocityComponent {
    glm::vec3 velocity;
};
struct CollisionComponent {
    std::vector<AABB> boxes;
};

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

static auto getRotationDelta(const Transform& transform, glm::ivec2 delta, float dt) -> glm::vec2 {
    if (delta.x != 0 || delta.y != 0) {
        const auto d4 = 0.5f * 0.6F + 0.2F;
        const auto d5 = d4 * d4 * d4 * 8.0f;
        return glm::vec2(delta) * d5 * dt * 9.0f;
    }
    return {};
}

struct WorldRenderer {
    Material entityMaterial;
    Material opaqueMaterial;
    Material cutoutMaterial;
    Material transparentMaterial;

    ChunkRenderDispatcher dispatcher{};
    std::vector<GraphicsBuffer> uniforms{};
    std::vector<ChunkRenderData*> chunkToRenders{};

    WorldRenderer() {
        _createUniforms();

//        entityMaterial = Material::LoadFromResources("craft:materials/entity.material");
        opaqueMaterial = Material::LoadFromResources("craft:materials/opaque.material");
        cutoutMaterial = Material::LoadFromResources("craft:materials/cutout.material");
        transparentMaterial = Material::LoadFromResources("craft:materials/transparent.material");

        opaqueMaterial.SetTexture(1, BlockGraphics::mTerrainTextureAtlas->texture);
        opaqueMaterial.SetConstantBuffer(0, uniforms[0]);

        cutoutMaterial.SetTexture(1, BlockGraphics::mTerrainTextureAtlas->texture);
        cutoutMaterial.SetConstantBuffer(0, uniforms[0]);

        transparentMaterial.SetTexture(1, BlockGraphics::mTerrainTextureAtlas->texture);
        transparentMaterial.SetConstantBuffer(0, uniforms[0]);
    }

    void drawTerrain(CommandBuffer cmd) {
        dispatcher.runChunkUploads();

        _drawChunks(cmd, opaqueMaterial, RenderLayer::Opaque);
        _drawChunks(cmd, cutoutMaterial, RenderLayer::Cutout);
        _drawChunks(cmd, transparentMaterial, RenderLayer::Transparent);
    }

private:
    void _drawChunks(CommandBuffer cmd, const Material& material, RenderLayer layer) {
        for (auto chunk : chunkToRenders) {
            if (chunk->mesh.getIndexCount() == 0) {
                continue;
            }
            cmd.drawMesh(chunk->mesh, material, static_cast<int>(layer));
        }
    }

    void _createUniforms() {
        // todo: move to Blaze
        uniforms.emplace_back(GraphicsBuffer::Target::Constant, sizeof(CameraConstants));
    }
};

struct Game : Blaze::Application {
    const int renderDistance = 3;

    Camera camera{};
    entt::registry ecs{};
    PacketManager<Game> handler{};
    std::unique_ptr<ClientWorld> world{};
    std::unique_ptr<CraftServer> server{};
    std::unique_ptr<ViewFrustum> frustum{};
    std::unique_ptr<Connection> connection{};
    std::unique_ptr<WorldRenderer> renderer{};
    std::unique_ptr<ResourceManager> resources{};
    std::optional<RayTraceResult> rayTraceResult{};

    Game() {
        handler.bind<SEncryptionRequestPacket, &Game::processEncryptionRequest>();
        handler.bind<SEnableCompressionPacket, &Game::processEnableCompression>();
        handler.bind<SLoginSuccessPacket, &Game::processLoginSuccess>();
        handler.bind<SLoadChunkPacket, &Game::processLoadChunk>();
        handler.bind<SUnloadChunkPacket, &Game::processUnloadChunk>();
        handler.bind<SChangeBlockPacket, &Game::processChangeBlock>();
        handler.bind<SSpawnPlayerPacket, &Game::processSpawnPlayer>();
        handler.bind<SPlayerPositionLookPacket, &Game::processPlayerPositionLook>();
        handler.bind<SJoinGamePacket, &Game::processJoinGame>();
    }

    void Init() override {
        extern auto GetDisplay() -> Display&;
        camera.setSize(GetDisplay().getSize());

        resources = std::make_unique<ResourceManager>();
        resources->emplace(std::make_unique<PhysFsResourcePack>("/resource_packs/vanilla"));
        resources->emplace(std::make_unique<FolderResourcePack>(std::filesystem::current_path()));

        loadResources();
        startLocalServer();
    }
    void Destroy() override {
        renderer.reset();
    }
    void Update() override {
        handler.handlePackets(*this, *connection);

        /**************************************************************************************************************/
        const auto dt = Time::getDeltaTime();
        const auto delta = Input::getMouseDelta();
        ecs.view<PlayerComponent, Transform, VelocityComponent>().each([dt, delta](auto& p, auto& tr, auto& vel) {
            p.camera.rotation -= getRotationDelta(p.camera, delta, dt);
            p.camera.rotation.y = glm::clamp(p.camera.rotation.y, -90.0f, 90.0f);

            tr.rotation.x = p.camera.rotation.x;

            const auto speed = Input::isKeyPressed(KeyCode::eLeftShift) ? 50.0f : 5.0f;
            const auto states = std::array{
                Input::isKeyPressed(KeyCode::eUpArrow) ? -1 : 0,
                Input::isKeyPressed(KeyCode::eLeftArrow) ? -1 : 0,
                Input::isKeyPressed(KeyCode::eDownArrow) ? 1 : 0,
                Input::isKeyPressed(KeyCode::eRightArrow) ? 1 : 0
            };
            const auto direction = glm::ivec4(states[1] + states[3], 0, states[0] + states[2], 1);

            vel.velocity = {};
            if (direction.x != 0 || direction.z != 0) {
                vel.velocity = glm::normalize(glm::vec3(p.camera.orientation() * direction)) * speed * dt;
            }

//            vel.velocity.x = 0;
//            vel.velocity.z = 0;
//            if (Input::isKeyPressed(KeyCode::eUpArrow)) {
//                vel.velocity += tr.forward() * speed * dt;
//            }
//            if (Input::isKeyPressed(KeyCode::eDownArrow)) {
//                vel.velocity -= tr.forward() * speed * dt;
//            }
//            if (Input::isKeyPressed(KeyCode::eLeftArrow)) {
//                vel.velocity -= tr.right() * speed * dt;
//            }
//            if (Input::isKeyPressed(KeyCode::eRightArrow)) {
//                vel.velocity += tr.right() * speed * dt;
//            }
//            if (Input::isKeyDown(KeyCode::eSpace)) {
//                vel.velocity.y += 5.0f * dt;
//            }
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
            auto ctx = RayTraceContext {
                .position = p.camera.position,
                .direction = p.camera.forward(),
                .ignoreLiquid = true
            };

            rayTraceResult = rayTraceBlocks(*world, ctx);
            if (rayTraceResult.has_value()) {
                if (Input::isMouseButtonPressed(MouseButton::Left)) {
                    p.cooldown = 0.25f;

                    connection->send(CPlayerDiggingPacket{
                        .pos = rayTraceResult->pos,
                        .dir = rayTraceResult->dir
                    });
                } else if (Input::isMouseButtonPressed(MouseButton::Right)) {
                    p.cooldown = 0.25f;

//                    connection->send(SChangeBlockPacket{
//                        .pos = result->pos + result->dir,
//                        .block = States::TORCH
//                    });
                }
            }
        });
    }
    void Render(CommandBuffer cmd) override {
        setupCamera();
        setupTerrain();
        renderer->drawTerrain(cmd);

        ecs.view<Transform, ModelComponent>().each([](const auto& tr, const auto& mr) {
            // todo: animation
//            const auto m = tr.localToWorldMatrix();
//
//            glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(m));
//            glBindVertexArray(mr.mesh->vao);
//            glDrawElements(GL_TRIANGLES, mr.mesh->index_count, GL_UNSIGNED_INT, nullptr);
        });
    }
    void DrawUI() override {
        const auto position = glm::ivec3(glm::floor(ecs.get<Transform>(connection->player).position));

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Always);
        ImGui::Begin("Info");
        ImGui::TextUnformatted(fmt::format("DeltaTime: {:.3}s", Time::getDeltaTime()).c_str());
        ImGui::TextUnformatted(fmt::format("Position: {}, {}, {}", position.x, position.y, position.z).c_str());
        if (rayTraceResult.has_value()) {
            const auto name = Blocks::blocks.name(rayTraceResult->state.getBlock()).value();
            ImGui::TextUnformatted(fmt::format("Target Block: {}", name).c_str());
        }
        ImGui::End();
    }

private:
    void loadResources() {
        BlockGraphics::init(*resources);
        ChunkStatus::init();
        Materials::init();
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
    }

    void startLocalServer() {
        const auto viewDistance = std::max(2, renderDistance - 1);
        world = std::make_unique<ClientWorld>(viewDistance);
        server = std::make_unique<CraftServer>(viewDistance + 1, *resources);
        frustum = std::make_unique<ViewFrustum>(renderDistance);

        connection = std::make_unique<Connection>(entt::null, server->getLocalAddress());
        connection->send(CHandshakePacket{720, ProtocolType::HANDSHAKING});
        connection->send(CLoginStartPacket{});

        const auto stride = renderDistance * 2 + 1;
        while (world->provider->chunkArray.getLoaded() < stride * stride) {
            handler.handlePackets(*this, *connection);
        }
        spdlog::info("Game started: {}", server->getLocalAddress());

        renderer = std::make_unique<WorldRenderer>();
    }

private:
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
//            ecs.emplace<GravityComponent>(connection->player);
            ecs.emplace<VelocityComponent>(connection->player);
//            ecs.emplace<CollisionComponent>(connection->player);
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
    void setupCamera() {
        auto& transform = ecs.get<PlayerComponent>(connection->player).camera;

        const auto projection = camera.getProjection();
        const auto view = glm::inverse(transform.localToWorldMatrix());
        const auto camera_matrix = projection * view;

        const auto constants = CameraConstants {
            .transform = camera_matrix,
            .position = glm::vec4(transform.position, 0.0f)
        };

        renderer->uniforms[0].setData(&constants, sizeof(CameraConstants), 0);
        frustum->ExtractPlanes(glm::transpose(camera_matrix), true);
    }

    void setupTerrain() {
        auto& transform = ecs.get<Transform>(connection->player);
        connection->send(PositionPacket{ .pos = transform.position });

        const auto pos = ChunkPos::from(glm::ivec3(glm::floor(transform.position)));

        world->provider->chunkArray.setCenter(pos.x, pos.z);

        renderer->chunkToRenders.clear();
        for (int x = pos.x - renderDistance; x <= pos.x + renderDistance; ++x) {
            for (int z = pos.z - renderDistance; z <= pos.z + renderDistance; ++z) {
                const auto from = glm::vec3{x << 4, 0, z << 4};
                const auto to = from + glm::vec3{16, 256, 16};

                if (!frustum->TestAABB(from, to)) {
                    continue;
                }

                auto& chunk = frustum->getChunk(x, z);

                if (std::exchange(chunk.needRender, false)) {
                    const auto dx = pos.x - x;
                    const auto dz = pos.z - z;
                    const auto immediate = (dx * dx + dz * dz) <= 1;

                    renderer->dispatcher.rebuild(*world, chunk, x, z, immediate);
                }

                renderer->chunkToRenders.emplace_back(&chunk);
            }
        }
    }
};

auto Blaze::CreateApplication() -> std::unique_ptr<Application> {
    return std::make_unique<Game>();
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