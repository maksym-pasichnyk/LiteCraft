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
#include <valarray>
#include <fmt/format.h>

#include "input.hpp"
#include "camera.hpp"
#include "transform.hpp"
#include "Block.hpp"
#include "Chunk.hpp"
#include "src/util/math/ChunkPos.hpp"
#include "BlockReader.hpp"
#include "TextureAtlas.hpp"
#include "raytrace.hpp"
#include "worldgenregion.hpp"
#include "ChunkRenderCache.h"
#include "world/gen/NoiseChunkGenerator.hpp"

#include <SDL2/SDL.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

extern void renderBlocks(RenderBuffer& rb, BlockTable& pallete, ChunkRenderCache& blocks);

std::map<std::string, BlockGraphics> tile_datas;

struct LiquidNode {
    glm::ivec3 pos;
    int data;
};

BlockTable global_pallete{};

struct ChunkArray {
private:
    int viewDistance = -1;
    int sideLength = -1;
    int loaded = 0;
    std::atomic_int centerX{0};
    std::atomic_int centerZ{0};
    std::vector<std::atomic<Chunk*>> chunks;

    static_assert(std::atomic<Chunk*>::is_always_lock_free);

public:
    void setViewDistance(int viewDistanceIn) {
        viewDistance = viewDistanceIn;
        sideLength = viewDistance * 2 + 1;
        chunks = std::vector<std::atomic<Chunk*>>(sideLength * sideLength);
    }

    auto getLoaded() const -> int {
        return loaded;
    }

    auto get(int32_t i) const -> Chunk* {
        return chunks.at(i).load();
    }

    auto set(int32_t i, Chunk* chunk) {
        auto old_chunk = chunks.at(i).exchange(chunk);

        if (old_chunk) {
            loaded -= 1;
        }

        if (chunk) {
            loaded += 1;
        }
    }

    auto getIndex(int32_t x, int32_t z) const -> int32_t {
        return floorMod(z, sideLength) * sideLength + floorMod(x, sideLength);
    }

    auto inView(int x, int z) const -> bool {
        return std::abs(x - centerX) <= viewDistance && std::abs(z - centerZ) <= viewDistance;
    }

    void setCenter(int32_t x, int32_t z) {
        centerX = x;
        centerZ = z;
    }
private:

    static auto floorMod(int32_t x, int32_t y) -> int32_t {
        return ((x % y) + y) % y;
    }
};

struct ClientWorld {
    ChunkArray chunkArray;
    std::queue<LiquidNode> liquids{};

    ClientWorld() {
        chunkArray.setViewDistance(8);
    }

	void loadChunk(int32 x, int32 z, Chunk* chunk) {
        if (chunkArray.inView(x, z)) {
            chunkArray.set(chunkArray.getIndex(x, z), chunk);
        }

        for (int chunk_x = x - 1; chunk_x <= x + 1; ++chunk_x) {
            for (int chunk_z = z - 1; chunk_z <= z + 1; ++chunk_z) {
                auto chunk = getChunk(chunk_x, chunk_z);
                if (chunk) chunk->is_dirty = true;
            }
        }
	}

	void unloadChunk(int32 x, int32 z) {
        if (chunkArray.inView(x, z)) {
            chunkArray.set(chunkArray.getIndex(x, z), nullptr);
        }
	}

	auto getChunk(int32 x, int32 z) const -> Chunk* {
        if (chunkArray.inView(x, z)) {
            return chunkArray.get(chunkArray.getIndex(x, z));
        }
        return nullptr;
	}

    auto getData(glm::ivec3 pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

	auto getData(int32 x, int32 y, int32 z) const -> BlockData {
		if (y >= 0 && y < 256) {
			if (auto chunk = getChunk(x >> 4, z >> 4)) {
				return chunk->getData(x, y, z);
			}
		}
		return {};
	}

    void setData(glm::ivec3 pos, BlockData blockData) {
        setData(pos.x, pos.y, pos.z, blockData);
    }

	void setData(int32 x, int32 y, int32 z, BlockData blockData) {
		if (y >= 0 && y < 256) {
			if (auto chunk = getChunk(x >> 4, z >> 4)) {
                chunk->setData(x, y, z, blockData);
			}
		}
    }

    auto getBlock(glm::ivec3 pos) const -> Block* {
        return getBlock(pos.x, pos.y, pos.z);
    }

    auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
        return Block::id_to_block[(int) getData(x, y, z).id];
    }

    auto getSkyLight(int32_t x, int32_t y, int32_t z) const -> int32 {
        if (y >= 0 && y < 256) {
            if (auto chunk = getChunk(x >> 4, z >> 4)) {
                return chunk->getSkyLight(x, y, z);
            }
        }
        return 0;
	}
};

ClientWorld client_world{};

struct World {
    NoiseChunkGenerator generator{global_pallete};
//    WorldLightManager lightManager;

    std::atomic<ChunkPos> player_position{ChunkPos::from(100, 100)};
    std::vector<std::jthread> workers{};
    std::map<int64, std::unique_ptr<Chunk>> chunks{};

    int64_t seed;

    World() {
        workers.emplace_back(std::bind_front(&World::runWorker, this));
    }

    ~World() {
    	workers.clear();
    }

    static auto getChunkDistance(ChunkPos chunkPos, int chunk_x, int chunk_z) -> int {
        return std::max(std::abs(chunkPos.x - chunk_x), std::abs(chunkPos.z - chunk_z));
    }

    void setChunkLoadedAtClient(int chunk_x, int chunk_z, bool wasLoaded, bool needLoad) {
        if (wasLoaded && !needLoad) {
            client_world.unloadChunk(chunk_x, chunk_z);
        } else if (needLoad && !wasLoaded) {
            auto chunk = getChunk(chunk_x, chunk_z, ChunkState::Full);
            client_world.loadChunk(chunk_x, chunk_z, chunk);
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

        while (!token.stop_requested()) {
            auto player_pos = player_position.load();
            if (last_player_position != player_pos) {
                updatePlayerPosition(player_pos, last_player_position);
                last_player_position = player_pos;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    auto getChunksInRadius(int32 radius, int32 chunk_x, int32 chunk_z, ChunkState state) -> std::vector<Chunk*> {
        if (radius == -1) return {};

        const usize count = radius * 2 + 1;
        std::vector<Chunk*> ret{count * count};

        usize i = 0;
        for (int32 z = chunk_z - radius; z <= chunk_z + radius; z++) {
            for (int32 x = chunk_x - radius; x <= chunk_x + radius; x++) {
                ret.at(i++) = getChunk(x, z, state);
            }
        }

        return std::move(ret);
    }

    auto findChunk(int32 chunk_x, int32 chunk_z) -> Chunk* {
        const auto pos = ChunkPos::from(chunk_x, chunk_z);
        auto it = chunks.find(pos.asLong());
        if (it == chunks.end()) {
            it = chunks.emplace(pos.asLong(), std::make_unique<Chunk>(pos)).first;
        }
        return it->second.get();
    }

    auto findChunk(int32 chunk_x, int32 chunk_z, ChunkState state) -> Chunk* {
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
                return 0;
            case ChunkState::Full:
                return 0;
        }
        return -1;
    }

    auto getChunk(int32 chunk_x, int32 chunk_z, ChunkState state = ChunkState::Full) -> Chunk* {
        auto chunk = findChunk(chunk_x, chunk_z);

        for (int i = (int) chunk->state + 1; i <= (int) state; i++) {
            const auto parent_state = (ChunkState)((int)i - 1);
            const auto range = getTaskRange((ChunkState) i);
            auto chunksInRadius = getChunksInRadius(range, chunk_x, chunk_z, parent_state);

            switch ((ChunkState) i) {
                case ChunkState::Empty: break;
                case ChunkState::StructureStart: {
//                    WorldGenRegion region{chunksInRadius, range, chunk_x, chunk_z, seed};
//                    generator.generateStructures(region, chunk);
                    break;
                }
                case ChunkState::StructureReferences: {
//                    WorldGenRegion region{chunksInRadius, range, chunk_x, chunk_z, seed};
//                    generator.getStructureReferences(region, chunk);
                    break;
                }
                case ChunkState::Noise:
                    generator.generateTerrain(*chunk, global_pallete);
                    break;
                case ChunkState::Surface: {
                    WorldGenRegion region{chunksInRadius, range, chunk_x, chunk_z, seed};
                    generator.generateSurface(region, *chunk, global_pallete);
                    break;
                }
                case ChunkState::Features: {
//                    WorldGenRegion region{chunksInRadius, range, chunk_x, chunk_z, seed};
//                    generator.generateFeatures(region, chunk, global_pallete);
                    break;
                }
                case ChunkState::Light: {
//                    WorldGenRegion region{chunksInRadius, range, chunk_x, chunk_z, seed};
//                    lightManager.calculateLight(region, chunk_x * 16, chunk_z * 16);
                    break;
                }
                case ChunkState::Full: {
//                    WorldGenRegion region{chunksInRadius, 1, chunk_x, chunk_z, seed};
//                    chunk->needRender = true;
                    break;
                }
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

struct Clock {

};

struct Shader {
    static std::string source(const std::string &path) {
        std::ifstream file(path, std::ios::in);
        std::stringstream stream{};
        stream << file.rdbuf();
        file.close();
        return stream.str();
    }

    static bool validate(const GLuint program) {
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            std::basic_string<GLchar> infoLog{};
            infoLog.resize(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            fmt::print("{}\n", infoLog);
            return false;
        }
        return true;
    }

    static GLuint compile(const std::string &source, GLenum type) {
        auto data = source.data();
        auto size = GLint(source.size());

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &data, &size);
        glCompileShader(shader);

        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            std::basic_string<GLchar> infoLog{};
            infoLog.resize(length);
            glGetShaderInfoLog(shader, length, &length, infoLog.data());
            fmt::print("{}\n", infoLog);
        }

	    GLint status = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    static GLuint create(const std::string &vertex_path, const std::string &fragment_path) {
        auto vertex = compile(source(vertex_path), GL_VERTEX_SHADER);
        auto fragment = compile(source(fragment_path), GL_FRAGMENT_SHADER);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            std::basic_string<GLchar> infoLog{};
            infoLog.resize(length);
            glGetProgramInfoLog(program, length, &length, &infoLog[0]);
            fmt::print("{}\n", infoLog);
        }

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            glDeleteProgram(program);
            return 0;
        }
        return program;
    }
};

struct RenderFrame {
    GLuint camera_ubo;
    void* camera_ptr;
};

struct App {
    bool running = true;

    SDL_Window* window;
    SDL_GLContext context;
    ResourceManager resources{};

    Input input{};
    Clock clock{};
    Camera camera{};
    Transform transform {
        .yaw = 0,
        .pitch = 0,
        .position = {637, 71, 220}
    };
	glm::vec3 velocity{0, 0, 0};
	int cooldown = 0;

    GLuint simple_pipeline;
    GLuint opaque_pipeline;
    GLuint cutout_pipeline;
    GLuint transparent_pipeline;

    TextureAtlas texture_atlas;

    std::vector<Chunk*> chunkToRenders;

    std::unique_ptr<Mesh> selection_mesh;
    std::unique_ptr<World> world;

    std::optional<RayTraceResult> rayTraceResult{std::nullopt};

    int frameIndex = 0;

    std::array<RenderFrame, 2> frames;

    App(const char* title, uint32 width, uint32 height) {
		stbi_set_flip_vertically_on_load(true);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        context = SDL_GL_CreateContext(window);

        SDL_SetWindowResizable(window, SDL_TRUE);

        glewInit();

        create_frames();
        create_imgui();

		resources.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla"));

        simple_pipeline = Shader::create("../resources/simple.vert", "../resources/simple.frag");
        opaque_pipeline = Shader::create("../resources/default.vert", "../resources/default.frag");
		cutout_pipeline = Shader::create("../resources/default.vert", "../resources/cutout.frag");
		transparent_pipeline = Shader::create("../resources/default.vert", "../resources/transparent.frag");

		texture_atlas.loadMetaFile(resources);
		texture_atlas.loadTexture();

		loadBlocks();

        Block::initBlocks();
        Block::registerBlocks(global_pallete);

		world = std::make_unique<World>();
    }

    void create_frames() {
        selection_mesh = std::make_unique<Mesh>();

        for (int i = 0; i < 2; i++) {
            glCreateBuffers(1, &frames[i].camera_ubo);
            glNamedBufferStorage(frames[i].camera_ubo, sizeof(CameraConstants), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
            frames[i].camera_ptr = glMapNamedBufferRange(frames[i].camera_ubo, 0, sizeof(CameraConstants), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        }
    }

    void create_imgui() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init("#version 150");
    }

	void loadBlocks() {
		auto blocks = Json::parse(resources.loadFile("blocks.json").value(), nullptr, true, true);

		using namespace std::string_view_literals;
		for (auto& [name, data] : blocks.items()) {
			if (name == "format_version"sv) continue;

			BlockGraphics tile_data{};

			if (data.contains("isotropic")) {
				auto& isotropic = data["isotropic"];
			}

			if (data.contains("textures")) {
				auto& textures = data["textures"];
				if (textures.is_object()) {
					tile_data.topTexture = texture_atlas.getTextureItem(textures["up"].get<std::string>());
					tile_data.bottomTexture = texture_atlas.getTextureItem(textures["down"].get<std::string>());

					if (textures.contains("side")) {
						auto sideTexture = texture_atlas.getTextureItem(textures["side"].get<std::string>());
						tile_data.southTexture = sideTexture;
						tile_data.northTexture = sideTexture;
						tile_data.eastTexture = sideTexture;
						tile_data.westTexture = sideTexture;
					} else {
						tile_data.southTexture = texture_atlas.getTextureItem(textures["south"].get<std::string>());
						tile_data.northTexture = texture_atlas.getTextureItem(textures["north"].get<std::string>());
						tile_data.eastTexture = texture_atlas.getTextureItem(textures["east"].get<std::string>());
						tile_data.westTexture = texture_atlas.getTextureItem(textures["west"].get<std::string>());
					}
				} else {
					auto texture = texture_atlas.getTextureItem(textures.get<std::string>());

					tile_data.topTexture = texture;
					tile_data.bottomTexture = texture;
					tile_data.southTexture = texture;
					tile_data.northTexture = texture;
					tile_data.eastTexture = texture;
					tile_data.westTexture = texture;
				}
			}

			if (data.contains("carried_textures")) {
				auto& carried_textures = data["carried_textures"];
			}

			if (data.contains("sound")) {
				auto& carried_textures = data["sound"];
			}

			if (data.contains("brightness_gamma")) {
				auto& carried_textures = data["brightness_gamma"];
			}

			tile_datas.emplace(name, tile_data);
		}
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
		auto mouse_delta = mouse_position - mouse_center;
        SDL_WarpMouseInWindow(window, mouse_center.x, mouse_center.y);

		rotate_camera(transform, mouse_delta, dt);

        const auto topBlock = client_world.getBlock(transform.position.x, transform.position.y + 1, transform.position.z);
        const bool is_liquid = topBlock->renderType == RenderType::Liquid;

		transform.position += calc_free_camera_velocity(input, transform, dt);

		RayTraceContext ray_trace_context {
			.position = transform.position + glm::vec3(0, 1.68, 0),
			.direction = transform.forward()
		};

		rayTraceResult = rayTraceBlocks(client_world, ray_trace_context);
//        if (cooldown == 0 && rayTraceResult.has_value()) {
//            std::set<int64> positions{};
//            if (input.IsMouseButtonPressed(Input::MouseButton::Left)) {
//                cooldown = 10;
//
//                const auto pos = rayTraceResult->pos;
//
//                client_world.setData(pos, BlockData{BlockID::AIR, 0});
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
//                client_world.setData(pos, BlockData{global_pallete.getId("water"), 0});
//
////                client_world.setData(pos, {Block::water, 0});
//                client_world.liquids.emplace(pos);
//
//                for (int x = pos.x - 1; x <= pos.x + 1; x++) {
//                    for (int z = pos.z - 1; z <= pos.z + 1; z++) {
//                        positions.emplace(ChunkPos::asLong(x >> 4, z >> 4));
//                    }
//                }
//            }
//
//            for (auto position : positions) {
//                client_world.getChunk(position)->is_dirty = true;
//            }
//		}
    }

    void setup_camera() {
        auto projection_matrix = camera.getProjection();
        auto transform_matrix = transform.getViewMatrix();
        auto camera_matrix = projection_matrix * transform_matrix;

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
                auto chunk = client_world.getChunk(x, z);
                if (chunk == nullptr) {
                    return std::nullopt;
                }
                cache.chunks[i++] = chunk;
            }
        }

        return cache;
    }

    void setup_terrain() {
        int32 center_x = (int32) transform.position.x >> 4;
        int32 center_z = (int32) transform.position.z >> 4;
        client_world.chunkArray.setCenter(center_x, center_z);
        world->player_position = {center_x, center_z};

        chunkToRenders.clear();

        for (int32 chunk_x = center_x - 8; chunk_x <= center_x + 8; chunk_x++) {
            for (int32 chunk_z = center_z - 8; chunk_z <= center_z + 8; chunk_z++) {
                auto chunk = client_world.getChunk(chunk_x, chunk_z);

                if (chunk != nullptr) {
                    if (chunk->is_dirty) {
                        chunk->is_dirty = false;

                        auto renderCache = create_render_cache(chunk_x, chunk_z);
                        if (renderCache.has_value()) {
                            renderBlocks(chunk->rb, global_pallete, *renderCache);
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
        const auto topBlock = client_world.getBlock(transform.position.x, std::floor(transform.position.y + 1.68), transform.position.z);
        const bool is_liquid = topBlock->renderType == RenderType::Liquid;

        std::array<float, 4> color{0, 0.68, 1.0, 1};

        glm::vec2 fog_offset{9, 13};
        if (is_liquid) {
            color = {0.27, 0.68, 0.96, 1};
            fog_offset = glm::vec2{0, 5 };
        }

		glClearNamedFramebufferfv(0, GL_COLOR, 0, color.data());
		glClearNamedFramebufferfi(0, GL_DEPTH_STENCIL, 0, 1, 0);

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

        int32 center_x = (int32) transform.position.x >> 4;
        int32 center_z = (int32) transform.position.z >> 4;
        client_world.chunkArray.setCenter(center_x, center_z);

        world = std::make_unique<World>();

        glm::ivec2 display_size;
        SDL_GetWindowSize(window, &display_size.x, &display_size.y);
        SDL_WarpMouseInWindow(window, display_size.x / 2, display_size.y / 2);

		camera.setSize(display_size.x, display_size.y);

        std::this_thread::sleep_for(1000ms);

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

            setup_camera();
            setup_terrain();
            render_terrain();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(window);
            ImGui::NewFrame();

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(300, 150));
            ImGui::Begin("Debug panel", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
            ImGui::Text("FPS: %d", FPS);
            ImGui::Text("Position: %.2f, %.2f, %.2f", transform.position.x, transform.position.y, transform.position.z);
            ImGui::Text("Server chunks: %d", static_cast<int>(world->chunks.size()));
            ImGui::Text("Client chunks: %d", client_world.chunkArray.getLoaded());
            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            SDL_GL_SwapWindow(window);

            frameIndex = (frameIndex + 1) % 2;
        }
    }

	void renderLayers(RenderLayer layer) {
		for (auto chunk : chunkToRenders) {
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