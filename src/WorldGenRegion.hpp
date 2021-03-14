#pragma once

#include "world/biome/BiomeMagnifier.hpp"
#include "world/biome/FuzzedBiomeMagnifier.hpp"
#include "world/WorldReader.hpp"
#include "block/BlockData.hpp"
#include "util/math/ChunkPos.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <array>
#include <span>

struct Block;
struct ServerWorld;

struct WorldGenRegion : WorldReader {
    ServerWorld* world;
    int64_t seed;
    int32_t radius;
	int32_t size;
	int32_t chunk_x;
	int32_t chunk_z;

	glm::ivec2 chunks_min{};
	glm::ivec2 chunks_max{};

    glm::ivec2 bounds_min{};
    glm::ivec2 bounds_max{};
    std::span<Chunk*> chunks;

    BiomeMagnifier magnifier;

	WorldGenRegion(ServerWorld* world, std::span<Chunk*> chunks, int32_t radius, int32_t chunk_x, int32_t chunk_z, int64_t seed)
	    : world(world)
	    , seed(seed)
        , radius(radius)
	    , size(radius * 2 + 1)
	    , chunk_x(chunk_x)
	    , chunk_z(chunk_z)
	    , chunks(chunks)
    {
        chunks_min.x = chunk_x - radius;
        chunks_min.y = chunk_z - radius;
        chunks_max.x = chunk_x + radius;
        chunks_max.y = chunk_z + radius;

        bounds_min.x = chunks_min.x << 4;
        bounds_min.y = chunks_min.y << 4;
        bounds_max.x = (chunks_max.x << 4) + 15;
        bounds_max.y = (chunks_max.y << 4) + 15;

        magnifier = FuzzedBiomeMagnifier::getBiome;
	}

	auto toIndex(int32_t x, int32_t z) const -> size_t {
		return (x - chunks_min.x) + (z - chunks_min.y) * size;
	}

	auto chunkExists(int32_t x, int32_t z) const -> bool {
		return chunks_min.x <= x && x <= chunks_max.x && chunks_min.y <= z && z <= chunks_max.y;
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

	auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block*;

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData;

    auto getData(glm::ivec3 pos) const -> BlockData {
        return getData(pos.x, pos.y, pos.z);
    }

    void setData(int32_t x, int32_t y, int32_t z, BlockData blockData);

    void setData(glm::ivec3 pos, BlockData blockData) {
        setData(pos.x, pos.y, pos.z, blockData);
    }

    void setLight(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val);

    void setLight(glm::ivec3 pos, int32_t channel, int32_t val) {
        setLight(pos.x, pos.y, pos.z, channel, val);
    }

    auto getLight(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t;

    auto getLight(glm::ivec3 pos, int32_t channel) const -> int32_t {
        return getLight(pos.x, pos.y, pos.z, channel);
    }

    auto getLightPacked(int32_t x, int32_t y, int32_t z) const -> int32_t;

    auto getLightPacked(glm::ivec3 pos) const -> int32_t {
        return getLightPacked(pos.x, pos.y, pos.z);
    }

    auto getMainChunk() const -> Chunk* {
		return chunks[(radius * (radius + 1)) << 1];
    }

    auto getBiome(glm::ivec3 pos) -> Biome* {
        return getBiome(pos.x, pos.y, pos.z);
    }

    auto getBiome(int32_t x, int32_t y, int32_t z) -> Biome* {
        return magnifier(seed, x, y, z, *this);
    }

    auto getSeed() const -> int64_t {
	    return seed;
	}

    auto getTopBlockY(/*type, */int32_t x, int32_t z) -> int32_t;

    auto getHeight(/*type, */int32_t x, int32_t z) -> int32_t;

    Chunk *getChunk(int x, int z, ChunkState requiredStatus, bool nonnull) override {
        return nullptr;
    }

    Biome *getNoiseBiomeRaw(int x, int y, int z) override;
};