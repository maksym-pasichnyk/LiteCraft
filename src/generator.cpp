#include "chunk.hpp"
#include "random.hpp"
#include "chunk_pos.hpp"
#include "block_reader.hpp"
#include "worldgenregion.hpp"
#include "block.hpp"

#include <stdint.hpp>
#include <glm/ext.hpp>

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

enum Biomes {
    Rainforest,
    Swampland,
    Seasonal_forest,
    Forest,
    Savanna,
    Shrubland,
    Taiga,
    Desert,
    Plains,
    IceDesert,
    Tundra,
};

struct BiomeResult {
    double *temperature;
    double *humidity;
    Biomes *biomes;
};


struct TerrainResult {
    BiomeResult *biomeResult;
    uint8 *chunkHeights;
};


extern TerrainResult *TerrainWrapper(uint64 worldSeed, int32_t chunkX, int32_t chunkZ);

struct PermutationTable {
    double xo;
    double yo;
    double zo;
    uint8 permutations[256];
};

void generateTerrain(Chunk* chunk, int32 chunk_x, int32 chunk_z) {
	Random random;
	random.setBaseChunkSeed(chunk_x, chunk_z);

	int32 start_x = chunk_x << 4;
	int32 start_z = chunk_z << 4;

    for (int32 x = start_x; x < start_x + 16; x++) {
        for (int32 z = start_z; z < start_z + 16; z++) {
            f32 noise = getNoiseValue(x, z);
            int32 height = noise * 60 + 40;

            chunk->heightmap[x & 15][z & 15] = height;

            for (int32 y = 0; y < height; y++) {
                chunk->setBlock(x, y, z, {Block::grass, 0});
            }

            for (int32 y = height; y < 68; y++) {
                chunk->setBlock(x, y, z, {Block::water, 0});
            }
        }
    }
}

void generateTree(Chunk* chunk, int32 x, int32 z, IBlockReader auto& blocks, Random& random) {
	int32 height = chunk->heightmap[x & 15][z & 15];

	int32 treeHeight = 4 + random.nextInt(0, 2);

	for (int32 y = treeHeight - 2; y <= treeHeight + 1; y++) {
        blocks.setBlock(x - 1, y + height, z - 1, {Block::leaves, 0});
        blocks.setBlock(x + 0, y + height, z - 1, {Block::leaves, 0});
        blocks.setBlock(x + 1, y + height, z - 1, {Block::leaves, 0});

        blocks.setBlock(x - 1, y + height, z, {Block::leaves, 0});
        blocks.setBlock(x + 0, y + height, z, {Block::leaves, 0});
        blocks.setBlock(x + 1, y + height, z, {Block::leaves, 0});

        blocks.setBlock(x - 1, y + height, z + 1, {Block::leaves, 0});
        blocks.setBlock(x + 0, y + height, z + 1, {Block::leaves, 0});
        blocks.setBlock(x + 1, y + height, z + 1, {Block::leaves, 0});
	}

	for (int32 y = height; y < height + treeHeight; y++) {
        blocks.setBlock(x, y, z, {Block::log, 0});
	}
}

void generateFeatures(Chunk* chunk, IBlockReader auto& blocks, int32 chunk_x, int32 chunk_z, int64 worldSeed) {
	Random random;
	auto seed = random.setDecorationSeed(worldSeed, (chunk_x << 4), (chunk_z << 4));

    for (int32 x = 0; x < 16; x++) {
        for (int32 z = 0; z < 16; z++) {
			random.setFeatureSeed(seed, x + (chunk_x << 4), z + (chunk_z << 4));

            int32 height = chunk->heightmap[x][z];

            if (height > 68) {
				int32 n = random.nextInt(0, 3000);

				if (n < 15) {
					generateTree(chunk, (chunk_x << 4) + x, (chunk_z << 4) + z, blocks, random);
				} else if (n < 40) {
                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {Block::red_flower, 0});
				} else if (n < 80) {
                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {Block::yellow_flower, 0});
				} else if (n < 200) {
                    blocks.setBlock((chunk_x << 4) + x, height, (chunk_z << 4) + z, {Block::tallgrass, 0});
				}
			}
        }
    }
}


template void generateFeatures(Chunk* chunk, WorldGenRegion<8ul>& blocks, int32 chunk_x, int32 chunk_z, int64 worldSeed);