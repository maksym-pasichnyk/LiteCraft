#pragma once

#include <stdint.hpp>
#include <glm/vec2.hpp>
#include <array>

#include "Chunk.hpp"
#include "Block.hpp"

struct WorldGenRegion {
    int32 radius;
	int32 size;
	int32 chunk_x;
	int32 chunk_z;
	glm::ivec2 bounds_min{};
	glm::ivec2 bounds_max{};
	std::vector<Chunk*> chunks;

	WorldGenRegion(int32_t radius, int32 chunk_x, int32 chunk_z)
	    : radius(radius)
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

	auto toIndex(int32 x, int32 z) const -> usize {
		return (x - bounds_min.x) + (z - bounds_min.y) * size;
	}

	auto chunkExists(int32 x, int32 z) const -> bool {
		return bounds_min.x <= x && x <= bounds_max.x && bounds_min.y <= z && z <= bounds_max.y;
	}

	auto getChunk(int32 x, int32 z) const -> Chunk* {
		if (chunkExists(x, z)) {
			return chunks[toIndex(x, z)];
		}
		return nullptr;
	}

    auto getBlock(int32 x, int32 y, int32 z) const -> BlockLayers {
        return getChunk(x >> 4, z >> 4)->getBlock(x, y, z);
    }

    auto getBlock(glm::ivec3 pos) const -> BlockLayers {
        return getBlock(pos.x, pos.y, pos.z);
    }

    void setBlock(int32 x, int32 y, int32 z, BlockLayers blockLayers) {
        getChunk(x >> 4, z >> 4)->setBlock(x, y, z, blockLayers);
    }

//    void setBlock(glm::ivec3 pos, Block* block) {
//        setBlock(pos.x, pos.y, pos.z, block);
//    }

    auto getMainChunk() const -> Chunk* {
		return chunks[(radius * (radius + 1)) << 1];
    }
};