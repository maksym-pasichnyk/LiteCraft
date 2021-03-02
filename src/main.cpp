#include <GL/glew.h>
#include <stdint.hpp>

#include <glm/glm.hpp>

#include <map>
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <random>
#include <set>
#include <queue>
#include <span>
#include <fmt/format.h>

#include "input.hpp"
#include "camera.hpp"
#include "transform.hpp"
#include "Block.hpp"
#include "world/chunk/Chunk.hpp"
#include "BlockReader.hpp"
#include "TextureAtlas.hpp"
#include "raytrace.hpp"
#include "worldgenregion.hpp"
#include "ChunkRenderCache.h"
#include "util/math/ChunkPos.hpp"
#include "world/biome/Biome.hpp"
#include "world/gen/NoiseChunkGenerator.hpp"
#include "shader.hpp"
#include "NetworkManager.hpp"
#include "ClientWorld.hpp"

#include <SDL2/SDL.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

extern void renderBlocks(RenderBuffer& rb, ChunkRenderCache& blocks);

enum class ClientPacketType {
    UnloadChunk,
    LoadChunk,
};

struct ClientPacket {
    ClientPacketType type;
    int chunk_x;
    int chunk_z;
    Chunk* chunk;
};

struct ServerWorld {
    NetworkServer networkServer;
    NoiseChunkGenerator generator;
//    WorldLightManager lightManager;

    std::vector<std::jthread> workers{};
    std::map<int64, std::unique_ptr<Chunk>> chunks{};

    int64_t seed = 0;

    ServerWorld(NetworkServer networkServer) : networkServer{networkServer} {
        workers.emplace_back(std::bind_front(&ServerWorld::runWorker, this));
    }

    ~ServerWorld() {
    	workers.clear();
    }

    static auto getChunkDistance(ChunkPos chunkPos, int chunk_x, int chunk_z) -> int {
        return std::max(std::abs(chunkPos.x - chunk_x), std::abs(chunkPos.z - chunk_z));
    }

    void setChunkLoadedAtClient(int chunk_x, int chunk_z, bool wasLoaded, bool needLoad) {
        if (wasLoaded && !needLoad) {
            ClientPacket packet {
                .type = ClientPacketType::UnloadChunk,
                .chunk_x = chunk_x,
                .chunk_z = chunk_z
            };

            write(networkServer.fd, &packet, sizeof(ClientPacket));
            chunks.erase(ChunkPos::asLong(chunk_x, chunk_z));
        } else if (needLoad && !wasLoaded) {
            auto chunk = provideChunk(chunk_x, chunk_z, ChunkState::Full);
            if (chunk != nullptr) {
                ClientPacket packet {
                        .type = ClientPacketType::LoadChunk,
                        .chunk_x = chunk_x,
                        .chunk_z = chunk_z,
                        .chunk = chunk
                };

                write(networkServer.fd, &packet, sizeof(ClientPacket));
            }
        }
    }

    void updatePlayerPosition(ChunkPos newChunkPos, ChunkPos oldChunkPos) {
        if (std::abs(newChunkPos.x - oldChunkPos.x) <= 2 * 8 && std::abs(newChunkPos.z - oldChunkPos.z) <= 2 * 8) {
            const int xStart = std::min(newChunkPos.x, oldChunkPos.x) - 8;
            const int zStart = std::min(newChunkPos.z, oldChunkPos.z) - 8;
            const int xEnd = std::max(newChunkPos.x, oldChunkPos.x) + 8;
            const int zEnd = std::max(newChunkPos.z, oldChunkPos.z) + 8;

            for (int chunk_x = xStart; chunk_x <= xEnd; chunk_x++) {
                for (int chunk_z = zStart; chunk_z <= zEnd; chunk_z++) {
                    const bool wasLoaded = getChunkDistance(oldChunkPos, chunk_x, chunk_z) <= 8;
                    const bool needLoad = getChunkDistance(newChunkPos, chunk_x, chunk_z) <= 8;

                    setChunkLoadedAtClient(chunk_x, chunk_z, wasLoaded, needLoad);
                }
            }
        } else {
            for (int32 chunk_x = oldChunkPos.x - 8; chunk_x <= oldChunkPos.x + 8; chunk_x++) {
                for (int32 chunk_z = oldChunkPos.z - 8; chunk_z <= oldChunkPos.z + 8; chunk_z++) {
                    setChunkLoadedAtClient(chunk_x, chunk_z, true, false);
                }
            }

            for (int32 chunk_x = newChunkPos.x - 8; chunk_x <= newChunkPos.x + 8; chunk_x++) {
                for (int32 chunk_z = newChunkPos.z - 8; chunk_z <= newChunkPos.z + 8; chunk_z++) {
                    setChunkLoadedAtClient(chunk_x, chunk_z, false, true);
                }
            }
        }
    }

    void runWorker(std::stop_token&& token) {
        auto last_player_position = ChunkPos::from(-9999,-9999);

        ChunkPos player_pos{};
        while (!token.stop_requested()) {
            int ret = read(networkServer.fd, &player_pos, sizeof(ChunkPos));
            if (ret > 0) {
                if (last_player_position != player_pos) {
                    updatePlayerPosition(player_pos, last_player_position);
                    last_player_position = player_pos;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    auto getChunk(int32 chunk_x, int32 chunk_z, ChunkState state) -> Chunk* {
        const auto pos = ChunkPos::from(chunk_x, chunk_z);
        auto it = chunks.find(pos.asLong());
        if (it != chunks.end()) {
            auto chunk = it->second.get();
            if (chunk->state >= state) {
                return chunk;
            }
        }
        return nullptr;
    }

    auto getChunksInRadius(int32 radius, int32 chunk_x, int32 chunk_z, ChunkState state) -> std::optional<std::vector<Chunk*>> {
        if (radius == -1) return {};

        const usize count = radius * 2 + 1;
        std::vector<Chunk*> ret{count * count};

        usize i = 0;
        for (int32 z = chunk_z - radius; z <= chunk_z + radius; z++) {
            for (int32 x = chunk_x - radius; x <= chunk_x + radius; x++) {
                auto chunk = provideChunk(x, z, state);
                if (chunk == nullptr) {
                    return std::nullopt;
                }
                ret.at(i++) = chunk;
            }
        }

        return std::move(ret);
    }

    auto getTaskRange(ChunkState state) {
        switch (state) {
            case ChunkState::Empty:
                return -1;
            case ChunkState::StructureStart:
                return 0;
            case ChunkState::StructureReferences:
                return 0;
            case ChunkState::Noise:
                return 0;
            case ChunkState::Surface:
                return 0;
            case ChunkState::Features:
                return 0;
            case ChunkState::Light:
                return 1;
            case ChunkState::Full:
                return 0;
        }
        return -1;
    }

    auto chunkLoad(int32 chunk_x, int32 chunk_z) -> Chunk* {
        const auto pos = ChunkPos::from(chunk_x, chunk_z);
        auto it = chunks.find(pos.asLong());
        if (it == chunks.end()) {
            it = chunks.emplace(pos.asLong(), std::make_unique<Chunk>(pos)).first;
        }
        return it->second.get();
    }

    auto provideChunk(int32 chunk_x, int32 chunk_z, ChunkState state = ChunkState::Full) -> Chunk* {
        auto chunk = chunkLoad(chunk_x, chunk_z);

        for (int i = (int) chunk->state + 1; i <= (int) state; i++) {
            const auto parent_state = (ChunkState) ((int) i - 1);
            const auto range = getTaskRange((ChunkState) i);
            auto chunksInRadius = getChunksInRadius(range, chunk_x, chunk_z, parent_state);

            WorldGenRegion region{*chunksInRadius, range, chunk_x, chunk_z, seed};

            switch ((ChunkState) i) {
                case ChunkState::Empty:
                    break;
                case ChunkState::StructureStart:
                    generator.generateStructures(region, *chunk);
                    break;
            case ChunkState::StructureReferences:
//                    generator.getStructureReferences(region, *chunk);
                    break;
                case ChunkState::Noise:
                    generator.generateTerrain(*chunk);
                    break;
                case ChunkState::Surface:
                    generator.generateSurface(region, *chunk);
                    break;
                case ChunkState::Features:
                    generator.generateFeatures(region, *chunk);
                    break;
                case ChunkState::Light:
//                    lightManager.calculateLight(region, chunk_x * 16, chunk_z * 16);
                    break;
                case ChunkState::Full:
                    break;
            }

            chunk->state = (ChunkState) i;
        }
		return chunk;
    }
};

struct CameraConstants {
	glm::mat4 transform;
	glm::vec3 position;
};

struct RenderFrame {
    GLuint framebuffer;
    GLuint color_attachment;
    GLuint depth_attachment;

    GLuint camera_ubo;
    void* camera_ptr;
};

struct App {
    bool running = true;

    SDL_Window* window;
    SDL_GLContext context;
    ResourceManager resources{};

    NetworkManager nm;
    NetworkClient networkClient;

    Input input{};
    Camera camera{};
    Transform transform {
        .yaw = 0,
        .pitch = 0,
        .position = {637, 71, 220}
    };

    int32_t last_center_x = -9999;
    int32_t last_center_z = -9999;

	glm::vec3 velocity{0, 0, 0};
	int cooldown = 0;

    GLuint simple_pipeline;
    GLuint opaque_pipeline;
    GLuint cutout_pipeline;
    GLuint transparent_pipeline;

    BlockTable block_pallete{};
    TextureAtlas texture_atlas;

    std::vector<Chunk*> chunkToRenders;

    std::unique_ptr<Mesh> selection_mesh{nullptr};
    std::unique_ptr<ServerWorld> serverWorld{nullptr};
    std::unique_ptr<ClientWorld> clientWorld{nullptr};

    std::optional<RayTraceResult> rayTraceResult{std::nullopt};

    int frameIndex = 0;

    std::array<RenderFrame, 2> frames;

    App(const char* title, uint32_t width, uint32_t height) {
		stbi_set_flip_vertically_on_load(true);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        context = SDL_GL_CreateContext(window);

//        SDL_SetWindowResizable(window, SDL_TRUE);

        glewInit();

        create_frames(width, height);
        create_imgui();

		resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla"));

        simple_pipeline = Shader::create("../resources/simple.vert", "../resources/simple.frag");
        opaque_pipeline = Shader::create("../resources/default.vert", "../resources/default.frag");
		cutout_pipeline = Shader::create("../resources/default.vert", "../resources/cutout.frag");
		transparent_pipeline = Shader::create("../resources/default.vert", "../resources/transparent.frag");

		texture_atlas.loadMetaFile(resources);
		texture_atlas.loadTexture();

		BlockGraphics::loadMetaFile(resources, texture_atlas);

        Block::initBlocks();
        Block::registerBlocks(block_pallete);

        Biome::registerBiomes();

        nm = NetworkManager::create().value();
        networkClient = nm.client();
    }

    void create_frames(uint32_t width, uint32_t height) {
        selection_mesh = std::make_unique<Mesh>();

        for (int i = 0; i < 2; i++) {
            glCreateBuffers(1, &frames[i].camera_ubo);
            glNamedBufferStorage(frames[i].camera_ubo, sizeof(CameraConstants), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
            frames[i].camera_ptr = glMapNamedBufferRange(frames[i].camera_ubo, 0, sizeof(CameraConstants), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

            glCreateTextures(GL_TEXTURE_2D, 1, &frames[i].color_attachment);
            glTextureStorage2D(frames[i].color_attachment, 1, GL_RGB8, width, height);
            glTextureParameteri(frames[i].color_attachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(frames[i].color_attachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glCreateRenderbuffers(1, &frames[i].depth_attachment);
            glNamedRenderbufferStorage(frames[i].depth_attachment, GL_DEPTH24_STENCIL8, width, height);

            glCreateFramebuffers(1, &frames[i].framebuffer);
            glNamedFramebufferTexture(frames[i].framebuffer, GL_COLOR_ATTACHMENT0, frames[i].color_attachment, 0);
            glNamedFramebufferRenderbuffer(frames[i].framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frames[i].depth_attachment);

            if(glCheckNamedFramebufferStatus(frames[i].framebuffer, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                fmt::print("ERROR::FRAMEBUFFER:: Framebuffer is not complete!: {}\n", glGetError());
            }
        }
    }

    void create_imgui() {
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

//        	if (event.type == sf::Event::LostFocus) {
////				window.setMouseCursorVisible(true);
//			} else if (event.type == sf::Event::GainedFocus) {
////        		window.setMouseCursorVisible(false);
//        	} else if (event.type == sf::Event::MouseMoved) {
//
//        	} else
            if (event.type == SDL_QUIT) {
                running = false;
//                window.close();
            }
        }
    }

	void update_player_input(float dt) {
        if (cooldown > 0) {
            cooldown -= 1;
        }

        glm::ivec2 display_size;
        SDL_GetWindowSize(window, &display_size.x, &display_size.y);

        glm::ivec2 mouse_center{display_size.x / 2, display_size.y / 2};
		glm::ivec2 mouse_position;
        SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
		const auto mouse_delta = mouse_position - mouse_center;
        SDL_WarpMouseInWindow(window, mouse_center.x, mouse_center.y);

		rotate_camera(transform, mouse_delta, dt);

        const auto topBlock = clientWorld->getBlock(transform.position.x, transform.position.y + 1, transform.position.z);

		transform.position += calc_free_camera_velocity(input, transform, dt);

		RayTraceContext ray_trace_context {
			.position = transform.position + glm::vec3(0, 1.68, 0),
			.direction = transform.forward()
		};

		rayTraceResult = rayTraceBlocks(*clientWorld, ray_trace_context);
//        if (cooldown == 0 && rayTraceResult.has_value()) {
//            std::set<int64> positions{};
//            if (input.IsMouseButtonPressed(Input::MouseButton::Left)) {
//                cooldown = 10;
//
//                const auto pos = rayTraceResult->pos;
//
//                clientWorld.setData(pos, BlockData{BlockID::AIR, 0});
//
//                for (int x = pos.x - 1; x <= pos.x + 1; x++) {
//                    for (int z = pos.z - 1; z <= pos.z + 1; z++) {
//                        positions.emplace(ChunkPos::asLong(x >> 4, z >> 4));
//                    }
//                }
//            } else if (input.IsMouseButtonPressed(Input::MouseButton::Right)) {
//                cooldown = 10;
//
//                const auto pos = rayTraceResult->pos + rayTraceResult->dir;
//
//                clientWorld.setData(pos, BlockData{block_pallete.getId("water"), 0});
//
////                clientWorld.setData(pos, {Block::water, 0});
//                clientWorld.liquids.emplace(pos);
//
//                for (int x = pos.x - 1; x <= pos.x + 1; x++) {
//                    for (int z = pos.z - 1; z <= pos.z + 1; z++) {
//                        positions.emplace(ChunkPos::asLong(x >> 4, z >> 4));
//                    }
//                }
//            }
//
//            for (auto position : positions) {
//                clientWorld.provideChunk(position)->is_dirty = true;
//            }
//		}
    }

    void setup_camera() {
        const auto projection_matrix = camera.getProjection();
        const auto transform_matrix = transform.getTransformMatrix(glm::vec3(0, 1.68, 0));
        const auto camera_matrix = projection_matrix * transform_matrix;

        CameraConstants camera_constants{
                .transform = camera_matrix,
                .position = transform.position
        };

        std::memcpy(frames[frameIndex].camera_ptr, &camera_constants, sizeof(CameraConstants));
    }

    auto create_render_cache(int32 chunk_x, int32 chunk_z) -> std::optional<ChunkRenderCache> {
        ChunkRenderCache cache{chunk_x, chunk_z};

        usize i = 0;
        for (int32 z = chunk_z - 1; z <= chunk_z + 1; z++) {
            for (int32 x = chunk_x - 1; x <= chunk_x + 1; x++) {
                auto chunk = clientWorld->getChunk(x, z);
                if (chunk == nullptr) {
                    return std::nullopt;
                }
                cache.chunks[i++] = chunk;
            }
        }

        return cache;
    }

    void setup_terrain() {
        const auto center_x = static_cast<int32_t>(transform.position.x) >> 4;
        const auto center_z = static_cast<int32_t>(transform.position.z) >> 4;

        if (last_center_x != center_x || last_center_z != center_z) {
            last_center_x = center_x;
            last_center_z = center_z;

            clientWorld->provider->chunkArray.setCenter(center_x, center_z);

            auto chunkPos = ChunkPos::from(center_x, center_z);
            write(networkClient.fd, &chunkPos, sizeof(ChunkPos));
        }

        chunkToRenders.clear();

        for (int32 chunk_x = center_x - 8; chunk_x <= center_x + 8; chunk_x++) {
            for (int32 chunk_z = center_z - 8; chunk_z <= center_z + 8; chunk_z++) {
                auto chunk = clientWorld->getChunk(chunk_x, chunk_z);

                if (chunk != nullptr) {
                    if (chunk->is_dirty) {
                        chunk->is_dirty = false;

                        auto renderCache = create_render_cache(chunk_x, chunk_z);
                        if (renderCache.has_value()) {
                            renderBlocks(chunk->rb, *renderCache);
                            chunk->needUpdate = true;
                        }
                    }

//                    fmt::print("render chunk at {}, {}\n", chunk_x, chunk_z);
                    if (chunk->needUpdate) {
                        chunk->needUpdate = false;
                        chunk->updateMesh();
                    }

                    if (chunk->mesh) {
                        chunkToRenders.emplace_back(chunk);
                    }
                }
            }
        }
    }

	void render_terrain() {
        const auto topBlock = clientWorld->getBlock(transform.position.x, std::floor(transform.position.y + 1.68), transform.position.z);
        const bool is_liquid = topBlock->renderType == RenderType::Liquid;

        std::array<float, 4> color{0, 0.68, 1.0, 1};

        glm::vec2 fog_offset{9, 13};
        if (is_liquid) {
            color = {0.27, 0.68, 0.96, 1};
            fog_offset = glm::vec2{0, 5 };
        }

		glClearNamedFramebufferfv(frames[frameIndex].framebuffer, GL_COLOR, 0, color.data());
		glClearNamedFramebufferfi(frames[frameIndex].framebuffer, GL_DEPTH_STENCIL, 0, 1, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, frames[frameIndex].framebuffer);

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, frames[frameIndex].camera_ubo);

        glBindTexture(GL_TEXTURE_2D, texture_atlas.texture);
		glActiveTexture(GL_TEXTURE0);

        glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
		glDepthRange(0.01, 1.0);

        glUseProgram(opaque_pipeline);
        glUniform3fv(0, 1, color.data());
        glUniform2f(4, fog_offset.x, fog_offset.y);
		renderLayers(RenderLayer::Opaque);

        glUseProgram(cutout_pipeline);
        glUniform3fv(0, 1, color.data());
        glUniform2f(4, fog_offset.x, fog_offset.y);
		renderLayers(RenderLayer::Cutout);

		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		glUseProgram(transparent_pipeline);
        glUniform3fv(0, 1, color.data());
        glUniform2f(4, fog_offset.x, fog_offset.y);
		renderLayers(RenderLayer::Transparent);

		if (rayTraceResult.has_value()) {
			const auto pos = rayTraceResult->pos;

			SimpleVBuffer buf{};
			buf.quad(0, 1, 1, 2, 2, 3, 3, 0);
			buf.vertex(pos.x + 0, pos.y + 0, pos.z + 0, 0, 0, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 0, pos.y + 1, pos.z + 0, 0, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 1, pos.y + 1, pos.z + 0, 1, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 1, pos.y + 0, pos.z + 0, 1, 0, 0, 0, 0, 0xFF);

			buf.quad(0, 1, 1, 2, 2, 3, 3, 0);
			buf.vertex(pos.x + 1, pos.y + 0, pos.z + 0, 0, 0, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 1, pos.y + 1, pos.z + 0, 0, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 1, pos.y + 1, pos.z + 1, 1, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 1, pos.y + 0, pos.z + 1, 1, 0, 0, 0, 0, 0xFF);

			buf.quad(0, 1, 1, 2, 2, 3, 3, 0);
			buf.vertex(pos.x + 1, pos.y + 0, pos.z + 1, 0, 0, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 1, pos.y + 1, pos.z + 1, 0, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 0, pos.y + 1, pos.z + 1, 1, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 0, pos.y + 0, pos.z + 1, 1, 0, 0, 0, 0, 0xFF);

			buf.quad(0, 1, 1, 2, 2, 3, 3, 0);
			buf.vertex(pos.x + 0, pos.y + 0, pos.z + 1, 0, 0, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 0, pos.y + 1, pos.z + 1, 0, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 0, pos.y + 1, pos.z + 0, 1, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos.x + 0, pos.y + 0, pos.z + 0, 1, 0, 0, 0, 0, 0xFF);

			selection_mesh->SetIndices(buf.indices);
			selection_mesh->SetVertices(buf.vertices);

			glUseProgram(simple_pipeline);

			glDisable(GL_BLEND);
			glDepthRange(0, 1.0);
			glBindVertexArray(selection_mesh->vao);
			glDrawElements(GL_LINES, selection_mesh->index_count, GL_UNSIGNED_INT, nullptr);
		}

        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
	}

    void run() {
        using namespace std::chrono_literals;

        clientWorld = std::make_unique<ClientWorld>();
        serverWorld = std::make_unique<ServerWorld>(nm.server());

        glm::ivec2 display_size;
        SDL_GetWindowSize(window, &display_size.x, &display_size.y);
        SDL_WarpMouseInWindow(window, display_size.x / 2, display_size.y / 2);

		camera.setSize(display_size.x, display_size.y);

        {
            const auto center_x = static_cast<int32_t>(transform.position.x) >> 4;
            const auto center_z = static_cast<int32_t>(transform.position.z) >> 4;

            last_center_x = center_x;
            last_center_z = center_z;

            clientWorld->provider->chunkArray.setCenter(center_x, center_z);

            auto chunkPos = ChunkPos::from(center_x, center_z);
            write(networkClient.fd, &chunkPos, sizeof(ChunkPos));
        }

        double frameTime = 0;
        int frameCount = 0;
        int FPS = 0;

        // todo: game loop

        auto startTime = std::chrono::high_resolution_clock::now();
        while (handleEvents(), running) {
            auto time = std::chrono::high_resolution_clock::now();
            auto dt = std::chrono::duration<double>(time - startTime).count();
            frameTime += dt;
            frameCount += 1;

            if (frameTime > 1) {
                FPS = frameCount;

                frameTime -= 1;
                frameCount = 0;
            }

            startTime = time;

            input.update();
            update_player_input(dt);

            ClientPacket packet{};
            while (true) {
                int ret = read(networkClient.fd, &packet, sizeof(ClientPacket));
                if (ret > 0) {
                    switch (packet.type) {
                        case ClientPacketType::LoadChunk:
                            clientWorld->loadChunk(packet.chunk_x, packet.chunk_z, packet.chunk);
                            break;
                        case ClientPacketType::UnloadChunk:
                            clientWorld->unloadChunk(packet.chunk_x, packet.chunk_z);
                            break;
                    }
                } else {
                    break;
                }
            }

            setup_camera();
            setup_terrain();
            render_terrain();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(window);
            ImGui::NewFrame();

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(300, 150));
            ImGui::Begin("Debug panel", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings);
            ImGui::Text("FPS: %d", FPS);
            ImGui::Text("Position: %.2f, %.2f, %.2f", transform.position.x, transform.position.y, transform.position.z);
            ImGui::Text("Server chunks: %d", static_cast<int>(serverWorld->chunks.size()));
            ImGui::Text("Client chunks: %d", clientWorld->provider->chunkArray.getLoaded());
            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glBlitNamedFramebuffer(frames[frameIndex].framebuffer, 0, 0, 0, 800, 600, 0, 0, 800, 600, GL_COLOR_BUFFER_BIT, GL_NEAREST);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            SDL_GL_SwapWindow(window);

            frameIndex = (frameIndex + 1) % 2;
        }
    }

	void renderLayers(RenderLayer layer) {
		for (auto chunk : chunkToRenders) {
		    // todo: sometimes crash here
			glBindVertexArray(chunk->mesh->vao);

			auto [index_offset, index_count] = chunk->layers[(int) layer];

			if (index_count != 0) {
				glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, (void*) (index_offset * sizeof(int32)));
			}
		}
	}

private:
    static void rotate_camera(Transform& transform, glm::ivec2 mouse_delta, float dt) {
        if (mouse_delta.x != 0 || mouse_delta.y != 0) {
            float d4 = 0.5f * 0.6F + 0.2F;
            float d5 = d4 * d4 * d4 * 8.0f;

            transform.yaw = transform.yaw - mouse_delta.x * d5 * dt * 9.0f;
            transform.pitch = glm::clamp(transform.pitch - mouse_delta.y * d5 * dt * 9.0f, -90.0f, 90.0f);
        }
    }

    static auto calc_free_camera_velocity(Input& input, Transform& transform, float dt) -> glm::vec3 {
        glm::vec3 velocity{0, 0, 0};

        auto forward = transform.forward();
        auto right = transform.right();

        float moveSpeed = 100.f;
        if (input.IsKeyPressed(Input::Key::Up)) {
            velocity += forward * dt * moveSpeed;
        }
        if (input.IsKeyPressed(Input::Key::Down)) {
            velocity -= forward * dt * moveSpeed;
        }
        if (input.IsKeyPressed(Input::Key::Left)) {
            velocity -= right * dt * moveSpeed;
        }
        if (input.IsKeyPressed(Input::Key::Right)) {
            velocity += right * dt * moveSpeed;
        }
        return velocity;
    }
};

auto main() -> int32 {
    App app{"Minecraft", 800, 600};
    app.run();
    return 0;
}