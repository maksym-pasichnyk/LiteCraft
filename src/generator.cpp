#include "Chunk.hpp"
#include "src/util/Random.hpp"
#include "BlockReader.hpp"
#include "worldgenregion.hpp"

#include <stdint.hpp>
#include <glm/ext.hpp>
#include <fmt/format.h>
#include <stack>

auto getNoiseValue(int32_t x, int32_t z) -> float {
	auto scale = 256.0f;
	auto frequency = 1.0f / scale;

	auto amplitute = 1.0f;
	auto lacunarity = 2.0f;
	auto persistence = 0.5f;

	auto val = 0.0f;
	auto max = 0.0f;

	for (auto i = 0; i < 8; i++) {
		auto noise = glm::simplex(glm::vec2{float(x) * frequency, float(z) * frequency});
		noise = noise * 0.5f + 0.5f;

		val += noise * amplitute;
		max += amplitute;

		frequency *= lacunarity;
		amplitute *= persistence;
	}

	return val / max;
}

void makeBedrock(Chunk* chunk, BlockTable& pallete, Random& rand) {
    const auto dimensionHeight = 256;
    const auto bedrockFloorPosition = 0;
    const auto bedrockRoofPosition = 3;//-1;
    const auto maxAvailableHeight = dimensionHeight - 1 - bedrockRoofPosition;
    const bool makeRoofBedrock = maxAvailableHeight + 4 >= 0 && maxAvailableHeight < dimensionHeight;
    const bool makeFloorBedrock = bedrockFloorPosition + 4 >= 0 && bedrockFloorPosition < dimensionHeight;

    if (makeRoofBedrock || makeFloorBedrock) {
        for (auto x = 0; x <= 15; x++) {
            for (auto z = 0; z <= 15; z++) {
                if (makeRoofBedrock) {
                    for (auto y = 0; y < 5; y++) {
                        if (y <= rand.nextInt(5)) {
                            chunk->setBlock(x, maxAvailableHeight - y, z, BlockData{pallete.getId("bedrock"), 0});
                        }
                    }
                }

                if (makeFloorBedrock) {
                    for (auto y = 4; y >= 0; y--) {
                        if (y <= rand.nextInt(5)) {
                            chunk->setBlock(x, bedrockFloorPosition + y, z, BlockData{pallete.getId("bedrock"), 0});
                        }
                    }
                }
            }
        }
    }
}

void generateSurface(Chunk* chunk, BlockTable& pallete) {
    Random rand{};
    rand.setBaseChunkSeed(chunk->pos.x, chunk->pos.z);

    makeBedrock(chunk, pallete, rand);
}

void generateTerrain(Chunk* chunk, BlockTable& pallete) {
    const auto start_x = chunk->pos.getStartX();
    const auto start_z = chunk->pos.getStartZ();

	Random random;
	random.setBaseChunkSeed(chunk->pos.x, chunk->pos.z);

    for (auto x = start_x; x < start_x + 16; x++) {
        for (auto z = start_z; z < start_z + 16; z++) {
            const auto noise = getNoiseValue(x, z);
            const auto height = static_cast<int32_t>(noise * 60 + 40);

            chunk->heightmap[x & 15][z & 15] = height;

            for (auto y = 0; y < height; y++) {
                chunk->setBlock(x, y, z, BlockData{pallete.getId("grass"), 0});
            }

            for (auto y = height; y < 68; y++) {
                chunk->setBlock(x, y, z, BlockData{pallete.getId("water"), 0});
            }
        }
    }
}

void generateTree(Chunk* chunk, BlockTable& pallete, int32_t x, int32_t z, WorldGenRegion& blocks, Random& rand) {
	const auto height = chunk->heightmap[x & 15][z & 15];
    const auto treeHeight = 4 + rand.nextInt(0, 2);

	for (auto y = treeHeight - 2; y <= treeHeight + 1; y++) {
        blocks.setBlock(x - 1, y + height, z - 1, BlockData{pallete.getId("leaves"), 0});
        blocks.setBlock(x + 0, y + height, z - 1, BlockData{pallete.getId("leaves"), 0});
        blocks.setBlock(x + 1, y + height, z - 1, BlockData{pallete.getId("leaves"), 0});

        blocks.setBlock(x - 1, y + height, z, BlockData{pallete.getId("leaves"), 0});
        blocks.setBlock(x + 0, y + height, z, BlockData{pallete.getId("leaves"), 0});
        blocks.setBlock(x + 1, y + height, z, BlockData{pallete.getId("leaves"), 0});

        blocks.setBlock(x - 1, y + height, z + 1, BlockData{pallete.getId("leaves"), 0});
        blocks.setBlock(x + 0, y + height, z + 1, BlockData{pallete.getId("leaves"), 0});
        blocks.setBlock(x + 1, y + height, z + 1, BlockData{pallete.getId("leaves"), 0});
	}

	for (auto y = height; y < height + treeHeight; y++) {
        blocks.setBlock(x, y, z, BlockData{pallete.getId("log"), 0});
	}
}

struct ExampleStructurePiece : StructurePiece {
    ExampleStructurePiece(int32_t pos_x, int32_t pos_z) {
        coordBaseMode = SOUTH;
        boundingBox = StructureBoundingBox::withSize(pos_x - 1, 6, pos_z - 1, 3, 10, 3);
    }

    void place(WorldGenRegion& region, BlockTable& pallete, StructureBoundingBox sbb) override {
        for (auto y = 0; y < 10; y++) {
            setBlock(region, sbb, 0, y, 0, get(pallete, "iron_bars", 2 | 4));
            setBlock(region, sbb, 0, y, 1, get(pallete, "wood", 0));
            setBlock(region, sbb, 0, y, 2, get(pallete, "iron_bars", 8 | 4));

            setBlock(region, sbb, 1, y, 0, get(pallete, "wood", 0));
            setBlock(region, sbb, 1, y, 1, get(pallete, "wood", 0));
            setBlock(region, sbb, 1, y, 2, get(pallete, "wood", 0));

            setBlock(region, sbb, 2, y, 0, get(pallete, "iron_bars", 2 | 1));
            setBlock(region, sbb, 2, y, 1, get(pallete, "wood", 0));
            setBlock(region, sbb, 2, y, 2, get(pallete, "iron_bars", 8 | 1));
        }
    }

    static BlockData get(BlockTable& pallete, const std::string& name, uint16_t data) {
        return {pallete.getId(name), data};
    }
};


struct ExampleStructureStart : StructureStart {
    void build(int32_t pos_x, int32_t pos_z) override {
        pieces.emplace_back(new ExampleStructurePiece(pos_x + 8, pos_z + 8));
    }
};

void generateStructures(Chunk* chunk, BlockTable& pallete, WorldGenRegion& blocks, int64 worldSeed) {
    if (std::abs(chunk->pos.x) % 2 == std::abs(chunk->pos.z) % 2) {
        auto start = std::make_shared<ExampleStructureStart>();
        start->build(chunk->pos.getStartX(), chunk->pos.getStartZ());
        start->updateBoundingBox();
        chunk->structureStarts.emplace_back(std::move(start));
    }
}

void getStructureReferences(Chunk* chunk, BlockTable& pallete, WorldGenRegion& blocks, int64 worldSeed) {
//    chunk->structureReferences.insert(chunk->structureReferences.end(), chunk->structureStarts.begin(), chunk->structureStarts.end());

    const auto sbb = StructureBoundingBox::fromChunkPos(chunk->pos.x, chunk->pos.z);

    for (auto x = chunk->pos.x - 8; x <= chunk->pos.x + 8; x++) {
        for (auto z = chunk->pos.z - 8; z <= chunk->pos.z + 8; z++) {
            for (auto& start : blocks.getChunk(x, z)->structureStarts) {
                if (sbb.intersect(start->boundingBox)) {
                    chunk->structureReferences.emplace_back(start);
                }
            }
        }
    }
}

void generateFeatures(Chunk* chunk, BlockTable& pallete, WorldGenRegion& blocks, int64 worldSeed) {
    Random random{};

    const auto seed = random.setDecorationSeed(worldSeed, chunk->pos.getStartX(), chunk->pos.getStartZ());
    const auto sbb = StructureBoundingBox::fromChunkPos(chunk->pos.x, chunk->pos.z);

    for (auto& structure : chunk->structureReferences) {
        for (auto& piece : structure.lock()->pieces) {
            piece->place(blocks, pallete, sbb);
        }
    }

//    for (int32_t x = 0; x < 16; x++) {
//        for (int32_t z = 0; z < 16; z++) {
//			random.setFeatureSeed(seed, x + (chunk_x << 4), z + (chunk_z << 4));
//
//            int32_t height = chunk->heightmap[x][z];
//
////            if (height > 68) {
//				int32_t n = random.nextInt(0, 3000);
//
//				if (n < 15) {
//					generateTree(chunk, pallete, (chunk_x << 4) + x, (chunk_z << 4) + z, blocks, random);
//				} else if (n < 40) {
//                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {
//                            BlockData{pallete.getId("red_flower"), 0},
//                            BlockData{BlockID::AIR, 0}
//                    });
//				} else if (n < 80) {
//                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {
//                            BlockData{pallete.getId("yellow_flower"), 0},
//                            BlockData{BlockID::AIR, 0}
//                    });
//				} else if (n < 200) {
//                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {
//                            BlockData{pallete.getId("tallgrass"), 0},
//                            BlockData{BlockID::AIR, 0}
//                    });
//				}
////			}
//        }
//    }
}