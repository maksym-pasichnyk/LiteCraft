#pragma once

#include <stdint.hpp>
#include <glm/vec2.hpp>
#include <array>

#include "chunk.hpp"
#include "tile.hpp"

template <usize Size>
struct WorldGenRegion {
	int32 radius = Size * 2 + 1;
	int32 chunk_x;
	int32 chunk_z;
	glm::ivec2 bounds_min{};
	glm::ivec2 bounds_max{};
	std::array<Chunk*, (Size * 2 + 1) * (Size * 2 + 1)> chunks;

	WorldGenRegion(int32 chunk_x, int32 chunk_z) : chunk_x(chunk_x), chunk_z(chunk_z) {
		bounds_min.x = chunk_x - Size;
		bounds_min.y = chunk_z - Size;
		bounds_max.x = chunk_x + Size;
		bounds_max.y = chunk_z + Size;
	}

	auto toIndex(int32 x, int32 z) const -> usize {
		return (x - bounds_min.x) + (z - bounds_min.y) * radius;
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

    auto getTile(int32 x, int32 y, int32 z) const -> Tile* {
        return getChunk(x >> 4, z >> 4)->getTile(x, y, z) ?: Tile::air;
    }

	void setTile(int32 x, int32 y, int32 z, Tile* tile) {
        return getChunk(x >> 4, z >> 4)->setTile(x, y, z, tile);
    }

    auto getMainChunk() const -> Chunk* {
		return chunks[(Size * (Size + 1)) << 1];
    }
};