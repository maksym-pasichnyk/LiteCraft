#pragma once

#include "ChunkManager.hpp"
#include "gen/NoiseChunkGenerator.hpp"

#include <memory>

struct Biome;
struct CraftServer;
struct ChunkManager;
struct NoiseChunkGenerator;
struct ServerWorld {
    CraftServer* server;
    std::unique_ptr<ChunkManager> manager;
    std::unique_ptr<NoiseChunkGenerator> generator;
    int64_t seed = 1;

    explicit ServerWorld(CraftServer* server);

    Biome* getNoiseBiomeRaw(int x, int y, int z);
};