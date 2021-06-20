#pragma once

#include "WorldReader.hpp"
#include "WorldWriter.hpp"
#include "gen/Heightmap.hpp"
#include "biome/BiomeMagnifier.hpp"
#include "biome/FuzzedBiomeMagnifier.hpp"
#include "../block/BlockData.hpp"
#include "../util/math/ChunkPos.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <memory>
#include <array>
#include <span>
#include <cassert>

struct ServerWorld;

struct WorldGenRegion : virtual WorldReader, virtual WorldWriter {
    WorldGenRegion(const WorldGenRegion&) = delete;
    WorldGenRegion& operator=(const WorldGenRegion&) = delete;

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
    std::span<std::weak_ptr<Chunk>> chunks;

    BiomeMagnifier magnifier;

	WorldGenRegion(ServerWorld* world, std::span<std::weak_ptr<Chunk>> chunks, int32_t radius, int32_t chunk_x, int32_t chunk_z, int64_t seed)
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
		    assert(!chunks[toIndex(x, z)].expired());
			return chunks[toIndex(x, z)].lock().get();
		}
		return nullptr;
	}

	auto getBlock(int32_t x, int32_t y, int32_t z) const -> Block*;

    auto getData(int32_t x, int32_t y, int32_t z) const -> BlockData;

    auto getData(const BlockPos& pos) const -> BlockData override {
        return getData(pos.x, pos.y, pos.z);
    }

    bool setData(int32_t x, int32_t y, int32_t z, BlockData data);

    bool setData(const BlockPos& pos, BlockData data) override {
        return setData(pos.x, pos.y, pos.z, data);
    }

    void setLightFor(int32_t x, int32_t y, int32_t z, int32_t channel, int32_t val);

    void setLightFor(const BlockPos& pos, int32_t channel, int32_t val) {
        setLightFor(pos.x, pos.y, pos.z, channel, val);
    }

    auto getLightFor(int32_t x, int32_t y, int32_t z, int32_t channel) const -> int32_t;

    auto getLightFor(const BlockPos& pos, int32_t channel) const -> int32_t {
        return getLightFor(pos.x, pos.y, pos.z, channel);
    }

    auto getBiome(BlockPos pos) -> Biome* {
        return getBiome(pos.x, pos.y, pos.z);
    }

    auto getBiome(int32_t x, int32_t y, int32_t z) -> Biome* {
        return magnifier(seed, x, 0, z, *this);
    }

    auto getSeed() const -> int64_t {
	    return seed;
	}

	int getSeaLevel() const {
        return 63;
    }
	int getMaxBuildHeight() const {
        return 256; // dimensionHeight
    }

//    auto getTopBlockY(/*type, */int32_t x, int32_t z) -> int32_t;

//    auto getHeight(/*type, */int32_t x, int32_t z) -> int32_t;

    Chunk *getChunk(int x, int z, ChunkStatus const* requiredStatus, bool nonnull) override {
        return nullptr;
    }

    Biome *getNoiseBiomeRaw(int x, int y, int z) override;

    int getHeight(HeightmapType type, int x, int z);
    BlockPos getHeight(HeightmapType type, const BlockPos& pos) {
        return BlockPos(pos.x, getHeight(type, pos.x, pos.z), pos.z);
    }
    int32_t getBlockLight(const BlockPos& pos) const override;
};