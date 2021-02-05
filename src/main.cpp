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
#include <queue>
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
#include "world/gen/NoiseChunkGenerator.hpp"

extern void renderBlocks(RenderBuffer& rb, BlockTable& pallete, const WorldGenRegion& blocks);

std::map<std::string, BlockGraphics> tile_datas;

struct LiquidNode {
    glm::ivec3 pos;
    int data;
};

BlockTable global_pallete{};

struct ClientWorld {
	mutable std::mutex chunk_mutex;
    std::map<int64, Chunk*> chunks{};
    std::queue<LiquidNode> liquids{};

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

	auto getChunk(int64 position) const -> Chunk* {
		Chunk* chunk{nullptr};
		chunk_mutex.lock();
		auto it = chunks.find(position);
		if (it != chunks.end()) {
			chunk = it->second;
		}
		chunk_mutex.unlock();
		return chunk;
	}

	auto getBlock(int32 x, int32 y, int32 z) const -> BlockData {
		if (y >= 0 && y < 256) {
			if (auto chunk = getChunk(ChunkPos::asLong(x >> 4, z >> 4))) {
				return chunk->getBlock(x, y, z);
			}
		}
		return {};
	}

    auto getBlock(glm::ivec3 pos) -> BlockData {
        return getBlock(pos.x, pos.y, pos.z);
    }

	void setBlock(int32 x, int32 y, int32 z, BlockData blockData) {
		if (y >= 0 && y < 256) {
			if (auto chunk = getChunk(ChunkPos::asLong(x >> 4, z >> 4))) {
				chunk->setBlock(x, y, z, blockData);
			}
		}
    }

    void setBlock(glm::ivec3 pos, BlockData blockData) {
        setBlock(pos.x, pos.y, pos.z, blockData);
    }
};

ClientWorld client_world{};

struct World {
    NoiseChunkGenerator generator{global_pallete};

    std::atomic<ChunkPos> player_position{ChunkPos{100, 100}};
    std::vector<std::jthread> workers{};
    std::map<int64, std::unique_ptr<Chunk>> chunks{};

    int64_t seed;

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

					WorldGenRegion region{1, (int32)(pos & 0xFFFFFFFFLL), (int32) ((pos >> 32) & 0xFFFFFFFF), seed};
					fillRegion(region, ChunkState::Full);

					renderBlocks(chunk->rb, global_pallete, region);
                    chunk->needUpdate = true;
				}
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    void loadChunks(int32 center_x, int32 center_z) {
        for (int32 chunk_x = center_x - 8; chunk_x <= center_x + 8; chunk_x++) {
            for (int32 chunk_z = center_z - 8; chunk_z <= center_z + 8; chunk_z++) {
				WorldGenRegion region{1, chunk_x, chunk_z, seed};
				fillRegion(region, ChunkState::Full);

				auto chunk = region.getMainChunk();
                if (chunk->needRender) {
                    chunk->needRender = false;
					renderBlocks(chunk->rb, global_pallete, region);
                    chunk->needUpdate = true;
                }

                client_world.loadChunk(ChunkPos::asLong(chunk_x, chunk_z), chunk);
            }
        }
    }

    void fillRegion(WorldGenRegion& region, ChunkState state) {
        const auto radius = region.radius;
        const auto chunk_x = region.chunk_x;
    	const auto chunk_z = region.chunk_z;

		usize i = 0;
		for (int32 z = chunk_z - radius; z <= chunk_z + radius; z++) {
			for (int32 x = chunk_x - radius; x <= chunk_x + radius; x++) {
				region.chunks[i++] = getChunk(x, z, state);
			}
		}
    }

    auto getChunk(int32 chunk_x, int32 chunk_z, ChunkState state = ChunkState::Full) -> Chunk* {
    	if (state == ChunkState::Empty) {
    	    const ChunkPos chunkPos{chunk_x, chunk_z};
        	auto& chunk = chunks[chunkPos.asLong()];
        	if (chunk == nullptr) {
				chunk = std::make_unique<Chunk>(chunkPos);
			}
			return chunk.get();
    	}

    	auto parent_state = (ChunkState)((int32)state - 1);

		auto chunk = getChunk(chunk_x, chunk_z, parent_state);
		if (chunk->state == parent_state) {
			switch (state) {
			case ChunkState::Empty:
				break;
			case ChunkState::StructureStart: {
//                WorldGenRegion region{1, chunk_x, chunk_z, seed};
//                fillRegion(region, parent_state);
//                generator.generateStructures(region, chunk);
                break;
            }
			case ChunkState::StructureReferences: {
//				WorldGenRegion region{8, chunk_x, chunk_z, seed};
//				fillRegion(region, parent_state);
//                generator.getStructureReferences(region, chunk);
				break;
			}
			case ChunkState::Noise:
                generator.generateTerrain(chunk, global_pallete);
				break;
            case ChunkState::Surface: {
                WorldGenRegion region{0, chunk_x, chunk_z, seed};
                fillRegion(region, parent_state);
                generator.generateSurface(region, chunk, global_pallete);
                break;
            }
			case ChunkState::Features: {
//				WorldGenRegion region{8, chunk_x, chunk_z, seed};
//				fillRegion(region, parent_state);
//				generator.generateFeatures(region, chunk, global_pallete);
				break;
			}
			case ChunkState::Light: {
				WorldGenRegion region{1, chunk_x, chunk_z, seed};
				fillRegion(region, parent_state);
				break;
			}
			case ChunkState::Full: {
//				WorldGenRegion<0> region{chunk_x, chunk_z};
//				fillRegion(region, parent_state);
				chunk->needRender = true;
				break;
			}
			}
            chunk->state = state;
		}
		return chunk;
    }
};

struct CameraConstants {
	glm::mat4 transform;
	glm::vec3 position;
};

auto check_collide(const IBlockReader auto& blocks, float x, float y, float z) -> bool {
	int32_t ix = glm::floor(x);
	int32_t iy = glm::floor(y);
	int32_t iz = glm::floor(z);

	return Block::id_to_block[(int) blocks.getBlock(ix, iy, iz).id]->renderType == RenderType::Block;
}

float check_down_velocity(const IBlockReader auto& blocks, glm::vec3 position, float velocity, float half_collider_width = 0.3f) {
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

float check_up_velocity(const IBlockReader auto& blocks, glm::vec3 entity_pos, float vel, float half_collider_width = 0.3f, float collider_height = 1.8f) {
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

float check_front_velocity(const IBlockReader auto& blocks, glm::vec3 position, glm::vec3 velocity, float half_collider_width = 0.3f, float collider_height = 1.8f) {
    const auto new_pos = position + velocity;
    if (check_collide(blocks, new_pos.x/* + half_collider_width*/, new_pos.y, new_pos.z + half_collider_width)) {
        return 0;
    }
//    if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y, new_pos.z + half_collider_width)) {
//        return 0;
//    }
    if (check_collide(blocks, new_pos.x/* + half_collider_width*/, new_pos.y + collider_height, new_pos.z + half_collider_width)) {
        return 0;
    }
//    if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y + collider_height, new_pos.z + half_collider_width)) {
//        return 0;
//    }
	return velocity.z;
}

float check_back_velocity(const IBlockReader auto& blocks, glm::vec3 position, glm::vec3 velocity, float half_collider_width = 0.3f, float collider_height = 1.8f) {
    const auto new_pos = position + velocity;
    if (check_collide(blocks, new_pos.x/* + half_collider_width*/, new_pos.y, new_pos.z - half_collider_width)) {
        return 0;
    }
//    if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y, new_pos.z - half_collider_width)) {
//        return 0;
//    }
    if (check_collide(blocks, new_pos.x/* + half_collider_width*/, new_pos.y + collider_height, new_pos.z - half_collider_width)) {
        return 0;
    }
//    if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y + collider_height, new_pos.z - half_collider_width)) {
//        return 0;
//    }
    return velocity.z;
}

float check_left_velocity(const IBlockReader auto& blocks, glm::vec3 position, glm::vec3 velocity, float half_collider_width = 0.3f, float collider_height = 1.8f) {
    const auto new_pos = position + velocity;
    if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y, new_pos.z/* - half_collider_width*/)) {
        return 0;
    }
//    if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y, new_pos.z + half_collider_width)) {
//        return 0;
//    }
    if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y + collider_height, new_pos.z/* - half_collider_width*/)) {
        return 0;
    }
//    if (check_collide(blocks, new_pos.x - half_collider_width, new_pos.y + collider_height, new_pos.z + half_collider_width)) {
//        return 0;
//    }
    return velocity.x;
}

float check_right_velocity(const IBlockReader auto& blocks, glm::vec3 position, glm::vec3 velocity, float half_collider_width = 0.3f, float collider_height = 1.8f) {
    const auto new_pos = position + velocity;
    if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y, new_pos.z/* - half_collider_width*/)) {
        return 0;
    }
//    if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y, new_pos.z + half_collider_width)) {
//        return 0;
//    }
    if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y + collider_height, new_pos.z/* - half_collider_width*/)) {
        return 0;
    }
//    if (check_collide(blocks, new_pos.x + half_collider_width, new_pos.y + collider_height, new_pos.z + half_collider_width)) {
//        return 0;
//    }
    return velocity.x;
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
        .position = {0, 100, 0}
    };
	glm::vec3 velocity{0, 0, 0};
	int cooldown = 0;

	sf::Shader opaque_pipeline;
	sf::Shader cutout_pipeline;
	sf::Shader transparent_pipeline;

    TextureAtlas texture_atlas;

    std::vector<Chunk*> chunkToRenders;

    std::unique_ptr<Mesh> selection_mesh;
    std::unique_ptr<World> world;

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

        Block::initBlocks();
        
        {
            Block::id_to_block[(int) global_pallete.getId("acacia_button")] = Block::acacia_button;
            Block::id_to_block[(int) global_pallete.getId("acacia_door")] = Block::acacia_door;
            Block::id_to_block[(int) global_pallete.getId("acacia_fence_gate")] = Block::acacia_fence_gate;
            Block::id_to_block[(int) global_pallete.getId("acacia_pressure_plate")] = Block::acacia_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("acacia_stairs")] = Block::acacia_stairs;
            Block::id_to_block[(int) global_pallete.getId("acacia_standing_sign")] = Block::acacia_standing_sign;
            Block::id_to_block[(int) global_pallete.getId("acacia_trapdoor")] = Block::acacia_trapdoor;
            Block::id_to_block[(int) global_pallete.getId("acacia_wall_sign")] = Block::acacia_wall_sign;
            Block::id_to_block[(int) global_pallete.getId("activator_rail")] = Block::activator_rail;
            Block::id_to_block[(int) global_pallete.getId("air")] = Block::air;
            Block::id_to_block[(int) global_pallete.getId("allow")] = Block::allow;
            Block::id_to_block[(int) global_pallete.getId("andesite_stairs")] = Block::andesite_stairs;
            Block::id_to_block[(int) global_pallete.getId("anvil")] = Block::anvil;
            Block::id_to_block[(int) global_pallete.getId("bamboo")] = Block::bamboo;
            Block::id_to_block[(int) global_pallete.getId("bamboo_sapling")] = Block::bamboo_sapling;
            Block::id_to_block[(int) global_pallete.getId("barrel")] = Block::barrel;
            Block::id_to_block[(int) global_pallete.getId("barrier")] = Block::barrier;
            Block::id_to_block[(int) global_pallete.getId("beacon")] = Block::beacon;
            Block::id_to_block[(int) global_pallete.getId("bed")] = Block::bed;
            Block::id_to_block[(int) global_pallete.getId("bedrock")] = Block::bedrock;
            Block::id_to_block[(int) global_pallete.getId("beetroot")] = Block::beetroot;
            Block::id_to_block[(int) global_pallete.getId("bell")] = Block::bell;
            Block::id_to_block[(int) global_pallete.getId("birch_button")] = Block::birch_button;
            Block::id_to_block[(int) global_pallete.getId("birch_door")] = Block::birch_door;
            Block::id_to_block[(int) global_pallete.getId("birch_fence_gate")] = Block::birch_fence_gate;
            Block::id_to_block[(int) global_pallete.getId("birch_pressure_plate")] = Block::birch_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("birch_stairs")] = Block::birch_stairs;
            Block::id_to_block[(int) global_pallete.getId("birch_standing_sign")] = Block::birch_standing_sign;
            Block::id_to_block[(int) global_pallete.getId("birch_trapdoor")] = Block::birch_trapdoor;
            Block::id_to_block[(int) global_pallete.getId("birch_wall_sign")] = Block::birch_wall_sign;
            Block::id_to_block[(int) global_pallete.getId("black_glazed_terracotta")] = Block::black_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("blast_furnace")] = Block::blast_furnace;
            Block::id_to_block[(int) global_pallete.getId("blue_glazed_terracotta")] = Block::blue_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("blue_ice")] = Block::blue_ice;
            Block::id_to_block[(int) global_pallete.getId("bone_block")] = Block::bone_block;
            Block::id_to_block[(int) global_pallete.getId("bookshelf")] = Block::bookshelf;
            Block::id_to_block[(int) global_pallete.getId("border_block")] = Block::border_block;
            Block::id_to_block[(int) global_pallete.getId("brewing_stand")] = Block::brewing_stand;
            Block::id_to_block[(int) global_pallete.getId("brick_block")] = Block::brick_block;
            Block::id_to_block[(int) global_pallete.getId("brick_stairs")] = Block::brick_stairs;
            Block::id_to_block[(int) global_pallete.getId("brown_glazed_terracotta")] = Block::brown_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("brown_mushroom")] = Block::brown_mushroom;
            Block::id_to_block[(int) global_pallete.getId("brown_mushroom_block")] = Block::brown_mushroom_block;
            Block::id_to_block[(int) global_pallete.getId("bubble_column")] = Block::bubble_column;
            Block::id_to_block[(int) global_pallete.getId("cactus")] = Block::cactus;
            Block::id_to_block[(int) global_pallete.getId("cake")] = Block::cake;
            Block::id_to_block[(int) global_pallete.getId("camera")] = Block::camera;
            Block::id_to_block[(int) global_pallete.getId("campfire")] = Block::campfire;
            Block::id_to_block[(int) global_pallete.getId("carpet")] = Block::carpet;
            Block::id_to_block[(int) global_pallete.getId("carrots")] = Block::carrots;
            Block::id_to_block[(int) global_pallete.getId("cartography_table")] = Block::cartography_table;
            Block::id_to_block[(int) global_pallete.getId("carved_pumpkin")] = Block::carved_pumpkin;
            Block::id_to_block[(int) global_pallete.getId("cauldron")] = Block::cauldron;
            Block::id_to_block[(int) global_pallete.getId("chain_command_block")] = Block::chain_command_block;
            Block::id_to_block[(int) global_pallete.getId("chest")] = Block::chest;
            Block::id_to_block[(int) global_pallete.getId("chorus_flower")] = Block::chorus_flower;
            Block::id_to_block[(int) global_pallete.getId("chorus_plant")] = Block::chorus_plant;
            Block::id_to_block[(int) global_pallete.getId("clay")] = Block::clay;
            Block::id_to_block[(int) global_pallete.getId("coal_block")] = Block::coal_block;
            Block::id_to_block[(int) global_pallete.getId("coal_ore")] = Block::coal_ore;
            Block::id_to_block[(int) global_pallete.getId("cobblestone")] = Block::cobblestone;
            Block::id_to_block[(int) global_pallete.getId("cobblestone_wall")] = Block::cobblestone_wall;
            Block::id_to_block[(int) global_pallete.getId("cocoa")] = Block::cocoa;
            Block::id_to_block[(int) global_pallete.getId("command_block")] = Block::command_block;
            Block::id_to_block[(int) global_pallete.getId("composter")] = Block::composter;
            Block::id_to_block[(int) global_pallete.getId("concrete")] = Block::concrete;
            Block::id_to_block[(int) global_pallete.getId("concretePowder")] = Block::concretePowder;
            Block::id_to_block[(int) global_pallete.getId("conduit")] = Block::conduit;
            Block::id_to_block[(int) global_pallete.getId("coral")] = Block::coral;
            Block::id_to_block[(int) global_pallete.getId("coral_block")] = Block::coral_block;
            Block::id_to_block[(int) global_pallete.getId("coral_fan")] = Block::coral_fan;
            Block::id_to_block[(int) global_pallete.getId("coral_fan_dead")] = Block::coral_fan_dead;
            Block::id_to_block[(int) global_pallete.getId("coral_fan_hang")] = Block::coral_fan_hang;
            Block::id_to_block[(int) global_pallete.getId("coral_fan_hang2")] = Block::coral_fan_hang2;
            Block::id_to_block[(int) global_pallete.getId("coral_fan_hang3")] = Block::coral_fan_hang3;
            Block::id_to_block[(int) global_pallete.getId("crafting_table")] = Block::crafting_table;
            Block::id_to_block[(int) global_pallete.getId("cyan_glazed_terracotta")] = Block::cyan_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("dark_oak_button")] = Block::dark_oak_button;
            Block::id_to_block[(int) global_pallete.getId("dark_oak_door")] = Block::dark_oak_door;
            Block::id_to_block[(int) global_pallete.getId("dark_oak_fence_gate")] = Block::dark_oak_fence_gate;
            Block::id_to_block[(int) global_pallete.getId("dark_oak_pressure_plate")] = Block::dark_oak_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("dark_oak_stairs")] = Block::dark_oak_stairs;
            Block::id_to_block[(int) global_pallete.getId("dark_oak_trapdoor")] = Block::dark_oak_trapdoor;
            Block::id_to_block[(int) global_pallete.getId("dark_prismarine_stairs")] = Block::dark_prismarine_stairs;
            Block::id_to_block[(int) global_pallete.getId("darkoak_standing_sign")] = Block::darkoak_standing_sign;
            Block::id_to_block[(int) global_pallete.getId("darkoak_wall_sign")] = Block::darkoak_wall_sign;
            Block::id_to_block[(int) global_pallete.getId("daylight_detector")] = Block::daylight_detector;
            Block::id_to_block[(int) global_pallete.getId("daylight_detector_inverted")] = Block::daylight_detector_inverted;
            Block::id_to_block[(int) global_pallete.getId("deadbush")] = Block::deadbush;
            Block::id_to_block[(int) global_pallete.getId("deny")] = Block::deny;
            Block::id_to_block[(int) global_pallete.getId("detector_rail")] = Block::detector_rail;
            Block::id_to_block[(int) global_pallete.getId("diamond_block")] = Block::diamond_block;
            Block::id_to_block[(int) global_pallete.getId("diamond_ore")] = Block::diamond_ore;
            Block::id_to_block[(int) global_pallete.getId("diorite_stairs")] = Block::diorite_stairs;
            Block::id_to_block[(int) global_pallete.getId("dirt")] = Block::dirt;
            Block::id_to_block[(int) global_pallete.getId("dispenser")] = Block::dispenser;
            Block::id_to_block[(int) global_pallete.getId("double_plant")] = Block::double_plant;
            Block::id_to_block[(int) global_pallete.getId("double_stone_slab")] = Block::double_stone_slab;
            Block::id_to_block[(int) global_pallete.getId("double_stone_slab2")] = Block::double_stone_slab2;
            Block::id_to_block[(int) global_pallete.getId("double_stone_slab3")] = Block::double_stone_slab3;
            Block::id_to_block[(int) global_pallete.getId("double_stone_slab4")] = Block::double_stone_slab4;
            Block::id_to_block[(int) global_pallete.getId("double_wooden_slab")] = Block::double_wooden_slab;
            Block::id_to_block[(int) global_pallete.getId("dragon_egg")] = Block::dragon_egg;
            Block::id_to_block[(int) global_pallete.getId("dried_kelp_block")] = Block::dried_kelp_block;
            Block::id_to_block[(int) global_pallete.getId("dropper")] = Block::dropper;
            Block::id_to_block[(int) global_pallete.getId("emerald_block")] = Block::emerald_block;
            Block::id_to_block[(int) global_pallete.getId("emerald_ore")] = Block::emerald_ore;
            Block::id_to_block[(int) global_pallete.getId("enchanting_table")] = Block::enchanting_table;
            Block::id_to_block[(int) global_pallete.getId("end_brick_stairs")] = Block::end_brick_stairs;
            Block::id_to_block[(int) global_pallete.getId("end_bricks")] = Block::end_bricks;
            Block::id_to_block[(int) global_pallete.getId("end_gateway")] = Block::end_gateway;
            Block::id_to_block[(int) global_pallete.getId("end_portal")] = Block::end_portal;
            Block::id_to_block[(int) global_pallete.getId("end_portal_frame")] = Block::end_portal_frame;
            Block::id_to_block[(int) global_pallete.getId("end_rod")] = Block::end_rod;
            Block::id_to_block[(int) global_pallete.getId("end_stone")] = Block::end_stone;
            Block::id_to_block[(int) global_pallete.getId("ender_chest")] = Block::ender_chest;
            Block::id_to_block[(int) global_pallete.getId("farmland")] = Block::farmland;
            Block::id_to_block[(int) global_pallete.getId("fence")] = Block::fence;
            Block::id_to_block[(int) global_pallete.getId("fence_gate")] = Block::fence_gate;
            Block::id_to_block[(int) global_pallete.getId("fire")] = Block::fire;
            Block::id_to_block[(int) global_pallete.getId("fletching_table")] = Block::fletching_table;
            Block::id_to_block[(int) global_pallete.getId("flower_pot")] = Block::flower_pot;
            Block::id_to_block[(int) global_pallete.getId("flowing_lava")] = Block::flowing_lava;
            Block::id_to_block[(int) global_pallete.getId("flowing_water")] = Block::flowing_water;
            Block::id_to_block[(int) global_pallete.getId("frame")] = Block::frame;
            Block::id_to_block[(int) global_pallete.getId("frosted_ice")] = Block::frosted_ice;
            Block::id_to_block[(int) global_pallete.getId("furnace")] = Block::furnace;
            Block::id_to_block[(int) global_pallete.getId("glass")] = Block::glass;
            Block::id_to_block[(int) global_pallete.getId("glass_pane")] = Block::glass_pane;
            Block::id_to_block[(int) global_pallete.getId("glowingobsidian")] = Block::glowingobsidian;
            Block::id_to_block[(int) global_pallete.getId("glowstone")] = Block::glowstone;
            Block::id_to_block[(int) global_pallete.getId("gold_block")] = Block::gold_block;
            Block::id_to_block[(int) global_pallete.getId("gold_ore")] = Block::gold_ore;
            Block::id_to_block[(int) global_pallete.getId("golden_rail")] = Block::golden_rail;
            Block::id_to_block[(int) global_pallete.getId("granite_stairs")] = Block::granite_stairs;
            Block::id_to_block[(int) global_pallete.getId("grass")] = Block::grass;
            Block::id_to_block[(int) global_pallete.getId("grass_path")] = Block::grass_path;
            Block::id_to_block[(int) global_pallete.getId("gravel")] = Block::gravel;
            Block::id_to_block[(int) global_pallete.getId("gray_glazed_terracotta")] = Block::gray_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("green_glazed_terracotta")] = Block::green_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("grindstone")] = Block::grindstone;
            Block::id_to_block[(int) global_pallete.getId("hardened_clay")] = Block::hardened_clay;
            Block::id_to_block[(int) global_pallete.getId("hay_block")] = Block::hay_block;
            Block::id_to_block[(int) global_pallete.getId("heavy_weighted_pressure_plate")] = Block::heavy_weighted_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("hopper")] = Block::hopper;
            Block::id_to_block[(int) global_pallete.getId("ice")] = Block::ice;
            Block::id_to_block[(int) global_pallete.getId("info_update")] = Block::info_update;
            Block::id_to_block[(int) global_pallete.getId("info_update2")] = Block::info_update2;
            Block::id_to_block[(int) global_pallete.getId("invisibleBedrock")] = Block::invisibleBedrock;
            Block::id_to_block[(int) global_pallete.getId("iron_bars")] = Block::iron_bars;
            Block::id_to_block[(int) global_pallete.getId("iron_block")] = Block::iron_block;
            Block::id_to_block[(int) global_pallete.getId("iron_door")] = Block::iron_door;
            Block::id_to_block[(int) global_pallete.getId("iron_ore")] = Block::iron_ore;
            Block::id_to_block[(int) global_pallete.getId("iron_trapdoor")] = Block::iron_trapdoor;
            Block::id_to_block[(int) global_pallete.getId("jigsaw")] = Block::jigsaw;
            Block::id_to_block[(int) global_pallete.getId("jukebox")] = Block::jukebox;
            Block::id_to_block[(int) global_pallete.getId("jungle_button")] = Block::jungle_button;
            Block::id_to_block[(int) global_pallete.getId("jungle_door")] = Block::jungle_door;
            Block::id_to_block[(int) global_pallete.getId("jungle_fence_gate")] = Block::jungle_fence_gate;
            Block::id_to_block[(int) global_pallete.getId("jungle_pressure_plate")] = Block::jungle_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("jungle_stairs")] = Block::jungle_stairs;
            Block::id_to_block[(int) global_pallete.getId("jungle_standing_sign")] = Block::jungle_standing_sign;
            Block::id_to_block[(int) global_pallete.getId("jungle_trapdoor")] = Block::jungle_trapdoor;
            Block::id_to_block[(int) global_pallete.getId("jungle_wall_sign")] = Block::jungle_wall_sign;
            Block::id_to_block[(int) global_pallete.getId("kelp")] = Block::kelp;
            Block::id_to_block[(int) global_pallete.getId("ladder")] = Block::ladder;
            Block::id_to_block[(int) global_pallete.getId("lantern")] = Block::lantern;
            Block::id_to_block[(int) global_pallete.getId("lapis_block")] = Block::lapis_block;
            Block::id_to_block[(int) global_pallete.getId("lapis_ore")] = Block::lapis_ore;
            Block::id_to_block[(int) global_pallete.getId("lava")] = Block::lava;
            Block::id_to_block[(int) global_pallete.getId("lava_cauldron")] = Block::lava_cauldron;
            Block::id_to_block[(int) global_pallete.getId("leaves")] = Block::leaves;
            Block::id_to_block[(int) global_pallete.getId("leaves2")] = Block::leaves2;
            Block::id_to_block[(int) global_pallete.getId("lectern")] = Block::lectern;
            Block::id_to_block[(int) global_pallete.getId("lever")] = Block::lever;
            Block::id_to_block[(int) global_pallete.getId("light_block")] = Block::light_block;
            Block::id_to_block[(int) global_pallete.getId("light_blue_glazed_terracotta")] = Block::light_blue_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("light_weighted_pressure_plate")] = Block::light_weighted_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("lime_glazed_terracotta")] = Block::lime_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("lit_blast_furnace")] = Block::lit_blast_furnace;
            Block::id_to_block[(int) global_pallete.getId("lit_furnace")] = Block::lit_furnace;
            Block::id_to_block[(int) global_pallete.getId("lit_pumpkin")] = Block::lit_pumpkin;
            Block::id_to_block[(int) global_pallete.getId("lit_redstone_lamp")] = Block::lit_redstone_lamp;
            Block::id_to_block[(int) global_pallete.getId("lit_redstone_ore")] = Block::lit_redstone_ore;
            Block::id_to_block[(int) global_pallete.getId("lit_smoker")] = Block::lit_smoker;
            Block::id_to_block[(int) global_pallete.getId("log")] = Block::log;
            Block::id_to_block[(int) global_pallete.getId("log2")] = Block::log2;
            Block::id_to_block[(int) global_pallete.getId("loom")] = Block::loom;
            Block::id_to_block[(int) global_pallete.getId("magenta_glazed_terracotta")] = Block::magenta_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("magma")] = Block::magma;
            Block::id_to_block[(int) global_pallete.getId("melon_block")] = Block::melon_block;
            Block::id_to_block[(int) global_pallete.getId("melon_stem")] = Block::melon_stem;
            Block::id_to_block[(int) global_pallete.getId("mob_spawner")] = Block::mob_spawner;
            Block::id_to_block[(int) global_pallete.getId("monster_egg")] = Block::monster_egg;
            Block::id_to_block[(int) global_pallete.getId("mossy_cobblestone")] = Block::mossy_cobblestone;
            Block::id_to_block[(int) global_pallete.getId("mossy_cobblestone_stairs")] = Block::mossy_cobblestone_stairs;
            Block::id_to_block[(int) global_pallete.getId("mossy_stone_brick_stairs")] = Block::mossy_stone_brick_stairs;
            Block::id_to_block[(int) global_pallete.getId("movingBlock")] = Block::movingBlock;
            Block::id_to_block[(int) global_pallete.getId("mycelium")] = Block::mycelium;
            Block::id_to_block[(int) global_pallete.getId("nether_brick")] = Block::nether_brick;
            Block::id_to_block[(int) global_pallete.getId("nether_brick_fence")] = Block::nether_brick_fence;
            Block::id_to_block[(int) global_pallete.getId("nether_brick_stairs")] = Block::nether_brick_stairs;
            Block::id_to_block[(int) global_pallete.getId("nether_wart")] = Block::nether_wart;
            Block::id_to_block[(int) global_pallete.getId("nether_wart_block")] = Block::nether_wart_block;
            Block::id_to_block[(int) global_pallete.getId("netherrack")] = Block::netherrack;
            Block::id_to_block[(int) global_pallete.getId("netherreactor")] = Block::netherreactor;
            Block::id_to_block[(int) global_pallete.getId("normal_stone_stairs")] = Block::normal_stone_stairs;
            Block::id_to_block[(int) global_pallete.getId("noteblock")] = Block::noteblock;
            Block::id_to_block[(int) global_pallete.getId("oak_stairs")] = Block::oak_stairs;
            Block::id_to_block[(int) global_pallete.getId("observer")] = Block::observer;
            Block::id_to_block[(int) global_pallete.getId("obsidian")] = Block::obsidian;
            Block::id_to_block[(int) global_pallete.getId("orange_glazed_terracotta")] = Block::orange_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("packed_ice")] = Block::packed_ice;
            Block::id_to_block[(int) global_pallete.getId("pink_glazed_terracotta")] = Block::pink_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("piston")] = Block::piston;
            Block::id_to_block[(int) global_pallete.getId("pistonArmCollision")] = Block::pistonArmCollision;
            Block::id_to_block[(int) global_pallete.getId("planks")] = Block::planks;
            Block::id_to_block[(int) global_pallete.getId("podzol")] = Block::podzol;
            Block::id_to_block[(int) global_pallete.getId("polished_andesite_stairs")] = Block::polished_andesite_stairs;
            Block::id_to_block[(int) global_pallete.getId("polished_diorite_stairs")] = Block::polished_diorite_stairs;
            Block::id_to_block[(int) global_pallete.getId("polished_granite_stairs")] = Block::polished_granite_stairs;
            Block::id_to_block[(int) global_pallete.getId("portal")] = Block::portal;
            Block::id_to_block[(int) global_pallete.getId("potatoes")] = Block::potatoes;
            Block::id_to_block[(int) global_pallete.getId("powered_comparator")] = Block::powered_comparator;
            Block::id_to_block[(int) global_pallete.getId("powered_repeater")] = Block::powered_repeater;
            Block::id_to_block[(int) global_pallete.getId("prismarine")] = Block::prismarine;
            Block::id_to_block[(int) global_pallete.getId("prismarine_bricks_stairs")] = Block::prismarine_bricks_stairs;
            Block::id_to_block[(int) global_pallete.getId("prismarine_stairs")] = Block::prismarine_stairs;
            Block::id_to_block[(int) global_pallete.getId("pumpkin")] = Block::pumpkin;
            Block::id_to_block[(int) global_pallete.getId("pumpkin_stem")] = Block::pumpkin_stem;
            Block::id_to_block[(int) global_pallete.getId("purple_glazed_terracotta")] = Block::purple_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("purpur_block")] = Block::purpur_block;
            Block::id_to_block[(int) global_pallete.getId("purpur_stairs")] = Block::purpur_stairs;
            Block::id_to_block[(int) global_pallete.getId("quartz_block")] = Block::quartz_block;
            Block::id_to_block[(int) global_pallete.getId("quartz_ore")] = Block::quartz_ore;
            Block::id_to_block[(int) global_pallete.getId("quartz_stairs")] = Block::quartz_stairs;
            Block::id_to_block[(int) global_pallete.getId("rail")] = Block::rail;
            Block::id_to_block[(int) global_pallete.getId("red_flower")] = Block::red_flower;
            Block::id_to_block[(int) global_pallete.getId("red_glazed_terracotta")] = Block::red_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("red_mushroom")] = Block::red_mushroom;
            Block::id_to_block[(int) global_pallete.getId("red_mushroom_block")] = Block::red_mushroom_block;
            Block::id_to_block[(int) global_pallete.getId("red_nether_brick")] = Block::red_nether_brick;
            Block::id_to_block[(int) global_pallete.getId("red_nether_brick_stairs")] = Block::red_nether_brick_stairs;
            Block::id_to_block[(int) global_pallete.getId("red_sandstone")] = Block::red_sandstone;
            Block::id_to_block[(int) global_pallete.getId("red_sandstone_stairs")] = Block::red_sandstone_stairs;
            Block::id_to_block[(int) global_pallete.getId("redstone_block")] = Block::redstone_block;
            Block::id_to_block[(int) global_pallete.getId("redstone_lamp")] = Block::redstone_lamp;
            Block::id_to_block[(int) global_pallete.getId("redstone_ore")] = Block::redstone_ore;
            Block::id_to_block[(int) global_pallete.getId("redstone_torch")] = Block::redstone_torch;
            Block::id_to_block[(int) global_pallete.getId("redstone_wire")] = Block::redstone_wire;
            Block::id_to_block[(int) global_pallete.getId("reeds")] = Block::reeds;
            Block::id_to_block[(int) global_pallete.getId("repeating_command_block")] = Block::repeating_command_block;
            Block::id_to_block[(int) global_pallete.getId("reserved6")] = Block::reserved6;
            Block::id_to_block[(int) global_pallete.getId("sand")] = Block::sand;
            Block::id_to_block[(int) global_pallete.getId("sandstone")] = Block::sandstone;
            Block::id_to_block[(int) global_pallete.getId("sandstone_stairs")] = Block::sandstone_stairs;
            Block::id_to_block[(int) global_pallete.getId("sapling")] = Block::sapling;
            Block::id_to_block[(int) global_pallete.getId("scaffolding")] = Block::scaffolding;
            Block::id_to_block[(int) global_pallete.getId("seaLantern")] = Block::seaLantern;
            Block::id_to_block[(int) global_pallete.getId("sea_pickle")] = Block::sea_pickle;
            Block::id_to_block[(int) global_pallete.getId("seagrass")] = Block::seagrass;
            Block::id_to_block[(int) global_pallete.getId("shulker_box")] = Block::shulker_box;
            Block::id_to_block[(int) global_pallete.getId("silver_glazed_terracotta")] = Block::silver_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("skull")] = Block::skull;
            Block::id_to_block[(int) global_pallete.getId("slime")] = Block::slime;
            Block::id_to_block[(int) global_pallete.getId("smithing_table")] = Block::smithing_table;
            Block::id_to_block[(int) global_pallete.getId("smoker")] = Block::smoker;
            Block::id_to_block[(int) global_pallete.getId("smooth_quartz_stairs")] = Block::smooth_quartz_stairs;
            Block::id_to_block[(int) global_pallete.getId("smooth_red_sandstone_stairs")] = Block::smooth_red_sandstone_stairs;
            Block::id_to_block[(int) global_pallete.getId("smooth_sandstone_stairs")] = Block::smooth_sandstone_stairs;
            Block::id_to_block[(int) global_pallete.getId("smooth_stone")] = Block::smooth_stone;
            Block::id_to_block[(int) global_pallete.getId("snow")] = Block::snow;
            Block::id_to_block[(int) global_pallete.getId("snow_layer")] = Block::snow_layer;
            Block::id_to_block[(int) global_pallete.getId("soul_sand")] = Block::soul_sand;
            Block::id_to_block[(int) global_pallete.getId("sponge")] = Block::sponge;
            Block::id_to_block[(int) global_pallete.getId("spruce_button")] = Block::spruce_button;
            Block::id_to_block[(int) global_pallete.getId("spruce_door")] = Block::spruce_door;
            Block::id_to_block[(int) global_pallete.getId("spruce_fence_gate")] = Block::spruce_fence_gate;
            Block::id_to_block[(int) global_pallete.getId("spruce_pressure_plate")] = Block::spruce_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("spruce_stairs")] = Block::spruce_stairs;
            Block::id_to_block[(int) global_pallete.getId("spruce_standing_sign")] = Block::spruce_standing_sign;
            Block::id_to_block[(int) global_pallete.getId("spruce_trapdoor")] = Block::spruce_trapdoor;
            Block::id_to_block[(int) global_pallete.getId("spruce_wall_sign")] = Block::spruce_wall_sign;
            Block::id_to_block[(int) global_pallete.getId("stained_glass")] = Block::stained_glass;
            Block::id_to_block[(int) global_pallete.getId("stained_glass_pane")] = Block::stained_glass_pane;
            Block::id_to_block[(int) global_pallete.getId("stained_hardened_clay")] = Block::stained_hardened_clay;
            Block::id_to_block[(int) global_pallete.getId("standing_banner")] = Block::standing_banner;
            Block::id_to_block[(int) global_pallete.getId("standing_sign")] = Block::standing_sign;
            Block::id_to_block[(int) global_pallete.getId("stickyPistonArmCollision")] = Block::stickyPistonArmCollision;
            Block::id_to_block[(int) global_pallete.getId("sticky_piston")] = Block::sticky_piston;
            Block::id_to_block[(int) global_pallete.getId("stone")] = Block::stone;
            Block::id_to_block[(int) global_pallete.getId("stone_brick_stairs")] = Block::stone_brick_stairs;
            Block::id_to_block[(int) global_pallete.getId("stone_button")] = Block::stone_button;
            Block::id_to_block[(int) global_pallete.getId("stone_pressure_plate")] = Block::stone_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("stone_slab")] = Block::stone_slab;
            Block::id_to_block[(int) global_pallete.getId("stone_slab2")] = Block::stone_slab2;
            Block::id_to_block[(int) global_pallete.getId("stone_slab3")] = Block::stone_slab3;
            Block::id_to_block[(int) global_pallete.getId("stone_slab4")] = Block::stone_slab4;
            Block::id_to_block[(int) global_pallete.getId("stone_stairs")] = Block::stone_stairs;
            Block::id_to_block[(int) global_pallete.getId("stonebrick")] = Block::stonebrick;
            Block::id_to_block[(int) global_pallete.getId("stonecutter")] = Block::stonecutter;
            Block::id_to_block[(int) global_pallete.getId("stonecutter_block")] = Block::stonecutter_block;
            Block::id_to_block[(int) global_pallete.getId("stripped_acacia_log")] = Block::stripped_acacia_log;
            Block::id_to_block[(int) global_pallete.getId("stripped_birch_log")] = Block::stripped_birch_log;
            Block::id_to_block[(int) global_pallete.getId("stripped_dark_oak_log")] = Block::stripped_dark_oak_log;
            Block::id_to_block[(int) global_pallete.getId("stripped_jungle_log")] = Block::stripped_jungle_log;
            Block::id_to_block[(int) global_pallete.getId("stripped_oak_log")] = Block::stripped_oak_log;
            Block::id_to_block[(int) global_pallete.getId("stripped_spruce_log")] = Block::stripped_spruce_log;
            Block::id_to_block[(int) global_pallete.getId("structure_block")] = Block::structure_block;
            Block::id_to_block[(int) global_pallete.getId("structure_void")] = Block::structure_void;
            Block::id_to_block[(int) global_pallete.getId("sweet_berry_bush")] = Block::sweet_berry_bush;
            Block::id_to_block[(int) global_pallete.getId("tallgrass")] = Block::tallgrass;
            Block::id_to_block[(int) global_pallete.getId("tnt")] = Block::tnt;
            Block::id_to_block[(int) global_pallete.getId("torch")] = Block::torch;
            Block::id_to_block[(int) global_pallete.getId("trapdoor")] = Block::trapdoor;
            Block::id_to_block[(int) global_pallete.getId("trapped_chest")] = Block::trapped_chest;
            Block::id_to_block[(int) global_pallete.getId("tripWire")] = Block::tripWire;
            Block::id_to_block[(int) global_pallete.getId("tripwire_hook")] = Block::tripwire_hook;
            Block::id_to_block[(int) global_pallete.getId("turtle_egg")] = Block::turtle_egg;
            Block::id_to_block[(int) global_pallete.getId("undyed_shulker_box")] = Block::undyed_shulker_box;
            Block::id_to_block[(int) global_pallete.getId("unlit_redstone_torch")] = Block::unlit_redstone_torch;
            Block::id_to_block[(int) global_pallete.getId("unpowered_comparator")] = Block::unpowered_comparator;
            Block::id_to_block[(int) global_pallete.getId("unpowered_repeater")] = Block::unpowered_repeater;
            Block::id_to_block[(int) global_pallete.getId("vine")] = Block::vine;
            Block::id_to_block[(int) global_pallete.getId("wall_banner")] = Block::wall_banner;
            Block::id_to_block[(int) global_pallete.getId("wall_sign")] = Block::wall_sign;
            Block::id_to_block[(int) global_pallete.getId("water")] = Block::water;
            Block::id_to_block[(int) global_pallete.getId("waterlily")] = Block::waterlily;
            Block::id_to_block[(int) global_pallete.getId("web")] = Block::web;
            Block::id_to_block[(int) global_pallete.getId("wheat")] = Block::wheat;
            Block::id_to_block[(int) global_pallete.getId("white_glazed_terracotta")] = Block::white_glazed_terracotta;
            Block::id_to_block[(int) global_pallete.getId("wither_rose")] = Block::wither_rose;
            Block::id_to_block[(int) global_pallete.getId("wood")] = Block::wood;
            Block::id_to_block[(int) global_pallete.getId("wooden_button")] = Block::wooden_button;
            Block::id_to_block[(int) global_pallete.getId("wooden_door")] = Block::wooden_door;
            Block::id_to_block[(int) global_pallete.getId("wooden_pressure_plate")] = Block::wooden_pressure_plate;
            Block::id_to_block[(int) global_pallete.getId("wooden_slab")] = Block::wooden_slab;
            Block::id_to_block[(int) global_pallete.getId("wool")] = Block::wool;
            Block::id_to_block[(int) global_pallete.getId("yellow_flower")] = Block::yellow_flower;
            Block::id_to_block[(int) global_pallete.getId("yellow_glazed_terracotta")] = Block::yellow_glazed_terracotta;
        }

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


        bool is_liquid = Block::id_to_block[(int) client_world.getBlock(transform.position.x, transform.position.y + 1, transform.position.z).id]->renderType == RenderType::Liquid;

        glm::vec3 ivelocity{};
//		if (input.IsKeyPressed(Input::Key::Up)) {
//            ivelocity += glm::vec3{-s, 0, c};
//		}
//		if (input.IsKeyPressed(Input::Key::Down)) {
//            ivelocity -= glm::vec3{-s, 0, c};
//		}
//		if (input.IsKeyPressed(Input::Key::Left)) {
//            ivelocity -= glm::vec3{c, 0, s};
//		}
//		if (input.IsKeyPressed(Input::Key::Right)) {
//            ivelocity += glm::vec3{c, 0, s};
//		}
//
//        velocity.x = 0;
//        velocity.z = 0;
//
//        if (ivelocity.x != 0 || ivelocity.z != 0) {
//            velocity += glm::normalize(ivelocity) * dt * (is_liquid ? 5.0f : 100.0f);
//        }

//		if (velocity.z > 0) {
//			velocity.z = check_front_velocity(client_world, transform.position, velocity);
//		} else if (velocity.z < 0) {
//			velocity.z = check_back_velocity(client_world, transform.position, velocity);
//		}
//		if (velocity.x > 0) {
//			velocity.x = check_right_velocity(client_world, transform.position, velocity);
//		} else if (velocity.x < 0) {
//			velocity.x = check_left_velocity(client_world, transform.position, velocity);
//		}

//		if (is_liquid) {
//			velocity.y = -2.5 * dt;
//		} else {
//			velocity.y -= 9.8 * dt * dt;
//		}

//		if (velocity.y < 0) {
//			velocity.y = check_down_velocity(client_world, transform.position, velocity.y);
//		}

//		if (input.IsKeyPressed(Input::Key::Jump)) {
//		if (input.IsKeyPressed(Input::Key::Jump)) {
////			if (is_liquid) {
////				velocity.y = 2.5 * dt;
////			} else if (velocity.y == 0) {
//				velocity.y = 5 * dt;
////			}
//		} else {
//            velocity.y = 0;
//		}

//		if (velocity.y > 0) {
//			velocity.y = check_up_velocity(client_world, transform.position, velocity.y);
//		}

        velocity = calc_free_camera_velocity(input, transform, dt);

		transform.position += velocity;

//		fmt::print("{}, {}, {}\n", transform.position.x, transform.position.y, transform.position.z);

		RayTraceContext ray_trace_context {
			.position = transform.position + glm::vec3(0, 1.68, 0),
			.direction = transform.forward()
		};

		rayTraceResult = rayTraceBlocks(client_world, ray_trace_context);
        if (cooldown == 0 && rayTraceResult.has_value()) {
            std::set<int64> positions{};
            if (input.IsMouseButtonPressed(Input::MouseButton::Left)) {
                cooldown = 10;

                const auto pos = rayTraceResult->pos;

                client_world.setBlock(pos, BlockData{BlockID::AIR, 0});

                for (int x = pos.x - 1; x <= pos.x + 1; x++) {
                    for (int z = pos.z - 1; z <= pos.z + 1; z++) {
                        positions.emplace(ChunkPos::asLong(x >> 4, z >> 4));
                    }
                }
            } else if (input.IsMouseButtonPressed(Input::MouseButton::Right)) {
                cooldown = 10;

                const auto pos = rayTraceResult->pos + rayTraceResult->dir;

                client_world.setBlock(pos, BlockData{global_pallete.getId("water"), 0});

//                client_world.setBlock(pos, {Block::water, 0});
                client_world.liquids.emplace(pos);

                for (int x = pos.x - 1; x <= pos.x + 1; x++) {
                    for (int z = pos.z - 1; z <= pos.z + 1; z++) {
                        positions.emplace(ChunkPos::asLong(x >> 4, z >> 4));
                    }
                }
            }

            for (auto position : positions) {
                client_world.getChunk(position)->is_dirty = true;
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

        bool is_liquid = Block::id_to_block[(int) client_world.getBlock(transform.position.x, std::floor(transform.position.y + 1.68), transform.position.z).id]->renderType == RenderType::Liquid;

        std::array<float, 4> color{0, 0.68, 1.0, 1};

        glm::vec2 fog_offset{9, 13};
        if (is_liquid) {
            color = {0.27, 0.68, 0.96, 1};

            fog_offset = glm::vec2{0, 5 };
        }

		glClearNamedFramebufferfv(0, GL_COLOR, 0, color.data());
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
        glUniform3f(0, 1, 0.68, 1.0);
        glUniform2f(4, fog_offset.x, fog_offset.y);

		sf::Shader::bind(&opaque_pipeline);
        glUniform3fv(0, 1, color.data());
        glUniform2f(4, fog_offset.x, fog_offset.y);
		renderLayers(RenderLayer::Opaque);

		sf::Shader::bind(&cutout_pipeline);
        glUniform3fv(0, 1, color.data());
        glUniform2f(4, fog_offset.x, fog_offset.y);
		renderLayers(RenderLayer::Cutout);

		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		sf::Shader::bind(&transparent_pipeline);
        glUniform3fv(0, 1, color.data());
        glUniform2f(4, fog_offset.x, fog_offset.y);
		renderLayers(RenderLayer::Transparent);

		if (rayTraceResult.has_value()) {
			const auto pos = rayTraceResult->pos;

			VBuffer buf{};
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