#pragma once

#include "light/WorldLightManager.hpp"
#include "chunk/ChunkStatus.hpp"
#include "../util/generate_queue.hpp"
#include "../util/complete_queue.hpp"
#include "../util/math/ChunkPos.hpp"

#include "promise.hpp/promise.hpp"
#include "promise.hpp/scheduler.hpp"

#include <thread>
#include <memory>
#include <stack>
#include <span>
#include <map>
#include <mutex>
#include <future>
#include <algorithm>

#include <list>

struct Chunk;
struct ServerWorld;
struct ChunkGenerator;
struct WorldLightManager;

enum class ChunkGenerationStatus {
    None,
    Progress,
    Ready
};

using ChunkResult = promise_hpp::promise<std::weak_ptr<Chunk>>;

struct ChunkHolder {
    ChunkPos pos;

    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(pos);

    explicit ChunkHolder(ChunkPos pos) : pos(pos) {}

    std::array<std::optional<ChunkResult>, 7> chunks{};
};

struct ChunkManager {
    ServerWorld* world;
    ChunkGenerator* generator;
    std::unique_ptr<WorldLightManager> lightManager;

    scheduler_hpp::scheduler executor;

    complete_queue<ChunkPos> complete;
    std::map<int64_t, std::shared_ptr<ChunkHolder>> holders;

    int viewDistance = -1;

    std::stop_source stop_source;
    std::vector<std::thread> workers;

    ChunkManager(ServerWorld* world, ChunkGenerator* generator);
    ~ChunkManager() {
        stop_source.request_stop();
        std::ranges::for_each(workers, std::mem_fn(&std::thread::join));
        workers.clear();
        complete.clear();
        holders.clear();
    }

    static auto getChunkDistance(const ChunkPos& pos, int x, int z) -> int {
        return std::max(std::abs(pos.x - x), std::abs(pos.z - z));
    }
    static auto getChunkDistance(const ChunkPos& from, const ChunkPos& to) -> int {
        return std::max(std::abs(from.x - to.x), std::abs(from.z - to.z));
    }

    void tick();
    void runLoop(std::stop_token&& token);
    void setChunkLoadedAtClient(int chunk_x, int chunk_z, bool wasLoaded, bool needLoad);
    void updatePlayerPosition(ChunkPos newChunkPos, ChunkPos oldChunkPos);
    std::shared_ptr<ChunkHolder> getHolder(int32_t x, int32_t z);

    std::vector<ChunkResult> getChunksAsync(int32_t range, int32_t chunk_x, int32_t chunk_z, ChunkStatus const* status);
    std::shared_ptr<Chunk> getChunk(int32_t chunk_x, int32_t chunk_z, ChunkStatus const* status = &ChunkStatus::Full);

//    ChunkResult tryLoadFromFile(int32_t chunk_x, int32_t chunk_z);
    ChunkResult generateChunk(int32_t chunk_x, int32_t chunk_z, ChunkStatus const* status);
    ChunkResult getChunkAsync(int32_t chunk_x, int32_t chunk_z, ChunkStatus const* status = &ChunkStatus::Full);
    void setPlayerTracking(ChunkPos pos, bool track);
};
