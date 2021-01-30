#include "chunk.hpp"
#include "random.hpp"
#include "block_reader.hpp"
#include "worldgenregion.hpp"

#include <stdint.hpp>
#include <glm/ext.hpp>
#include <fmt/format.h>

auto getNoiseValue(int32 x, int32 z) -> float {
	auto scale = 256.0f;
	auto frequency = 1.0f / scale;

	auto amplitute = 1.0f;
	auto lacunarity = 2.0f;
	auto persistence = 0.5f;

	auto val = 0.0f;
	auto max = 0.0f;

	for (int32 i = 0; i < 8; i++) {
		auto noise = glm::simplex(glm::vec2{float(x) * frequency, float(z) * frequency});
		noise = noise * 0.5f + 0.5f;

		val += noise * amplitute;
		max += amplitute;

		frequency *= lacunarity;
		amplitute *= persistence;
	}

	return val / max;
}

void generateTerrain(Chunk* chunk, BlockTable& global_pallete, int32 chunk_x, int32 chunk_z) {
	Random random;
	random.setBaseChunkSeed(chunk_x, chunk_z);

	int32 start_x = chunk_x << 4;
	int32 start_z = chunk_z << 4;

    for (int32 x = start_x; x < start_x + 16; x++) {
        for (int32 z = start_z; z < start_z + 16; z++) {
//            f32 noise = getNoiseValue(x, z);
            int32 height = 6;//noise * 60 + 40;

            chunk->heightmap[x & 15][z & 15] = height;

            for (int32 y = 0; y < height; y++) {
                chunk->setBlock(x, y, z, {
                        BlockData{global_pallete.getId("grass"), 0},
                        BlockData{BlockID::AIR, 0}
                });
            }

//            for (int32 y = height; y < 68; y++) {
//                chunk->setBlock(x, y, z, {
//                        BlockData{global_pallete.getId("water"), 0},
//                        BlockData{BlockID::AIR, 0},
//                });
//            }
        }
    }
}

void generateTree(Chunk* chunk, BlockTable& global_pallete, int32 x, int32 z, WorldGenRegion& blocks, Random& random) {
	int32 height = chunk->heightmap[x & 15][z & 15];

	int32 treeHeight = 4 + random.nextInt(0, 2);

	for (int32 y = treeHeight - 2; y <= treeHeight + 1; y++) {
        blocks.setBlock(x - 1, y + height, z - 1, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });
        blocks.setBlock(x + 0, y + height, z - 1, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });
        blocks.setBlock(x + 1, y + height, z - 1, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });

        blocks.setBlock(x - 1, y + height, z, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });
        blocks.setBlock(x + 0, y + height, z, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });
        blocks.setBlock(x + 1, y + height, z, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });

        blocks.setBlock(x - 1, y + height, z + 1, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });
        blocks.setBlock(x + 0, y + height, z + 1, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });
        blocks.setBlock(x + 1, y + height, z + 1, {
                BlockData{global_pallete.getId("leaves"), 0},
                BlockData{BlockID::AIR, 0}
        });
	}

	for (int32 y = height; y < height + treeHeight; y++) {
        blocks.setBlock(x, y, z, {
                BlockData{global_pallete.getId("log"), 0},
                BlockData{BlockID::AIR, 0}
        });
	}
}

struct ExampleStructurePiece : StructurePiece {
    ExampleStructurePiece(int pos_x, int pos_z) {
        coordBaseMode = SOUTH;
//        boundingBox = StructureBoundingBox::withSize(pos_x, 6, pos_z + 6, 3, 10, 3);
        boundingBox = StructureBoundingBox::withSize(pos_x - 1, 6, pos_z - 1, 3, 10, 3);
    }

    void place(WorldGenRegion& region, BlockTable& pallete, StructureBoundingBox sbb) override {
        for (int y = 0; y < 10; y++) {
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

    static BlockData get(BlockTable& global_pallete, const std::string& name, int data) {
        return {global_pallete.getId(name), 2 | 4};
    }
};

#include <stack>

struct ExampleStructureStart : StructureStart {
    void build(int pos_x, int pos_z) override {
        pieces.emplace_back(new ExampleStructurePiece(pos_x + 8, pos_z + 8));
    }
};

void generateStructures(Chunk* chunk, BlockTable& global_pallete, WorldGenRegion& blocks, int32 chunk_x, int32 chunk_z, int64 worldSeed) {
    if (std::abs(chunk_x) % 2 == std::abs(chunk_z) % 2) {
        auto start = std::make_shared<ExampleStructureStart>();
        start->build(chunk_x << 4, chunk_z << 4);
        start->updateBoundingBox();
        chunk->structureStarts.emplace_back(std::move(start));
    }
}

void generateStructureReferences(Chunk* chunk, BlockTable& global_pallete, WorldGenRegion& blocks, int32 chunk_x, int32 chunk_z, int64 worldSeed) {
    chunk->structureReferences.insert(chunk->structureReferences.end(), chunk->structureStarts.begin(), chunk->structureStarts.end());

    const auto sbb = StructureBoundingBox::fromChunkPos(chunk_x, chunk_z);

    for (int x = chunk_x - 8; x <= chunk_x + 8; x++) {
        for (int z = chunk_z - 8; z <= chunk_z + 8; z++) {
            if (x == chunk_x && z == chunk_z) continue;

            for (auto& start : blocks.getChunk(x, z)->structureStarts) {
                if (sbb.intersect(start->boundingBox)) {
                    chunk->structureReferences.emplace_back(start);
                }
            }
        }
    }
}

void generateFeatures(Chunk* chunk, BlockTable& global_pallete, WorldGenRegion& blocks, int32 chunk_x, int32 chunk_z, int64 worldSeed) {
    Random random;

    auto seed = random.setDecorationSeed(worldSeed, (chunk_x << 4), (chunk_z << 4));

    const auto sbb = StructureBoundingBox::fromChunkPos(chunk_x, chunk_z);

    for (auto& structure : chunk->structureReferences) {
        for (auto& piece : structure.lock()->pieces) {
            piece->place(blocks, global_pallete, sbb);
        }
    }

//    for (int32 x = 0; x < 16; x++) {
//        for (int32 z = 0; z < 16; z++) {
//			random.setFeatureSeed(seed, x + (chunk_x << 4), z + (chunk_z << 4));
//
//            int32 height = chunk->heightmap[x][z];
//
////            if (height > 68) {
//				int32 n = random.nextInt(0, 3000);
//
//				if (n < 15) {
//					generateTree(chunk, global_pallete, (chunk_x << 4) + x, (chunk_z << 4) + z, blocks, random);
//				} else if (n < 40) {
//                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {
//                            BlockData{global_pallete.getId("red_flower"), 0},
//                            BlockData{BlockID::AIR, 0}
//                    });
//				} else if (n < 80) {
//                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {
//                            BlockData{global_pallete.getId("yellow_flower"), 0},
//                            BlockData{BlockID::AIR, 0}
//                    });
//				} else if (n < 200) {
//                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {
//                            BlockData{global_pallete.getId("tallgrass"), 0},
//                            BlockData{BlockID::AIR, 0}
//                    });
//				}
////			}
//        }
//    }
}