#pragma once

#include "biome/BiomeReader.hpp"

enum class ChunkState;

struct Chunk;

struct WorldReader : virtual BiomeReader {
    virtual Chunk* getChunk(int x, int z, ChunkState requiredStatus, bool nonnull) = 0;
    virtual Biome* getNoiseBiomeRaw(int x, int y, int z) = 0;

    Biome *getNoiseBiome(int x, int y, int z) final {
//        auto chunk = getChunk(x >> 2, z >> 2, ChunkState::Biomes, false);
        return getNoiseBiomeRaw(x, y, z);
    }
};