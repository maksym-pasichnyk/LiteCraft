#include <span>
#include <queue>
#include <mutex>
#include <memory>
#include <iostream>
#include <functional>

#include <glm/glm.hpp>
#include <entt/entt.hpp>
#include <spdlog/spdlog.h>

#include "raytrace.hpp"
#include "transform.hpp"
#include "util/Utils.hpp"
#include "CraftServer.hpp"
#include "TextureAtlas.hpp"
#include "UserInterface.hpp"

#include <Time.hpp>
#include <Blaze.hpp>
#include <Input.hpp>
#include <Screen.hpp>
#include <Display.hpp>
#include <Material.hpp>
#include <ImLogger.hpp>
#include <WorldRenderer.hpp>
#include <misc/cpp/imgui_stdlib.h>

#include <block/Blocks.hpp>
#include <block/States.hpp>
#include <block/BlockStates.hpp>
#include <client/world/ClientWorld.hpp>
#include <client/render/ViewFrustum.hpp>
#include <client/render/model/Models.hpp>
#include <client/render/ModelComponent.hpp>
#include <client/render/chunk/ChunkRenderDispatcher.hpp>

#include <world/biome/Biome.hpp>
#include <world/biome/Biomes.hpp>
#include <world/chunk/ChunkStatus.hpp>
#include <world/gen/carver/Carvers.hpp>
#include <world/gen/feature/Features.hpp>
#include <world/gen/pools/JigsawPools.hpp>
#include <world/gen/placement/Placements.hpp>
#include <world/gen/surface/SurfaceBuilders.hpp>
#include <world/gen/carver/ConfiguredCarvers.hpp>
#include <world/gen/feature/ConfiguredFeatures.hpp>
#include <world/gen/feature/structure/Structures.hpp>
#include <world/gen/feature/processor/ProcessorLists.hpp>
#include <world/gen/surface/ConfiguredSurfaceBuilders.hpp>
#include <world/gen/feature/structure/StructureFeatures.hpp>

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
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

using ServerNetHandler = PacketHandler<
    SEncryptionRequestPacket,
    SEnableCompressionPacket,
    SLoginSuccessPacket,
    SLoadChunkPacket,
    SUnloadChunkPacket,
    SChangeBlockPacket,
    SSpawnPlayerPacket,
    SPlayerPositionLookPacket,
    SJoinGamePacket
>;

struct AppState {
    virtual ~AppState() = default;

    virtual void Init() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
    virtual void DrawUI() = 0;
    virtual void Draw(CommandBuffer cmd) = 0;
};

struct MainState : AppState {
    entt::delegate<void()> onStartButton;
    entt::delegate<void()> onExitButton;
    entt::delegate<void(std::string const& ip, int port)> onConnectButton;

    std::string ip = "127.0.0.1";
    int port = 8080;

    void Init() override {
    }
    void Destroy() override {
//        onStartButton.reset();
//        onExitButton.reset();
    }
    void Update() override {
    }
    void DrawUI() override {
        const auto sz = glm::vec2(Screen::getSize());

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(sz.x, sz.y), ImGuiCond_Always);
        ImGui::Begin("#Screen", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
        ImGui::SetCursorPos(ImVec2(sz.x * 0.5f - 100, sz.y * 0.5f - 40));
        ImGui::BeginGroup();
        if (ImGui::Button("Start", ImVec2(200, 30))) {
            onStartButton();
        }
        ImGui::SetNextItemWidth(200);
        ImGui::InputText("IP", &ip);
        ImGui::SetNextItemWidth(200);
        ImGui::InputInt("Port", &port);
        if (ImGui::Button("Connect", ImVec2(200, 30))) {
            onConnectButton(ip, port);
        }
        if (ImGui::Button("Exit", ImVec2(200, 30))) {
            onExitButton();
        }
        ImGui::EndGroup();
        ImGui::End();
    }
    void Draw(CommandBuffer cmd) override {
    }
};

struct GameState : AppState {
    std::shared_ptr<ImLogger> logger{};
    entt::delegate<void()> onExitGame{};

    const int renderDistance = 10;

    tl::optional<SocketAddr> addr{};

    bool focus = false;
    std::string command{};

    entt::registry ecs{};
    ServerNetHandler handler{};
    std::unique_ptr<ClientWorld> world{};
    std::unique_ptr<CraftServer> server{};
    std::unique_ptr<Connection> connection{};
    std::unique_ptr<WorldRenderer> renderer{};
    tl::optional<RayTraceResult> rayTraceResult{};

    explicit GameState(std::shared_ptr<ImLogger> logger) : logger(std::move(logger)) {}

    void Init() override {
        focus = false;
        command.clear();
        startLocalServer();
    }
    void Destroy() override {
//        onExitGame.reset();
        connection.reset();
        renderer.reset();
        server.reset();
        world.reset();
    }

    void Update() override {
        handler.handlePackets(*this, *connection);

        renderer->tick();

        /**************************************************************************************************************/
        const auto dt = Time::getDeltaTime();
        const auto delta = Input::getMouseDelta();

        ecs.view<PlayerComponent, Transform, VelocityComponent>().each([dt, delta](auto& p, auto& tr, auto& vel) {
            p.camera.rotation -= getRotationDelta(p.camera, delta, dt);
            p.camera.rotation.y = glm::clamp(p.camera.rotation.y, -90.0f, 90.0f);

            tr.rotation.x = p.camera.rotation.x;

            const auto speed = Input::isKeyPressed(KeyCode::eLeftShift) ? 50.0f : 5.0f;
            const auto states = std::array{
                Input::isKeyPressed(KeyCode::eW) ? -1 : 0,
                Input::isKeyPressed(KeyCode::eA) ? -1 : 0,
                Input::isKeyPressed(KeyCode::eS) ? 1 : 0,
                Input::isKeyPressed(KeyCode::eD) ? 1 : 0
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

        if (Input::isMouseButtonDown(MouseButton::Left)) {
            focus = true;
        } else if (Input::isKeyDown(KeyCode::eEscape)) {
            focus = false;
        }
        if (extern auto GetUserInterface() -> UserInterface&; GetUserInterface().WantCaptureMouse()) {
            focus = false;
        }
        if (extern auto GetDisplay() -> Display&; GetDisplay().hasFocus()) {
            Input::setLock(focus);
        }
//        if (Input::isKeyDown(KeyCode::eEscape)) {
//            onExitGame();
//        }
    }
    void DrawUI() override {
        const auto screenSize = Screen::getSize();
        const auto position = glm::ivec3(glm::floor(ecs.get<Transform>(connection->player).position));

        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(screenSize.x, 200), ImGuiCond_Always);
        ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
        ImGui::TextUnformatted(fmt::format("FPS: {:.3}s", 1.0f / Time::getDeltaTime()).c_str());
        ImGui::TextUnformatted(fmt::format("DeltaTime: {:.3}s", Time::getDeltaTime()).c_str());
        ImGui::TextUnformatted(fmt::format("Position: {}, {}, {}", position.x, position.y, position.z).c_str());
        ImGui::TextUnformatted(fmt::format("Client: {}", world->provider->chunkArray.getLoaded()).c_str());
        if (rayTraceResult.has_value()) {
            const auto block = rayTraceResult->state.getBlock();

            ImGui::TextUnformatted(fmt::format("Target Block: {}", Blocks::blocks.name(block).value()).c_str());
            for (auto&& [name, prop] : block->properties) {
                const auto value = rayTraceResult->state.get(prop);
                ImGui::TextUnformatted(fmt::format("#{}: {}", name, PropertyUtil::string(value).value()).c_str());
            }
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(glm::f32(screenSize.x), 0), ImGuiCond_Always);
        ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        logger->Draw(ImVec2(0, 100));
        ImGui::SetNextItemWidth(screenSize.x - 16);
        if (ImGui::InputText("##command", &command, ImGuiInputTextFlags_EnterReturnsTrue)) {
            ImGui::SetKeyboardFocusHere(-1);

            if (!command.empty()) {
                if (command.starts_with('/')) {
                    auto cmd = std::string_view(command).substr(1);
                    if (cmd == "clear") {
                        logger->clear();
                    } else {
                        spdlog::info("unknown command: {}", cmd);
                    }
                } else {
                    spdlog::info("{}", command);
                }
                command.clear();
            }
        }
        ImGui::SetWindowPos(ImVec2(0, glm::f32(screenSize.y - ImGui::GetWindowHeight())), ImGuiCond_Always);
        ImGui::End();
    }
    void Draw(CommandBuffer cmd) override {
        setupCamera();
        setupTerrain();
        renderer->drawTerrain(cmd);
//
//        ecs.view<Transform, ModelComponent>().each([](const auto& tr, const auto& mr) {
//// todo: animation
////            const auto m = tr.localToWorldMatrix();
////
////            glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(m));
////            glBindVertexArray(mr.mesh->vao);
////            glDrawElements(GL_TRIANGLES, mr.mesh->index_count, GL_UNSIGNED_INT, nullptr);
//        });
    }

private:
    void startLocalServer() {
        const auto viewDistance = std::max(2, renderDistance - 1);
        world = std::make_unique<ClientWorld>(viewDistance);

        if (!addr) {
            server = std::make_unique<CraftServer>(viewDistance + 1);
            addr = server->getLocalAddress();
        }
        renderer = std::make_unique<WorldRenderer>(renderDistance);

        connection = std::make_unique<Connection>(entt::null, *addr);
        connection->send(CHandshakePacket{720, ProtocolType::HANDSHAKING});
        connection->send(CLoginStartPacket{});

        while (connection->player == entt::null) {
            handler.handlePackets(*this, *connection);
        }
        spdlog::info("Game started: {}", *addr);
    }

public:
    /**************************************************************************************************************/

    void onPacket(Connection& connection, const SEncryptionRequestPacket& packet) {
        connection.send(CEncryptionResponsePacket{});
    }

    void onPacket(Connection& _, const SEnableCompressionPacket& packet) {}

    void onPacket(Connection& _, const SLoginSuccessPacket& packet) {}

    void onPacket(Connection& _, const SLoadChunkPacket& packet) {
        auto blocks = PacketBuffer::from(packet.bytes);

        auto chunk = new Chunk(ChunkPos::from(packet.x, packet.z));
        for (size_t i = 0; i < chunk->sections.size(); ++i) {
            if ((packet.sections & (1 << i)) != 0) {
                chunk->sections[i] = std::make_unique<ChunkSection>();
                blocks.read_bytes_to(std::as_writable_bytes(std::span(chunk->sections[i]->blocks)));
            }
        }

        world->loadChunk(packet.x, packet.z, chunk);

        for (int x = packet.x - 1; x <= packet.x + 1; ++x) {
            for (int z = packet.z - 1; z <= packet.z + 1; ++z) {
                renderer->frustum.markForRender(x, z);
            }
        }
    }

    void onPacket(Connection& _, const SUnloadChunkPacket& packet) {
        world->unloadChunk(packet.x, packet.z);
    }

    void onPacket(Connection& _, const SChangeBlockPacket& packet) {
        auto chunk = world->getChunk(packet.pos.x >> 4, packet.pos.z >> 4);
        if (!chunk) {
            return;
        }
        chunk->setData(packet.pos, packet.block);

        const auto pos = packet.pos;
        for (int x = (pos.x - 1) >> 4; x <= (pos.x + 1) >> 4; x++) {
            for (int z = (pos.z - 1) >> 4; z <= (pos.z + 1) >> 4; z++) {
                renderer->frustum.markForRender(x, z);
            }
        }
    }

    void onPacket(Connection& _, const SJoinGamePacket& packet) {
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

    void onPacket(Connection& _, const SPlayerPositionLookPacket& packet) {
        ecs.replace<Transform>(connection->player, packet.pos, packet.rot);
    }

    void onPacket(Connection& _, const SSpawnPlayerPacket& packet) {
        spdlog::info("SpawnPlayer: {}, {}, {}", packet.pos.x, packet.pos.y, packet.pos.z);

        auto player = ecs.create();
        ecs.emplace<Transform>(player, packet.pos, glm::vec2{});
//        ecs.emplace<ModelComponent>(player, *Models::models.get("geometry.humanoid").value());
//        ecs.emplace<GravityComponent>(player);
//        ecs.emplace<VelocityComponent>(player);
//        ecs.emplace<CollisionComponent>(player);
    }

private:
    void setupCamera() {
        auto& transform = ecs.get<PlayerComponent>(connection->player).camera;

        renderer->camera.setSize(Screen::getSize());
        const auto projection = renderer->camera.getProjection();
        const auto view = glm::inverse(transform.localToWorldMatrix());
        const auto camera_matrix = projection * view;

        const auto constants = CameraConstants {
            .transform = camera_matrix,
            .position = glm::vec4(transform.position, 0.0f)
        };

        renderer->uniforms[0].setData(&constants, sizeof(CameraConstants), 0);
        renderer->frustum.ExtractPlanes(glm::transpose(camera_matrix), true);
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

                if (!renderer->frustum.TestAABB(from, to)) {
                    continue;
                }

                auto& chunk = renderer->frustum.getChunk(x, z);

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

struct AppClient : Blaze::Application {
    std::unique_ptr<MainState> mainState{};
    std::unique_ptr<GameState> gameState{};

    AppState* state{};
    AppState* nextState{};

    explicit AppClient(std::shared_ptr<ImLogger> logger) {
        PHYSFS_mount("client-extra.zip", nullptr, 1);

        mainState = std::make_unique<MainState>();
        mainState->onStartButton.connect<&AppClient::onStartButton>(this);
        mainState->onExitButton.connect<&AppClient::onExitButton>(this);
        mainState->onConnectButton.connect<&AppClient::onConnectButton>(this);

        gameState = std::make_unique<GameState>(std::move(logger));
        gameState->onExitGame.connect<&AppClient::onExitGame>(this);
    }

    void Init() override {
        ChunkStatus::init();
        Materials::init();
        Blocks::init();
        BlockStates::init();
        TextureManager::instance().build();
        Models::init();
        States::init();
        BlockTags::init();
        Carvers::init();
        Features::init();
        Placements::init();
        Structures::init();
        SurfaceBuilders::init();
        ConfiguredCarvers::init();
        ConfiguredFeatures::init();
        ProcessorLists::init();
        JigsawPools::init();
        StructureFeatures::init();
        ConfiguredSurfaceBuilders::init();
        Biomes::init();

        state = mainState.get();
        state->Init();
    }
    void Destroy() override {
        state->Destroy();
    }
    void Update() override {
        if (nextState != nullptr) {
            state->Destroy();
            state = nextState;
            state->Init();

            nextState = nullptr;
        }
        state->Update();
    }
    void Draw(CommandBuffer cmd) override {
        state->Draw(cmd);
    }
    void DrawUI() override {
        state->DrawUI();
    }

    void onStartButton() {
        nextState = gameState.get();
    }

    void onExitButton() {
        extern auto GetDisplay() -> Display&;
        GetDisplay().close();
    }

    void onConnectButton(std::string const& ip, int port) {
        gameState->addr = SocketAddr::from(Ipv4Addr::from(ip).value(), port);
        nextState = gameState.get();
    }

    void onExitGame() {
        nextState = mainState.get();
    }
};

auto main(int argc, char* argv[]) -> int {
    if constexpr (Utils::is_server()) {
        PHYSFS_mount("client-extra.zip", nullptr, 1);

        ChunkStatus::init();
        Materials::init();
        Blocks::init();
        BlockStates::init();
        Models::init();
        States::init();
        BlockTags::init();
        Carvers::init();
        Features::init();
        Placements::init();
        Structures::init();
        SurfaceBuilders::init();
        ConfiguredCarvers::init();
        ConfiguredFeatures::init();
        ProcessorLists::init();
        JigsawPools::init();
        StructureFeatures::init();
        ConfiguredSurfaceBuilders::init();
        Biomes::init();

        const auto renderDistance = 10;
        const auto viewDistance = std::max(2, renderDistance - 1);

        auto server = std::make_unique<CraftServer>(viewDistance + 1);
        spdlog::info("Start server: {}", server->getLocalAddress());
        std::string input;
        while (true) {
            std::cin >> input;
            if (input == "exit") {
                break;
            }
            std::this_thread::yield();
        }
    } else {
        auto logger = std::make_shared<ImLogger>();
        spdlog::default_logger()->sinks().push_back(logger);

        Blaze::Start([logger]() -> std::unique_ptr<Blaze::Application> {
            return std::make_unique<AppClient>(logger);
        });
    }
    return 0;
}

//auto parse_command(std::string_view cmd, size_t& offset) -> tl::optional<std::string> {
//    if (offset == std::string_view::npos) {
//        return tl::nullopt;
//    }
//    const auto off = std::exchange(offset, cmd.find(' ', offset));
//    return offset != std::string_view::npos
//            ? std::string(cmd.substr(off, offset - off))
//            : std::string(cmd.substr(off));
//}