#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <array>

#include "world/chunk/Chunk.hpp"
#include "block/Block.hpp"

struct Biome;

struct WorldGenRegion {
    int64_t seed;
    int32_t radius;
	int32_t size;
	int32_t chunk_x;
	int32_t chunk_z;

	glm::ivec2 bounds_min{};
	glm::ivec2 bounds_max{};
    std::span<Chunk*> chunks;

	WorldGenRegion(std::span<Chunk*> chunks, int32_t radius, int32_t chunk_x, int32_t chunk_z, int64_t seed)
	    : seed(seed)
        , radius(radius)
	    , size(radius * 2 + 1)
	    , chunk_x(chunk_x)
	    , chunk_z(chunk_z)
	    , chunks(chunks)
    {
		bounds_min.x = chunk_x - radius;
		bounds_min.y = chunk_z - radius;
		bounds_max.x = chunk_x + radius;
		bounds_max.y = chunk_z + radius;
	}

	auto toIndex(int32_t x, int32_t z) const -> size_t {
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

	auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block* {
        return Block::id_to_block[(int) getData(x, y, z).id];
	}

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData {
	    if (y < 0 || y > 255) {
	        return {};
	    }
        return getChunk(x >> 4, z >> 4)->getData(x, y, z);
    }

    auto getData(glm::ivec3 pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

    void setData(int32_t x, int32_t y, int32_t z, BlockData blockData) {
        getChunk(x >> 4, z >> 4)->setData(x, y, z, blockData);
    }

    void setData(glm::ivec3 pos, BlockData blockData) {
        setData(pos.x, pos.y, pos.z, blockData);
    }

    void setLight(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val) {
        getChunk(x >> 4, z >> 4)->setLight(x, y, z, channel, val);
    }

    void setLight(glm::ivec3 pos, int32_t channel, int32_t val) {
        setLight(pos.x, pos.y, pos.z, channel, val);
    }

    auto getLight(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t {
        return getChunk(x >> 4, z >> 4)->getLight(x, y, z, channel);
    }

    auto getLight(glm::ivec3 pos, int32_t channel) const -> int32_t {
        return getLight(pos.x, pos.y, pos.z, channel);
    }

    auto getLightPacked(int32_t x, int32_t y, int32_t z) const -> int32_t {
        return getChunk(x >> 4, z >> 4)->getLightPacked(x, y, z);
    }

    auto getLightPacked(glm::ivec3 pos) const -> int32_t {
        return getLightPacked(pos.x, pos.y, pos.z);
    }

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

    auto getTopBlockY(/*type, */int32_t x, int32_t z) -> int32_t {
        return getChunk(x >> 4, z >> 4)->getTopBlockY(x, z);
    }

    auto getHeight(/*type, */int32_t x, int32_t z) -> int32_t {
        return getChunk(x >> 4, z >> 4)->getHeight(x, z);
    }
};