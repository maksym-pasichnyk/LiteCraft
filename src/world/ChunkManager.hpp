#pragma once

#include "light/WorldLightManager.hpp"
#include "chunk/ChunkStatus.hpp"
#include "../util/math/ChunkPos.hpp"

#include <memory>
#include <span>
#include <map>

struct Chunk;
struct ServerWorld;
struct ChunkGenerator;
struct WorldLightManager;
struct ChunkManager {
    ServerWorld* world;
    ChunkGenerator* generator;
    std::unique_ptr<WorldLightManager> lightManager;
    std::map<int64_t, std::unique_ptr<Chunk>> chunks{};
    int viewDistance = 8;

    ChunkManager(ServerWorld* world, ChunkGenerator* generator);

    static auto getChunkDistance(ChunkPos chunkPos, int chunk_x, int chunk_z) -> int {
        return std::max(std::abs(chunkPos.x - chunk_x), std::abs(chunkPos.z - chunk_z));
    }

    void setChunkLoadedAtClient(int chunk_x, int chunk_z, bool wasLoaded, bool needLoad);
    void updatePlayerPosition(ChunkPos newChunkPos, ChunkPos oldChunkPos);
    bool fillChunks(std::span<Chunk*> _chunks, int32_t radius, int32_t chunk_x, int32_t chunk_z, ChunkStatus const* status);
    auto chunkLoad(int32_t chunk_x, int32_t chunk_z) -> Chunk*;
    auto provideChunk(int32_t chunk_x, int32_t chunk_z, ChunkStatus const* required = &ChunkStatus::Full) -> Chunk*;
    void setPlayerTracking(ChunkPos pos, bool track);
};
