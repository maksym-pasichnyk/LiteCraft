#pragma once

#include <stdint.hpp>
#include <glm/vec2.hpp>
#include <array>

#include "Chunk.hpp"
#include "Block.hpp"

struct Biome;

struct WorldGenRegion {
    int64_t seed;
    int32_t radius;
	int32_t size;
	int32_t chunk_x;
	int32_t chunk_z;

	glm::ivec2 bounds_min{};
	glm::ivec2 bounds_max{};
	std::vector<Chunk*> chunks;

	WorldGenRegion(int32_t radius, int32_t chunk_x, int32_t chunk_z, int64_t seed)
	    : seed(seed)
        , radius(radius)
	    , size(radius * 2 + 1)
	    , chunk_x(chunk_x)
	    , chunk_z(chunk_z)
	    , chunks(size * size)
    {
		bounds_min.x = chunk_x - radius;
		bounds_min.y = chunk_z - radius;
		bounds_max.x = chunk_x + radius;
		bounds_max.y = chunk_z + radius;
	}

	auto toIndex(int32_t x, int32_t z) const -> usize {
		return (x - bounds_min.x) + (z - bounds_min.y) * size;
	}

	auto chunkExists(int32_t x, int32_t z) const -> bool {
		return bounds_min.x <= x && x <= bounds_max.x && bounds_min.y <= z && z <= bounds_max.y;
	}

    auto getMainChunkPos() const -> ChunkPos {
        return {chunk_x, chunk_z};
    }

	auto getChunk(int32_t x, int32_t z) const -> Chunk* {
		if (chunkExists(x, z)) {
			return chunks[toIndex(x, z)];
		}
		return nullptr;
	}

    auto getBlock(int32_t x, int32_t y, int32_t z) const -> BlockData {
        return getChunk(x >> 4, z >> 4)->getBlock(x, y, z);
    }

    auto getBlock(glm::ivec3 pos) const -> BlockData {
        return getBlock(pos.x, pos.y, pos.z);
    }

    void setBlock(int32_t x, int32_t y, int32_t z, BlockData blockData) {
        getChunk(x >> 4, z >> 4)->setBlock(x, y, z, blockData);
    }

//    void setBlock(glm::ivec3 pos, Block* block) {
//        setBlock(pos.x, pos.y, pos.z, block);
//    }

    auto getMainChunk() const -> Chunk* {
		return chunks[(radius * (radius + 1)) << 1];
    }

    auto getBiome(glm::ivec3 pos) -> Biome* {
        return nullptr;
    }

    auto getBiome(int32_t x, int32_t y, int32_t z) -> Biome* {
        return nullptr;
    }

    auto getSeed() const -> int64_t {
	    return seed;
	}
};