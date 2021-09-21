#pragma once

#include "biome/BiomeReader.hpp"
#include "BlockReader.hpp"

struct Chunk;
struct ChunkStatus;

struct WorldReader : virtual BiomeReader, virtual BlockReader {
    virtual Chunk* getChunk(int x, int z, ChunkStatus* requiredStatus, bool nonnull) = 0;
    virtual Biome* getNoiseBiomeRaw(int x, int y, int z) = 0;

    Biome *getNoiseBiome(int x, int y, int z) final {
//        auto chunk = getChunk(x >> 2, z >> 2, ChunkState::Biomes, false);
        return getNoiseBiomeRaw(x, y, z);
    }

    bool hasWater(const BlockPos& pos) const;
    bool isAirBlock(const BlockPos& pos) const;
    bool isLiquidBlock(const BlockPos& pos) const;
};