#pragma once

#include "light/WorldLightManager.hpp"
#include "chunk/ChunkStatus.hpp"
#include "../util/generate_queue.hpp"
#include "../util/complete_queue.hpp"
#include "../util/math/ChunkPos.hpp"

#include <map>
#include <list>
#include <span>
#include <stack>
#include <mutex>
#include <future>
#include <thread>
#include <memory>
#include <optional>
#include <async++.h>
#include <algorithm>
#include <range/v3/algorithm.hpp>

struct Chunk;
struct ServerWorld;
struct ChunkGenerator;
struct WorldLightManager;

enum class ChunkGenerationStatus {
    None,
    Progress,
    Ready
};

using ChunkResult = async::shared_task<std::shared_ptr<Chunk>>;

struct ChunkHolder {
    ChunkPos pos;
    ChunkResult chunkToSave = async::make_task<std::shared_ptr<Chunk>>(nullptr).share();
    std::array<std::optional<ChunkResult>, 10> chunks{};

    explicit ChunkHolder(const ChunkPos& pos) : pos(pos) {}

    void updateChunkToSave(ChunkResult task) {
        chunkToSave = async::when_all(std::move(chunkToSave), std::move(task))
                        .then([](const std::tuple<ChunkResult, ChunkResult>& results) {
                              return std::get<0>(results).get();
                        }).share();
    }
};

struct ThreadPool {
    ThreadPool(size_t thread_count = std::thread::hardware_concurrency()) {
        workers.reserve(thread_count);
        for (int i = 0; i < thread_count; ++i) {
            workers.emplace_back(&ThreadPool::loop, this, stop_source.get_token());
        }
    }

    ~ThreadPool() {
        stop_source.request_stop();
        signal.notify_all();
        std::for_each(workers.begin(), workers.end(), std::mem_fn(&std::thread::join));
        workers.clear();
    }

    void loop(std::stop_token &&token) {
        while (auto task = get_task(token)) {
            task->run();
        }
    }

    auto get_task(std::stop_token& token) -> std::optional<async::task_run_handle> {
        std::unique_lock lock{mutex};
        signal.wait(lock, [this, &token] {
            return !tasks.empty() || token.stop_requested();
        });
        if (token.stop_requested()) {
            return std::nullopt;
        }
        auto task = std::move(tasks.front());
        tasks.pop();
        return task;
    }

    void schedule(async::task_run_handle task) {
        {
            std::lock_guard _{mutex};
            tasks.emplace(std::move(task));
        }
        signal.notify_one();
    }

private:
    std::stop_source stop_source;
    std::vector<std::thread> workers{};

    std::mutex mutex{};
    std::condition_variable signal{};
    std::queue<async::task_run_handle> tasks{};
};

struct Connection;
struct ChunkManager {
    ServerWorld* world;
    ChunkGenerator* generator;
    TemplateManager* templates;
    std::unique_ptr<WorldLightManager> lightManager = std::make_unique<WorldLightManager>();
    std::unique_ptr<ThreadPool> executor = std::make_unique<ThreadPool>();

    complete_queue<ChunkPos> complete;
    std::map<int64_t, std::shared_ptr<ChunkHolder>> holders;

    int viewDistance = -1;

    ChunkManager(ServerWorld* world, ChunkGenerator* generator, TemplateManager* templates);
    ~ChunkManager() {
        executor.reset();
        complete.clear();
        holders.clear();
    }

    static auto getChunkDistance(const ChunkPos& pos, int x, int z) -> int {
        return std::max(std::abs(pos.x - x), std::abs(pos.z - z));
    }
    static auto getChunkDistance(const ChunkPos& from, const ChunkPos& to) -> int {
        return std::max(std::abs(from.x - to.x), std::abs(from.z - to.z));
    }

    void tick(Connection& connection);
    void setChunkLoadedAtClient(Connection & connection, int chunk_x, int chunk_z, bool wasLoaded, bool needLoad);
    void updatePlayerPosition(Connection & connection, const ChunkPos& newChunkPos, const ChunkPos& oldChunkPos);
    auto getHolder(int32_t x, int32_t z) -> std::shared_ptr<ChunkHolder>;

    auto getChunksAsync(int32_t range, int32_t chunk_x, int32_t chunk_z, ChunkStatus* status) -> std::vector<ChunkResult>;
    auto getChunk(int32_t chunk_x, int32_t chunk_z, ChunkStatus* status = ChunkStatus::Full) -> std::shared_ptr<Chunk>;

//    ChunkResult tryLoadFromFile(int32_t chunk_x, int32_t chunk_z);
    auto generateChunk(int32_t chunk_x, int32_t chunk_z, ChunkStatus* status) -> ChunkResult;
    auto getChunkAsync(int32_t chunk_x, int32_t chunk_z, ChunkStatus* status = ChunkStatus::Full) -> ChunkResult;
    void setPlayerTracking(Connection & connection, const ChunkPos& pos, bool track);
};
