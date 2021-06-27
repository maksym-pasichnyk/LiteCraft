#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <set>
#include <span>
#include <queue>
#include <mutex>
#include <random>
#include <memory>

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <fmt/format.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

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

struct AABB {
    float min_x;
    float min_y;
    float min_z;
    float max_x;
    float max_y;
    float max_z;

    constexpr auto min() const noexcept -> glm::vec3 {
        return {min_x, min_y, min_z};
    }

    constexpr auto max() const noexcept -> glm::vec3 {
        return {min_x, min_y, min_z};
    }

    constexpr auto size() const noexcept -> glm::vec3 {
        return max() - min();
    }

    constexpr auto center() const noexcept -> glm::vec3 {
        return (min() + max()) * 0.5f;
    }

    constexpr auto add(const glm::vec3& offset) const noexcept -> AABB {
        return from(min() + offset, max() + offset);
    }

    constexpr auto sub(const glm::vec3& offset) const noexcept -> AABB {
        return from(min() - offset, max() - offset);
    }

    static constexpr auto from(const glm::vec3& min, const glm::vec3& max) noexcept -> AABB {
        return AABB{min.x, min.y, min.z, max.x, max.y, max.z};
    }

    static constexpr auto with_size(const glm::vec3& min, const glm::vec3& size) noexcept -> AABB {
        return from(min, min + size);
    }
};

struct CameraConstants {
	glm::mat4 transform;
	glm::vec4 position;
    glm::vec4 FOG_COLOR;
    glm::vec2 FOG_CONTROL;
    float RENDER_DISTANCE;
};

struct RenderFrame {
    GLuint framebuffer;
    GLuint color_attachment;
    GLuint depth_attachment;

    GLuint camera_ubo;
    void* camera_ptr;
};

namespace nlohmann {
    void to_json(json &value, const glm::vec2 &v) {
        value = {v.x, v.y};
    }

    void from_json(const json &value, glm::vec2 &v) {
        value.at(0).get_to(v.x);
        value.at(1).get_to(v.y);
    }

    void to_json(json &value, const glm::vec3 &v) {
        value = {v.x, v.y, v.z};
    }

    void from_json(const json &value, glm::vec3 &v) {
        value.at(0).get_to(v.x);
        value.at(1).get_to(v.y);
        value.at(2).get_to(v.z);
    }
}

struct PlayerComponent {};
struct MobComponent {};

struct VelocityComponent {
    glm::vec2 horizontal{};
    glm::f32 vertical = 0;

    constexpr auto flat() const -> glm::vec3 {
        return {horizontal.x, vertical, horizontal.y};
    }
};

struct App {
    entt::registry _registry;
    entt::entity _player;

    bool running = true;

    SDL_Window* window;
    SDL_GLContext context;
    ResourcePackManager resources{};

    NetworkManager nm;
    std::shared_ptr<NetworkConnection> connection;
    PacketManager<App, 10> packetManager;

    Input input{};
    Camera camera{};

    int32_t last_center_x = -9999;
    int32_t last_center_z = -9999;

	int cooldown = 0;
	int viewDistance = 19;

    GLuint entity_pipeline;
    GLuint simple_pipeline;
    GLuint opaque_pipeline;
    GLuint cutout_pipeline;
    GLuint transparent_pipeline;

    TextureAtlas texture_atlas;

    std::vector<ChunkRenderData*> chunkToRenders;

    std::unique_ptr<ChunkRenderDispatcher> renderDispatcher = nullptr;
    std::unique_ptr<ViewFrustum> frustum = nullptr;

    SimpleVBuffer lineCache{};
    std::unique_ptr<Mesh> lineMesh{nullptr};
    std::unique_ptr<CraftServer> server{nullptr};
    std::unique_ptr<ClientWorld> world{nullptr};

    std::optional<RayTraceResult> rayTraceResult{std::nullopt};

    bool debugCamera = false;
    int frameIndex = 0;
    std::array<RenderFrame, 2> frames;
    glm::vec4 FOG_COLOR;

    double frameTime = 0;
    int frameCount = 0;
    int FPS = 0;
    std::chrono::high_resolution_clock::time_point startTime;
    glm::ivec2 displaySize{};

    App(const char* title, uint32_t width, uint32_t height) {
        packetManager.bind<SUnloadChunkPacket, &App::processUnloadChunk>();
        packetManager.bind<SLoadChunkPacket, &App::processLoadChunk>();
        packetManager.bind<SChangeBlockPacket, &App::processChangeBlock>();

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        context = SDL_GL_CreateContext(window);

        SDL_GetWindowSize(window, &displaySize.x, &displaySize.y);
        SDL_SetWindowResizable(window, SDL_FALSE);

        glewInit();

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GraphicsDebugCallback, nullptr);

        glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

        createFrames(width, height);
        createImGui();

        _player = createPlayer({3385, 83, 1500});

        // createZombie({3386, 83, 1501});
        // createZombie({3387, 83, 1502});
        // createZombie({3388, 83, 1503});
    }

    entt::entity createPlayer(const glm::vec3& position) {
        auto id = _registry.create();
        _registry.emplace<PlayerComponent>(id);
        _registry.emplace<VelocityComponent>(id);
        _registry.emplace<TransformComponent>(id, TransformComponent{
            .yaw = 0,
            .pitch = 0,
            .position = position
        });
        return id;
    }

    entt::entity createZombie(const glm::vec3& position) {
        auto id = _registry.create();
        _registry.emplace<MobComponent>(id);
        _registry.emplace<VelocityComponent>(id);
        _registry.emplace<TransformComponent>(id, TransformComponent{
            .yaw = 0,
            .pitch = 0,
            .position = position
        });
        return id;
    }

    static void GraphicsDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const *message, void const *user_param) {
        auto source_str = [source]() -> std::string_view {
            switch (source) {
                case GL_DEBUG_SOURCE_API:
                    return "API";
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                    return "WINDOW SYSTEM";
                case GL_DEBUG_SOURCE_SHADER_COMPILER:
                    return "SHADER COMPILER";
                case GL_DEBUG_SOURCE_THIRD_PARTY:
                    return "THIRD PARTY";
                case GL_DEBUG_SOURCE_APPLICATION:
                    return "APPLICATION";
                case GL_DEBUG_SOURCE_OTHER:
                    return "OTHER";
                default:
                    return "UNKNOWN";
            }
        }();

        auto type_str = [type]() -> std::string_view {
            switch (type) {
                case GL_DEBUG_TYPE_ERROR:
                    return "ERROR";
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                    return "DEPRECATED_BEHAVIOR";
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                    return "UNDEFINED_BEHAVIOR";
                case GL_DEBUG_TYPE_PORTABILITY:
                    return "PORTABILITY";
                case GL_DEBUG_TYPE_PERFORMANCE:
                    return "PERFORMANCE";
                case GL_DEBUG_TYPE_MARKER:
                    return "MARKER";
                case GL_DEBUG_TYPE_OTHER:
                    return "OTHER";
                default:
                    return "UNKNOWN";
            }
        }();

        auto severity_str = [severity]() -> std::string_view {
            switch (severity) {
                case GL_DEBUG_SEVERITY_NOTIFICATION:
                    return "NOTIFICATION";
                case GL_DEBUG_SEVERITY_LOW:
                    return "LOW";
                case GL_DEBUG_SEVERITY_MEDIUM:
                    return "MEDIUM";
                case GL_DEBUG_SEVERITY_HIGH:
                    return "HIGH";
                default:
                    return "UNKNOWN";
            }
        }();

        fmt::print("{}, {}, {}, {}: {}\n", source_str, type_str, severity_str, id, message);
    }

    void createFrames(uint32_t width, uint32_t height) {
        constexpr std::array attributes {
            VertexArrayAttrib{0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, point)},
            VertexArrayAttrib{1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, tex)},
            VertexArrayAttrib{2, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, color)},
            VertexArrayAttrib{3, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, light)}
        };

        constexpr std::array bindings {
            VertexArrayBinding{0, 0},
            VertexArrayBinding{1, 0},
            VertexArrayBinding{2, 0},
            VertexArrayBinding{3, 0},
        };

        lineMesh = std::make_unique<Mesh>(attributes, bindings, sizeof(Vertex), GL_DYNAMIC_DRAW);

        for (int i = 0; i < 2; i++) {
            glCreateBuffers(1, &frames[i].camera_ubo);
            glNamedBufferStorage(frames[i].camera_ubo, sizeof(CameraConstants), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
            frames[i].camera_ptr = glMapNamedBufferRange(frames[i].camera_ubo, 0, sizeof(CameraConstants), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

            glCreateTextures(GL_TEXTURE_2D, 1, &frames[i].color_attachment);
            glTextureStorage2D(frames[i].color_attachment, 1, GL_RGB8, width, height);
            glTextureParameteri(frames[i].color_attachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(frames[i].color_attachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glCreateRenderbuffers(1, &frames[i].depth_attachment);
            glNamedRenderbufferStorage(frames[i].depth_attachment, GL_DEPTH32F_STENCIL8, width, height);

            glCreateFramebuffers(1, &frames[i].framebuffer);
            glNamedFramebufferTexture(frames[i].framebuffer, GL_COLOR_ATTACHMENT0, frames[i].color_attachment, 0);
            glNamedFramebufferRenderbuffer(frames[i].framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frames[i].depth_attachment);

            if(glCheckNamedFramebufferStatus(frames[i].framebuffer, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                fmt::print("Framebuffer is not complete!: {}\n", glGetError());
            }
        }
    }

    void createImGui() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init("#version 150");
    }

    void handleEvents() {
        SDL_PumpEvents();

        SDL_Event event{};
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

        	if (event.type == SDL_WINDOWEVENT_FOCUS_LOST) {
//				window.setMouseCursorVisible(true);
			} else if (event.type == SDL_WINDOWEVENT_FOCUS_GAINED) {
//        		window.setMouseCursorVisible(false);
        	} else if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

	void updateInput(float dt) {
        input.update();

        if (cooldown > 0) {
            cooldown -= 1;
        }

        if (input.isKeyDown(Input::Key::X)) {
            debugCamera = !debugCamera;
        }

        const auto mouse_center = displaySize / 2;
        const auto mouse_position = input.getMousePosition();
		const auto mouse_delta = mouse_center - mouse_position;
        SDL_WarpMouseInWindow(window, mouse_center.x, mouse_center.y);

        auto& transform = _registry.get<TransformComponent>(_player);
        auto& velocity = _registry.get<VelocityComponent>(_player);

        rotateCamera(transform, mouse_delta, dt);

        auto cam_vel = calc_free_camera_velocity(input, transform, dt);

        velocity.horizontal = {cam_vel.x, cam_vel.z};
        velocity.vertical = cam_vel.y;

//		RayTraceContext ray_trace_context {
//			.position = transform.position + glm::vec3(0, 1.68, 0),
//			.direction = transform.forward(),
//			.ignoreLiquid = true
//		};
//
//		rayTraceResult = rayTraceBlocks(*world, ray_trace_context);
//        if (cooldown == 0 && rayTraceResult.has_value()) {
//            if (input.isMouseButtonPressed(Input::MouseButton::Left)) {
//                cooldown = 10;
//
//                connection->sendPacket(CPlayerDiggingPacket{
//                    .pos = rayTraceResult->pos,
//                    .dir = rayTraceResult->dir
//                });
//            } else if (input.isMouseButtonPressed(Input::MouseButton::Right)) {
//                cooldown = 10;
//
//                connection->sendPacket(SChangeBlockPacket{
//                    .pos = rayTraceResult->pos + rayTraceResult->dir,
//                    .data = Blocks::TORCH->getDefaultState()
//                });
//            }
//		}
    }

    void setupCamera(TransformComponent& transform) {
        const auto [x, y, z] = transform.position;
        const auto topMaterial = world->getBlock(glm::floor(x), std::floor(y + 1.68), glm::floor(z))->getMaterial();

        glm::vec2 FOG_CONTROL;
        if (topMaterial == Materials::WATER) {
            FOG_COLOR = {0.27, 0.68, 0.96, 1};
            FOG_CONTROL = glm::vec2{0, 5};
        } else if (topMaterial == Materials::LAVA) {
            FOG_COLOR = {0.96, 0.38, 0.27, 1};
            FOG_CONTROL = glm::vec2{-2, 1};
        } else {
            FOG_COLOR = {0, 0.68, 1.0, 1};
            FOG_CONTROL = {9, 13};
        }

        const auto projection_matrix = camera.getProjection();
        const auto transform_matrix = transform.getTransformMatrix(glm::vec3(0, 1.68, 0));
        const auto camera_matrix = projection_matrix * transform_matrix;

        CameraConstants camera_constants{
            .transform = camera_matrix,
            .position = glm::vec4(transform.position, 0),
            .FOG_COLOR = FOG_COLOR,
            .FOG_CONTROL = FOG_CONTROL,
            .RENDER_DISTANCE = 8.0f,
        };

        std::memcpy(frames[frameIndex].camera_ptr, &camera_constants, sizeof(CameraConstants));

        if (!debugCamera) {
            frustum->ExtractPlanes(glm::transpose(camera_matrix), true);
        }
    }

    void processUnloadChunk(const SUnloadChunkPacket& packet) {
        world->unloadChunk(packet.x, packet.z);
    }

    void processLoadChunk(const SLoadChunkPacket& packet) {
        world->loadChunk(packet.x, packet.z, packet.chunk);

        for (int chunk_x = packet.x - 1; chunk_x <= packet.x + 1; ++chunk_x) {
            for (int chunk_z = packet.z - 1; chunk_z <= packet.z + 1; ++chunk_z) {
                frustum->chunks[world->provider->chunkArray.getIndex(chunk_x, chunk_z)].needRender = true;
            }
        }
    }

    void processChangeBlock(const SChangeBlockPacket& packet) {
        const auto pos = packet.pos;

        std::set<ChunkPos> positions;
        for (int x = (pos.x - 1) >> 4; x <= (pos.x + 1) >> 4; x++) {
            for (int z = (pos.z - 1) >> 4; z <= (pos.z + 1) >> 4; z++) {
                frustum->chunks[world->provider->chunkArray.getIndex(x, z)].needRender = true;
            }
        }
    }

    void setupTerrain(TransformComponent& transform) {
        const auto center_x = static_cast<int32_t>(transform.position.x) >> 4;
        const auto center_z = static_cast<int32_t>(transform.position.z) >> 4;

        if (!debugCamera) {
            if (last_center_x != center_x || last_center_z != center_z) {
                last_center_x = center_x;
                last_center_z = center_z;

                world->provider->chunkArray.setCenter(center_x, center_z);

                connection->sendPacket(PositionPacket{
                    .pos = transform.position
                });
            }
        }

        chunkToRenders.clear();

        for (glm::i32 chunk_x = last_center_x - 8; chunk_x <= last_center_x + 8; chunk_x++) {
            for (glm::i32 chunk_z = last_center_z - 8; chunk_z <= last_center_z + 8; chunk_z++) {
                const auto bounds_min = glm::vec3{chunk_x << 4, 0, chunk_z << 4};
                const auto bounds_max = bounds_min + glm::vec3{16, 256, 16};

                if (frustum->TestAABB(bounds_min, bounds_max)) {
                    const glm::i32 i = world->provider->chunkArray.getIndex(chunk_x, chunk_z);

                    if (std::exchange(frustum->chunks[i].needRender, false)) {
                        const auto dx = last_center_x - chunk_x;
                        const auto dz = last_center_z - chunk_z;
                        const auto immediate = (dx * dx + dy * dy) <= 1;

                        renderDispatcher->rebuildChunk(frustum->chunks[i], chunk_x, chunk_z, immediate);
                    }
                    chunkToRenders.emplace_back(&frustum->chunks[i]);
                }
            }
        }
    }

    void renderTerrain() {
        glBindTexture(GL_TEXTURE_2D, texture_atlas.texture);
		glActiveTexture(GL_TEXTURE0);

        glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
//        glEnable(GL_DEPTH_CLAMP);
		glDepthFunc(GL_GREATER);
		glDisable(GL_BLEND);
//		glDepthRange(0.01, 1.0);

        glUseProgram(opaque_pipeline);
        renderLayer(RenderLayer::Opaque);

//        glEnable(GL_BLEND);
//        glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

        glUseProgram(cutout_pipeline);
        renderLayer(RenderLayer::Cutout);

		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		glUseProgram(transparent_pipeline);
        renderLayer(RenderLayer::Transparent);

//        glDisable(GL_BLEND);
//        glDepthRange(0, 1.0);

//        glBindTexture(GL_TEXTURE_2D, agentTexture);
//        glm::mat4 model_transform = glm::translate(glm::mat4(1.0f), glm::vec3(636, 72, 221));

//        glUseProgram(entity_pipeline);
//        glUniform3fv(0, 1, FOG_COLOR.data());
//        glUniformMatrix4fv(8, 1, GL_FALSE, glm::value_ptr(model_transform));

//        glBindTexture(GL_TEXTURE_2D, goatTexture);
//        glBindVertexArray(goatModel->mesh.vao);
//        glDrawElements(GL_TRIANGLES, goatModel->mesh.index_count, GL_UNSIGNED_INT, nullptr);

        glBindTexture(GL_TEXTURE_2D, 0);

        lineCache.clear();
        for (auto const& [_, /*mob,*/ transform] : _registry.view<MobComponent, TransformComponent>().each()) {
            const auto aabb = AABB::with_size(transform.position, glm::vec3(1, 2, 1));

            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
            lineCache.vertex(aabb.min_x, aabb.min_y, aabb.min_z, 0, 0, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.min_x, aabb.max_y, aabb.min_z, 0, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.max_x, aabb.max_y, aabb.min_z, 1, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.max_x, aabb.min_y, aabb.min_z, 1, 0, 0, 0, 0, 0xFF);

            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
            lineCache.vertex(aabb.max_x, aabb.min_y, aabb.min_z, 0, 0, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.max_x, aabb.max_y, aabb.min_z, 0, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.max_x, aabb.max_y, aabb.max_z, 1, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.max_x, aabb.min_y, aabb.max_z, 1, 0, 0, 0, 0, 0xFF);

            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
            lineCache.vertex(aabb.max_x, aabb.min_y, aabb.max_z, 0, 0, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.max_x, aabb.max_y, aabb.max_z, 0, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.min_x, aabb.max_y, aabb.max_z, 1, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.min_x, aabb.min_y, aabb.max_z, 1, 0, 0, 0, 0, 0xFF);

            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
            lineCache.vertex(aabb.min_x, aabb.min_y, aabb.max_z, 0, 0, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.min_x, aabb.max_y, aabb.max_z, 0, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.min_x, aabb.max_y, aabb.min_z, 1, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(aabb.min_x, aabb.min_y, aabb.min_z, 1, 0, 0, 0, 0, 0xFF);
        }

		if (rayTraceResult.has_value()) {
			const auto [fx, fy, fz] = glm::vec3(rayTraceResult->pos);

            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
            lineCache.vertex(fx + 0, fy + 0, fz + 0, 0, 0, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 0, fy + 1, fz + 0, 0, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 1, fy + 1, fz + 0, 1, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 1, fy + 0, fz + 0, 1, 0, 0, 0, 0, 0xFF);

            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
            lineCache.vertex(fx + 1, fy + 0, fz + 0, 0, 0, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 1, fy + 1, fz + 0, 0, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 1, fy + 1, fz + 1, 1, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 1, fy + 0, fz + 1, 1, 0, 0, 0, 0, 0xFF);

            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
            lineCache.vertex(fx + 1, fy + 0, fz + 1, 0, 0, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 1, fy + 1, fz + 1, 0, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 0, fy + 1, fz + 1, 1, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 0, fy + 0, fz + 1, 1, 0, 0, 0, 0, 0xFF);

            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
            lineCache.vertex(fx + 0, fy + 0, fz + 1, 0, 0, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 0, fy + 1, fz + 1, 0, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 0, fy + 1, fz + 0, 1, 1, 0, 0, 0, 0xFF);
            lineCache.vertex(fx + 0, fy + 0, fz + 0, 1, 0, 0, 0, 0, 0xFF);
		}

//        for (auto chunk : chunkToRenders) {
//            const auto [x, z] = chunk->pos;
//            const auto [dx, dz] = std::tuple(x - last_center_x, z - last_center_z);
//
//            if (dx * dx + dz * dz > 4) {
//                continue;
//            }
//
//            const auto [fx, fy, fz] = std::tuple(x * 16.0f, 0.0f, z * 16.0f);
//            const auto [w, h, d] = std::tuple(16, 256, 16);
//
//            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
//            lineCache.vertex(fx + 0, fy + 0, fz + 0, 0, 0, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + 0, fy + h, fz + 0, 0, 1, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + w, fy + h, fz + 0, 1, 1, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + w, fy + 0, fz + 0, 1, 0, 0, 0, 0, 0xFF);
//
//            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
//            lineCache.vertex(fx + w, fy + 0, fz + 0, 0, 0, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + w, fy + h, fz + 0, 0, 1, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + w, fy + h, fz + d, 1, 1, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + w, fy + 0, fz + d, 1, 0, 0, 0, 0, 0xFF);
//
//            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
//            lineCache.vertex(fx + w, fy + 0, fz + d, 0, 0, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + w, fy + h, fz + d, 0, 1, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + 0, fy + h, fz + d, 1, 1, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + 0, fy + 0, fz + d, 1, 0, 0, 0, 0, 0xFF);
//
//            lineCache.quad(0, 1, 1, 2, 2, 3, 3, 0);
//            lineCache.vertex(fx + 0, fy + 0, fz + d, 0, 0, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + 0, fy + h, fz + d, 0, 1, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + 0, fy + h, fz + 0, 1, 1, 0, 0, 0, 0xFF);
//            lineCache.vertex(fx + 0, fy + 0, fz + 0, 1, 0, 0, 0, 0, 0xFF);
//        }

        if (!lineCache.indices.empty()) {
            glDisable(GL_BLEND);
//            glDepthRange(0, 1.0);
            lineMesh->SetIndices(lineCache.indices);
            lineMesh->SetVertices(std::span(lineCache.vertices));

            glUseProgram(simple_pipeline);
            glBindVertexArray(lineMesh->vao);
            glDrawElements(GL_LINES, lineMesh->index_count, GL_UNSIGNED_INT, nullptr);
            glUseProgram(0);
        }
	}

    promise_hpp::promise<void> loadResources() {
        using namespace std::string_view_literals;

        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla"));
        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla_1.14"));
        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla_1.15"));
        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla_1.16"));
        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla_1.16.100"));
        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla_1.16.200"));
        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla_1.16.210"));
        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/experimental_caves_and_cliffs"));
//        resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/chemistry"));

        entity_pipeline = Shader::create("../resources/entity.vert", "../resources/entity.frag");
        simple_pipeline = Shader::create("../resources/simple.vert", "../resources/simple.frag");
        opaque_pipeline = Shader::create("../resources/default.vert", "../resources/default.frag");
        cutout_pipeline = Shader::create("../resources/default.vert", "../resources/cutout.frag");
        transparent_pipeline = Shader::create("../resources/default.vert", "../resources/transparent.frag");

        texture_atlas.loadMetaFile(resources);
        texture_atlas.loadTexture();

        BlockGraphics::mTerrainTextureAtlas = &texture_atlas;

        return executor.schedule([this] {
            Materials::registerMaterials();
            BlockGraphics::initBlocks(resources);
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
//            loadModels();
        });
    }

    void createWorld() {
        nm = NetworkManager::create().value();
        connection = nm.client();

        frustum = std::make_unique<ViewFrustum>(viewDistance);
        world = std::make_unique<ClientWorld>(viewDistance);
        renderDispatcher = std::make_unique<ChunkRenderDispatcher>(world.get());
        server = std::make_unique<CraftServer>(std::move(nm.server()), viewDistance);
    }

    void sendSpawnPacket(const glm::vec3& position) {
        const auto center_x = static_cast<int32_t>(position.x) >> 4;
        const auto center_z = static_cast<int32_t>(position.z) >> 4;

        last_center_x = center_x;
        last_center_z = center_z;

        world->provider->chunkArray.setCenter(center_x, center_z);

        connection->sendPacket(SSpawnPlayerPacket{
            .pos = position
        });
    }

    void tick() {

    }

    void flipFrame() {
        SDL_GL_SwapWindow(window);
        handleEvents();

        frameIndex = (frameIndex + 1) % 2;
    }

    void updateCameraAndRender(TransformComponent& transform) {
        setupCamera(transform);
        setupTerrain(transform);
        renderDispatcher->runChunkUploads();
        renderTerrain();
    }

    scheduler_hpp::scheduler executor;

    void runGameLoop(bool renderWorld) {
        const auto time = std::chrono::high_resolution_clock::now();
        const auto dt = std::chrono::duration<double>(time - startTime).count();

        frameTime += dt;
        frameCount += 1;

        if (frameTime > 1) {
            FPS = frameCount;
            frameTime -= 1;
            frameCount = 0;
        }

        startTime = time;

        auto& player_transform = _registry.get<TransformComponent>(_player);

        updateInput(dt);

        for (auto const& components : _registry.view<TransformComponent, VelocityComponent>().each()) {
            auto& transform = std::get<1>(components);
            const auto& velocity = std::get<2>(components);

            transform.position += velocity.flat() * static_cast<float>(dt);
//            velocity.vertical -= 9.8f * dt;
        }

        packetManager.handlePackets(this, *connection);

        glClearNamedFramebufferfv(frames[frameIndex].framebuffer, GL_COLOR, 0, glm::value_ptr(FOG_COLOR));
        glClearNamedFramebufferfi(frames[frameIndex].framebuffer, GL_DEPTH_STENCIL, 0, 0, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, frames[frameIndex].framebuffer);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, frames[frameIndex].camera_ubo);

        updateCameraAndRender(player_transform);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(300, /*150*/400));
        ImGui::Begin("Debug panel", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings);
        ImGui::Text("FPS: %d", FPS);
        ImGui::Text("Position: %.2f, %.2f, %.2f", player_transform.position.x, player_transform.position.y, player_transform.position.z);
        ImGui::Text("Server chunks: %d", static_cast<int>(server->world->manager->holders.size()));
        ImGui::Text("Client chunks: %d", world->provider->chunkArray.getLoaded());
        ImGui::Text("Render chunks: %zu", chunkToRenders.size());
        ImGui::Text("Render distance: %d", viewDistance);
        ImGui::Text("Debug camera: %s", debugCamera ? "true" : "false");
        ImGui::End();
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glBlitNamedFramebuffer(frames[frameIndex].framebuffer, 0, 0, 0, 800, 600, 0, 0, 800, 600, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        flipFrame();
    }

    int run() {
        using namespace std::chrono_literals;

        SDL_WarpMouseInWindow(window, displaySize.x / 2, displaySize.y / 2);

        camera.setSize(displaySize.x, displaySize.y);

        auto loading = loadResources()
                        .then([this] {
                            createWorld();
                            sendSpawnPacket(_registry.get<TransformComponent>(_player).position);
                        });

        startTime = std::chrono::high_resolution_clock::now();
        while (running) {
            executor.process_all_tasks();

            runGameLoop(true);
        }

        return 0;
    }

	void renderLayer(RenderLayer layer) {
        for (auto chunk : chunkToRenders) {
            // todo: sometimes crash here

            const auto [offset, count] = chunk->layers[static_cast<size_t>(layer)];

            if (count != 0) {
                glBindVertexArray(chunk->mesh.vao);

                glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, static_cast<std::byte*>(nullptr) + offset * sizeof(int32_t));
            }
        }
    }

private:
    static void rotateCamera(TransformComponent& transform, glm::ivec2 mouse_delta, float dt) {
        if (mouse_delta.x != 0 || mouse_delta.y != 0) {
            float d4 = 0.5f * 0.6F + 0.2F;
            float d5 = d4 * d4 * d4 * 8.0f;

            transform.yaw = transform.yaw - mouse_delta.x * d5 * dt * 9.0f;
            transform.pitch = glm::clamp(transform.pitch - mouse_delta.y * d5 * dt * 9.0f, -90.0f, 90.0f);
        }
    }

    static auto calc_free_camera_velocity(Input& input, TransformComponent& transform, float dt) -> glm::vec3 {
        glm::vec3 velocity{0, 0, 0};

        auto forward = transform.forward();
        auto right = transform.right();

        float moveSpeed = input.isKeyPressed(Input::Key::Shift) ? 100.0f : 10.0f;
        if (input.isKeyPressed(Input::Key::Up)) {
            velocity += forward * moveSpeed;
        }
        if (input.isKeyPressed(Input::Key::Down)) {
            velocity -= forward * moveSpeed;
        }
        if (input.isKeyPressed(Input::Key::Left)) {
            velocity -= right * moveSpeed;
        }
        if (input.isKeyPressed(Input::Key::Right)) {
            velocity += right * moveSpeed;
        }
        return velocity;
    }
};

int main() {
    App app{"Bedcraft", 800, 600};
    return app.run();
}