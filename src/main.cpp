#include <GL/glew.h>
#include <stdint.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <random>
#include <set>

#include "input.hpp"
#include "camera.hpp"
#include "transform.hpp"
#include "tile.hpp"
#include "chunk.hpp"
#include "chunk_pos.hpp"
#include "block_reader.hpp"
#include "texture_atlas.hpp"
#include "random.hpp"
#include "raytrace.hpp"
#include "worldgenregion.hpp"

extern void renderBlocks(RenderBuffer& rb, IBlockReader auto const& blocks);
extern void generateTerrain(Chunk* chunk, int32 chunk_x, int32 chunk_z);
extern void generateTree(Chunk* chunk, int32 x, int32 z, IBlockReader auto& blocks, Random& random);
extern void generateFeatures(Chunk* chunk, IBlockReader auto& blocks, int32 chunk_x, int32 chunk_z, int64 worldSeed);

std::map<std::string, TileData> tile_datas;

struct ClientWorld {
	std::mutex chunk_mutex;
    std::map<int64, Chunk*> chunks{};

	void loadChunk(int64 position, Chunk* chunk) {
		chunk_mutex.lock();
		chunks.insert_or_assign(position, chunk);
		chunk_mutex.unlock();
	}

	void unloadChunk(int64 position) {
		chunk_mutex.lock();
		chunks.erase(position);
		chunk_mutex.unlock();
	}

	auto getChunk(int64 position) -> Chunk* {
		Chunk* chunk{nullptr};
		chunk_mutex.lock();
		auto it = chunks.find(position);
		if (it != chunks.end()) {
			chunk = it->second;
		}
		chunk_mutex.unlock();
		return chunk;
	}

	auto getTile(int32 x, int32 y, int32 z) -> Tile* {
		if (y >= 0 && y < 256) {
			if (auto chunk = getChunk(ChunkPos::asLong(x >> 4, z >> 4))) {
				return chunk->getTile(x, y, z)?:Tile::air;
			}
		}
		return Tile::air;
	}

	void setTile(int32 x, int32 y, int32 z, Tile* tile) {
		if (y >= 0 && y < 256) {
			if (auto chunk = getChunk(ChunkPos::asLong(x >> 4, z >> 4))) {
				chunk->setTile(x, y, z, tile);
			}
		}
    }
};

ClientWorld client_world{};

struct World {
    std::atomic<ChunkPos> player_position{ChunkPos{100, 100}};
    std::vector<std::jthread> workers{};
    std::map<int64, std::unique_ptr<Chunk>> chunks{};

    World() {
        workers.emplace_back(std::bind_front(&World::runWorker, this));
    }

    ~World() {
    	workers.clear();
    }

    void runWorker(std::stop_token&& token) {
        ChunkPos last_player_position{-9999,-9999 };

        while (!token.stop_requested()) {
            auto player_pos = player_position.load();
            if (last_player_position != player_pos) {
                last_player_position = player_pos;
                loadChunks(player_pos.x, player_pos.z);
            }

            for (auto& [pos, chunk] : chunks) {
				if (chunk->is_dirty) {
                    chunk->is_dirty = false;

					WorldGenRegion<1> region{(int32)(pos & 0xFFFFFFFFLL), (int32) ((pos >> 32) & 0xFFFFFFFF)};
					fillRegion(region, ChunkState::Full);

					renderBlocks(chunk->rb, region);
                    chunk->needUpdate = true;
				}
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    void loadChunks(int32 center_x, int32 center_z) {
        for (int32 chunk_x = center_x - 8; chunk_x <= center_x + 8; chunk_x++) {
            for (int32 chunk_z = center_z - 8; chunk_z <= center_z + 8; chunk_z++) {
				WorldGenRegion<1> region{chunk_x, chunk_z};
				fillRegion(region, ChunkState::Full);

				auto chunk = region.getMainChunk();
                if (chunk->needRender) {
                    chunk->needRender = false;
					renderBlocks(chunk->rb, region);
                    chunk->needUpdate = true;
                }

                client_world.loadChunk(ChunkPos::asLong(chunk_x, chunk_z), chunk);
            }
        }
    }

    template <usize Radius>
    void fillRegion(WorldGenRegion<Radius>& region, ChunkState state) {
    	int32 chunk_x = region.chunk_x;
    	int32 chunk_z = region.chunk_z;

    	int32 radius = (int32) Radius;

		usize i = 0;
		for (int32 z = chunk_z - radius; z <= chunk_z + radius; z++) {
			for (int32 x = chunk_x - radius; x <= chunk_x + radius; x++) {
				region.chunks[i++] = getChunk(x, z, state);
			}
		}
    }

    auto getChunk(int32 chunk_x, int32 chunk_z, ChunkState state = ChunkState::Full) -> Chunk* {
    	if (state == ChunkState::Empty) {
        	auto& chunk = chunks[ChunkPos::asLong(chunk_x, chunk_z)];
        	if (chunk == nullptr) {
				chunk = std::make_unique<Chunk>();
			}
			return chunk.get();
    	}

    	auto parent_state = (ChunkState)((int32)state - 1);

		auto chunk = getChunk(chunk_x, chunk_z, parent_state);
		if (chunk->state == parent_state) {
			switch (state) {
			case ChunkState::Empty:
//				chunk->state = state;
				break;
			case ChunkState::StructureStart:
				chunk->state = state;
				break;
			case ChunkState::StructureReferences: {
				WorldGenRegion<8> region{chunk_x, chunk_z};
				fillRegion(region, parent_state);
				chunk->state = state;
				break;
			}
			case ChunkState::Noise:
				generateTerrain(chunk, chunk_x, chunk_z);
				chunk->state = state;
				break;
			case ChunkState::Features: {
				WorldGenRegion<8> region{chunk_x, chunk_z};
				fillRegion(region, parent_state);
				generateFeatures(chunk, region, chunk_x, chunk_z, 0);
				chunk->state = state;
				break;
			}
			case ChunkState::Light: {
				WorldGenRegion<1> region{chunk_x, chunk_z};
				fillRegion(region, parent_state);
				chunk->state = state;
				break;
			}
			case ChunkState::Full: {
//				WorldGenRegion<0> region{chunk_x, chunk_z};
//				fillRegion(region, parent_state);
				chunk->state = state;
				chunk->needRender = true;
				break;
			}
			}
		}
		return chunk;
    }
};

struct CameraConstants {
	glm::mat4 transform;
	glm::vec3 position;
};


auto check_collide(IBlockReader auto& blocks, float x, float y, float z) -> bool {
	int32_t ix = glm::floor(x);
	int32_t iy = glm::floor(y);
	int32_t iz = glm::floor(z);

	return blocks.getTile(ix, iy, iz)->renderType == RenderType::Block;
}

float check_down_velocity(IBlockReader auto& blocks, glm::vec3 position, float velocity, float half_collider_width = 0.3f) {
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

float check_up_velocity(IBlockReader auto& blocks, glm::vec3 entity_pos, float vel, float half_collider_width = 0.3f, float collider_height = 1.8f) {
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

float check_front_velocity(IBlockReader auto& blocks, glm::vec3 position, float velocity, float half_collider_width = 0.3f, float collider_height = 1.8f) {
	if (check_collide(blocks, position.x, position.y, position.z + half_collider_width + velocity)) {
		return 0;
	}
	if (check_collide(blocks, position.x, position.y + collider_height, position.z + half_collider_width + velocity)) {
		return 0;
	}
	return velocity;
}

float check_back_velocity(IBlockReader auto& blocks, glm::vec3 entity_pos, float vel, float half_collider_width = 0.3f, float collider_height = 1.8f) {
	if (check_collide(blocks, entity_pos.x, entity_pos.y, entity_pos.z - half_collider_width + vel)) {
		return 0;
	}
	if (check_collide(blocks, entity_pos.x, entity_pos.y + collider_height, entity_pos.z - half_collider_width + vel)) {
		return 0;
	}
	return vel;
}

float check_left_velocity(IBlockReader auto& blocks, glm::vec3 entity_pos, float vel, float half_collider_width = 0.3f, float collider_height = 1.8f) {
	if (check_collide(blocks, entity_pos.x - half_collider_width + vel, entity_pos.y, entity_pos.z)) {
		return 0;
	}
	if (check_collide(blocks, entity_pos.x - half_collider_width + vel, entity_pos.y + collider_height, entity_pos.z)) {
		return 0;
	}
	return vel;
}

float check_right_velocity(IBlockReader auto& blocks, glm::vec3 entity_pos, float vel, float half_collider_width = 0.3f, float collider_height = 1.8f) {
	if (check_collide(blocks, entity_pos.x + half_collider_width + vel, entity_pos.y, entity_pos.z)) {
		return 0;
	}
	if (check_collide(blocks, entity_pos.x + half_collider_width + vel, entity_pos.y + collider_height, entity_pos.z)) {
		return 0;
	}
	return vel;
}

struct App {
    sf::Window window{};
    sf::Clock clock{};
    ResourceManager resource_manager{};

    Input input{};
    Camera camera{};
    Transform transform {
        .yaw = 0,
        .pitch = 0,
        .position = {0, 70, 0}
    };
	glm::vec3 velocity{0, 0, 0};
	int cooldown = 0;

	sf::Shader opaque_pipeline;
	sf::Shader cutout_pipeline;
	sf::Shader transparent_pipeline;

    TextureAtlas texture_atlas;

    std::vector<Chunk*> chunkToRenders;

    std::unique_ptr<Mesh> selection_mesh;
    std::unique_ptr<World> world{};

    std::optional<RayTraceResult> rayTraceResult{std::nullopt};

	GLuint ubo;
	void* ubo_ptr{nullptr};

    App(const char* title, uint32 width, uint32 height) {
		stbi_set_flip_vertically_on_load(true);

        window.create(sf::VideoMode(width, height), title, sf::Style::Close, sf::ContextSettings{24, 8});
        window.setFramerateLimit(60);
        window.setActive();

        glewInit();

		resource_manager.addResourcePack(std::make_unique<ResourcePack>("../assets/resource_packs/vanilla"));

		opaque_pipeline.loadFromFile("../resources/default.vert", "../resources/default.frag");
		cutout_pipeline.loadFromFile("../resources/default.vert", "../resources/cutout.frag");
		transparent_pipeline.loadFromFile("../resources/default.vert", "../resources/transparent.frag");

		texture_atlas.loadMetaFile(resource_manager);
		texture_atlas.loadTexture();

		loadBlocks();

		Tile::initTiles();

		world = std::make_unique<World>();


        glCreateBuffers(1, &ubo);
        glNamedBufferStorage(ubo, sizeof(CameraConstants), nullptr, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
        ubo_ptr = glMapNamedBufferRange(ubo, 0, sizeof(CameraConstants), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
    }

	void loadBlocks() {
		auto blocks = Json::parse(resource_manager.loadFile("blocks.json").value(), nullptr, true, true);

		using namespace std::string_view_literals;
		for (auto& [name, data] : blocks.items()) {
			if (name == "format_version"sv) continue;

			TileData tile_data{};

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
        sf::Event event{};
        while (window.pollEvent(event)) {
        	if (event.type == sf::Event::LostFocus) {
				window.setMouseCursorVisible(true);
			} else if (event.type == sf::Event::GainedFocus) {
        		window.setMouseCursorVisible(false);
        	} else if (event.type == sf::Event::MouseMoved) {

        	} else if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

	static void rotate_camera(Transform& transform, sf::Vector2i mouse_delta, float dt) {
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

        float moveSpeed = 10.f;
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

	void update_player_input(float dt) {
		auto display_size = window.getSize();

		sf::Vector2i mouse_center(display_size.x / 2, display_size.y / 2);
		auto mouse_position = sf::Mouse::getPosition(window);
		auto mouse_delta = mouse_position - mouse_center;
		sf::Mouse::setPosition(mouse_center, window);

		rotate_camera(transform, mouse_delta, dt);

		float yaw = glm::radians(transform.yaw);

		float c = glm::cos(yaw);
		float s = glm::sin(yaw);

		velocity.x = 0;
		velocity.z = 0;

		float moveSpeed = 10.f;
		if (input.IsKeyPressed(Input::Key::Up)) {
			velocity += glm::vec3{-s, 0, c} * dt * moveSpeed;
		}
		if (input.IsKeyPressed(Input::Key::Down)) {
			velocity -= glm::vec3{-s, 0, c} * dt * moveSpeed;
		}
		if (input.IsKeyPressed(Input::Key::Left)) {
			velocity -= glm::vec3{c, 0, s} * dt * moveSpeed;
		}
		if (input.IsKeyPressed(Input::Key::Right)) {
			velocity += glm::vec3{c, 0, s} * dt * moveSpeed;
		}

		if (velocity.z > 0) {
			velocity.z = check_front_velocity(client_world, transform.position, velocity.z);
		} else if (velocity.z < 0) {
			velocity.z = check_back_velocity(client_world, transform.position, velocity.z);
		}
		if (velocity.x > 0) {
			velocity.x = check_right_velocity(client_world, transform.position, velocity.x);
		} else if (velocity.x < 0) {
			velocity.x = check_left_velocity(client_world, transform.position, velocity.x);
		}

		bool is_liquid = client_world.getTile(transform.position.x, transform.position.y + 1, transform.position.z)->renderType == RenderType::Liquid;

		if (is_liquid) {
			velocity.y = -2.5 * dt;
		} else {
			velocity.y -= 9.8 * dt * dt;
		}

		if (velocity.y < 0) {
			velocity.y = check_down_velocity(client_world, transform.position, velocity.y);
		}

		if (input.IsKeyPressed(Input::Key::Jump)) {
			if (is_liquid) {
				velocity.y = 2.5 * dt;
			} else if (velocity.y == 0) {
				velocity.y = 5 * dt;
			}
		}

		if (velocity.y > 0) {
			velocity.y = check_up_velocity(client_world, transform.position, velocity.y);
		}

		transform.position += velocity;

		RayTraceContext ray_trace_context {
			.position = transform.position + glm::vec3(0, 1.68, 0),
			.direction = transform.forward()
		};

		rayTraceResult = rayTraceBlocks(client_world, ray_trace_context);
		if (cooldown == 0 && input.IsMouseButtonPressed(Input::MouseButton::Left)) {
			if (rayTraceResult.has_value()) {
				cooldown = 10;
				auto [pos_x, pos_y, pos_z] = rayTraceResult->pos;

				client_world.setTile(pos_x, pos_y, pos_z, Tile::air);

				std::set<int64> positions{};
				for (int x = pos_x - 1; x <= pos_x + 1; x++) {
					for (int z = pos_z - 1; z <= pos_z + 1; z++) {
						positions.emplace(ChunkPos::asLong(x >> 4, z >> 4));
					}
				}

				for (auto position : positions) {
					client_world.getChunk(position)->is_dirty = true;
				}
			}
		}
    }

	void render_terrain() {
		int32 center_x = (int32) transform.position.x >> 4;
		int32 center_z = (int32) transform.position.z >> 4;

		world->player_position = {center_x, center_z};

		auto projection_matrix = camera.getProjection();
		auto transform_matrix = transform.getViewMatrix();
		auto camera_matrix = projection_matrix * transform_matrix;

		CameraConstants camera_constants{
				.transform = camera_matrix,
				.position = transform.position
		};

		std::memcpy(ubo_ptr, &camera_constants, sizeof(CameraConstants));

		auto display_size = window.getSize();
		glViewport(0, 0, display_size.x, display_size.y);

		float color[4]{0, 0.68, 1.0, 1};
		glClearNamedFramebufferfv(0, GL_COLOR, 0, color);
		glClearNamedFramebufferfi(0, GL_DEPTH_STENCIL, 0, 1, 0);

		glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

		sf::Texture::bind(&texture_atlas.texture);
		glActiveTexture(GL_TEXTURE0);

		chunkToRenders.clear();

		for (int32 chunk_x = center_x - 8; chunk_x <= center_x + 8; chunk_x++) {
			for (int32 chunk_z = center_z - 8; chunk_z <= center_z + 8; chunk_z++) {
				auto chunk = client_world.getChunk(ChunkPos::asLong(chunk_x, chunk_z));

				if (chunk != nullptr) {
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

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
		glDepthRange(0.01, 1.0);

		sf::Shader::bind(&opaque_pipeline);
		renderLayers(RenderLayer::Opaque);

		sf::Shader::bind(&cutout_pipeline);
		renderLayers(RenderLayer::Cutout);

		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		sf::Shader::bind(&transparent_pipeline);
		renderLayers(RenderLayer::Transparent);


		if (rayTraceResult.has_value()) {
			auto[pos_x, pos_y, pos_z] = rayTraceResult->pos;

			VBuffer buf{};
			buf.quad(0, 1, 1, 2, 2, 3, 3, 0);
			buf.vertex(pos_x + 0, pos_y + 0, pos_z + 0, 0, 0, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 0, pos_y + 1, pos_z + 0, 0, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 1, pos_y + 1, pos_z + 0, 1, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 1, pos_y + 0, pos_z + 0, 1, 0, 0, 0, 0, 0xFF);

			buf.quad(0, 1, 1, 2, 2, 3, 3, 0);
			buf.vertex(pos_x + 1, pos_y + 0, pos_z + 0, 0, 0, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 1, pos_y + 1, pos_z + 0, 0, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 1, pos_y + 1, pos_z + 1, 1, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 1, pos_y + 0, pos_z + 1, 1, 0, 0, 0, 0, 0xFF);

			buf.quad(0, 1, 1, 2, 2, 3, 3, 0);
			buf.vertex(pos_x + 1, pos_y + 0, pos_z + 1, 0, 0, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 1, pos_y + 1, pos_z + 1, 0, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 0, pos_y + 1, pos_z + 1, 1, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 0, pos_y + 0, pos_z + 1, 1, 0, 0, 0, 0, 0xFF);

			buf.quad(0, 1, 1, 2, 2, 3, 3, 0);
			buf.vertex(pos_x + 0, pos_y + 0, pos_z + 1, 0, 0, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 0, pos_y + 1, pos_z + 1, 0, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 0, pos_y + 1, pos_z + 0, 1, 1, 0, 0, 0, 0xFF);
			buf.vertex(pos_x + 0, pos_y + 0, pos_z + 0, 1, 0, 0, 0, 0, 0xFF);

			selection_mesh->SetIndices(buf.indices);
			selection_mesh->SetVertices(buf.vertices);

			glDisable(GL_BLEND);
			glDepthRange(0, 1.0);
			glBindVertexArray(selection_mesh->vao);
			glDrawElements(GL_LINES, selection_mesh->index_count, GL_UNSIGNED_INT, nullptr);
		}

		sf::Shader::bind(nullptr);
	}

    void run() {
        window.setMouseCursorGrabbed(true);
        window.setMouseCursorVisible(false);


        auto [display_width, display_height] = window.getSize();
		sf::Mouse::setPosition(sf::Vector2i(display_width / 2, display_height / 2), window);

		camera.setSize(display_width, display_height);

		selection_mesh = std::make_unique<Mesh>();

        float dt = 1.0f / 60.0f;

        using namespace std::chrono_literals;

        std::this_thread::sleep_for(1000ms);

        clock.restart();
        while (handleEvents(), window.isOpen()) {
			input.update();

			if (window.hasFocus()) {
				update_player_input(dt);
			}

			if (cooldown > 0) {
				cooldown -= 1;
			}

			render_terrain();

			window.display();

            dt = clock.restart().asSeconds();
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
};

auto main() -> int32 {
    App app{"Minecraft", 800, 600};
    app.run();
    return 0;
}