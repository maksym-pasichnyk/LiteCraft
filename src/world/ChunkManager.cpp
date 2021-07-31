#include "ChunkManager.hpp"
#include "ServerWorld.hpp"
#include "gen/NoiseChunkGenerator.hpp"
#include "light/WorldLightManager.hpp"
#include "../CraftServer.hpp"

#include <future>
#include <memory>

//todo: task chain
//todo: merge tasks
//todo: promise allocator
//todo: priority queue
//todo: load from file
//todo: chunk allocator

ChunkManager::ChunkManager(ServerWorld *world, ChunkGenerator *generator)
    : world(world)
    , generator(generator)
    , lightManager(std::make_unique<WorldLightManager>())
    , viewDistance(world->viewDistance) {
    workers.emplace_back(&ChunkManager::runLoop, this, stop_source.get_token());
    workers.emplace_back(&ChunkManager::runLoop, this, stop_source.get_token());
    workers.emplace_back(&ChunkManager::runLoop, this, stop_source.get_token());
    workers.emplace_back(&ChunkManager::runLoop, this, stop_source.get_token());
}

void ChunkManager::runLoop(std::stop_token&& token) {
    while (!token.stop_requested()) {
        executor.process_all_tasks();
    }
}

void ChunkManager::tick(NetworkConnection& connection) {
    while (auto pos = complete.try_pop()) {
        const auto [x, z] = *pos;
        auto chunk = getChunk(x, z).get();

        if (connection.send(SLoadChunkPacket{chunk, x, z})) {
            continue;
        }
        complete.emplace(*pos);
        break;
    }
}

void ChunkManager::setChunkLoadedAtClient(NetworkConnection& connection, int chunk_x, int chunk_z, bool wasLoaded, bool needLoad) {
    if (wasLoaded && !needLoad) {
        connection.send(SUnloadChunkPacket{chunk_x, chunk_z});
    } else if (needLoad && !wasLoaded) {
        auto chunk = getChunk(chunk_x, chunk_z, &ChunkStatus::Full);
        if (chunk != nullptr) {
            connection.send(SLoadChunkPacket{chunk.get(), chunk_x, chunk_z});
        }
    }
}

void ChunkManager::updatePlayerPosition(NetworkConnection& connection, ChunkPos newChunkPos, ChunkPos oldChunkPos) {
    if (std::abs(newChunkPos.x - oldChunkPos.x) <= 2 * viewDistance && std::abs(newChunkPos.z - oldChunkPos.z) <= 2 * viewDistance) {
        const int xStart = std::min(newChunkPos.x, oldChunkPos.x) - viewDistance;
        const int zStart = std::min(newChunkPos.z, oldChunkPos.z) - viewDistance;
        const int xEnd = std::max(newChunkPos.x, oldChunkPos.x) + viewDistance;
        const int zEnd = std::max(newChunkPos.z, oldChunkPos.z) + viewDistance;

        for (int chunk_x = xStart; chunk_x <= xEnd; chunk_x++) {
            for (int chunk_z = zStart; chunk_z <= zEnd; chunk_z++) {
                const bool wasLoaded = getChunkDistance(oldChunkPos, chunk_x, chunk_z) <= viewDistance;
                const bool needLoad = getChunkDistance(newChunkPos, chunk_x, chunk_z) <= viewDistance;

                setChunkLoadedAtClient(connection, chunk_x, chunk_z, wasLoaded, needLoad);
            }
        }
    } else {
        for (int32_t chunk_x = oldChunkPos.x - viewDistance; chunk_x <= oldChunkPos.x + viewDistance; chunk_x++) {
            for (int32_t chunk_z = oldChunkPos.z - viewDistance; chunk_z <= oldChunkPos.z + viewDistance; chunk_z++) {
                setChunkLoadedAtClient(connection, chunk_x, chunk_z, true, false);
            }
        }

        for (int32_t chunk_x = newChunkPos.x - viewDistance; chunk_x <= newChunkPos.x + viewDistance; chunk_x++) {
            for (int32_t chunk_z = newChunkPos.z - viewDistance; chunk_z <= newChunkPos.z + viewDistance; chunk_z++) {
                setChunkLoadedAtClient(connection, chunk_x, chunk_z, false, true);
            }
        }
    }
}

std::shared_ptr<ChunkHolder> ChunkManager::getHolder(int32_t x, int32_t z) {
    auto holder_ptr = holders[ChunkPos::asLong(x, z)];
    if (holder_ptr == nullptr) {
        holder_ptr = std::make_unique<ChunkHolder>(ChunkPos::from(x, z));
        holders[ChunkPos::asLong(x, z)] = holder_ptr;
    }
    return holder_ptr;
}

std::vector<ChunkResult> ChunkManager::getChunksAsync(int32_t range, int32_t chunk_x, int32_t chunk_z, ChunkStatus const* status) {
    const size_t stride = range * 2 + 1;
    const size_t count = stride * stride;

    std::vector<ChunkResult> async_chunks{count};

    size_t i = 0;
    for (int32_t z = chunk_z - range; z <= chunk_z + range; z++) {
        for (int32_t x = chunk_x - range; x <= chunk_x + range; x++) {
            async_chunks[i++] = getChunkAsync(x, z, status);
        }
    }

    return std::move(async_chunks);
}

std::shared_ptr<Chunk> ChunkManager::getChunk(int32_t chunk_x, int32_t chunk_z, const ChunkStatus *status) {
    using namespace std::chrono_literals;

    auto async_chunk = getChunkAsync(chunk_x, chunk_z, status);
    return async_chunk.wait_for(0ms) == promise_hpp::promise_wait_status::no_timeout
           ? assert(!async_chunk.get().expired()), async_chunk.get().lock()
           : nullptr;
}

template <typename T>
struct when_all_result {
    std::atomic_size_t counter;
    std::vector<T> results;

    explicit when_all_result(size_t count) : counter(count), results(count) {}
};

//ChunkResult ChunkManager::tryLoadFromFile(int32_t chunk_x, int32_t chunk_z) {
////    return executor.schedule([this, chunk_x, chunk_z]() mutable {
////        return std::make_shared<Chunk>(ChunkPos{chunk_x, chunk_z});
////    });
//
//    return promise_hpp::make_resolved_promise(std::make_shared<Chunk>(ChunkPos{chunk_x, chunk_z}));
//}

ChunkResult ChunkManager::generateChunk(int32_t chunk_x, int32_t chunk_z, ChunkStatus const* status) {
    ChunkResult async_chunk;
    auto async_chunks = getChunksAsync(status->range, chunk_x, chunk_z, ChunkStatus::getById(status->ordinal - 1));

    auto result = std::make_shared<when_all_result<std::weak_ptr<Chunk>>>(async_chunks.size());
    for (size_t i = 0; i < async_chunks.size(); ++i) {
        async_chunks[i].then([this, status, i, result, async_chunk](std::weak_ptr<Chunk> chunk) mutable {
            assert(!chunk.expired());

            if (result->results[i] = std::move(chunk), (result->counter -= 1) == 0) {
                executor.schedule(/*scheduler_hpp::scheduler_priority::highest,*/ [this, status, chunks = std::move(result->results), async_chunk = std::move(async_chunk)]() mutable {
                    assert(!chunks[chunks.size() / 2].expired());
                    auto chunk = chunks[chunks.size() / 2].lock();
                    status->generate(world, *lightManager, *generator, chunk->pos.x, chunk->pos.z, *chunk, chunks, world->seed);

                    if (status->ordinal == ChunkStatus::Full.ordinal) {
                        complete.emplace(chunk->pos);
                    }

                    async_chunk.resolve(chunk);
                });
            }
        });
    }
    return std::move(async_chunk);
}

ChunkResult ChunkManager::getChunkAsync(int32_t chunk_x, int32_t chunk_z, const ChunkStatus *status) {
    auto holder = getHolder(chunk_x, chunk_z);
    auto& async_chunk = holder->chunks[status->ordinal];
    if (!async_chunk.has_value()) {
        if (status == &ChunkStatus::Empty) {
            async_chunk = promise_hpp::make_resolved_promise(std::weak_ptr(holder->chunk));
//            tryLoadFromFile(chunk_x, chunk_z);
        } else {
            async_chunk = generateChunk(chunk_x, chunk_z, status);
        }
    }
    return *async_chunk;
}

void ChunkManager::setPlayerTracking(NetworkConnection& connection, ChunkPos pos, bool track) {
    for (int32_t chunk_x = pos.x - viewDistance; chunk_x <= pos.x + viewDistance; chunk_x++) {
        for (int32_t chunk_z = pos.z - viewDistance; chunk_z <= pos.z + viewDistance; chunk_z++) {
            setChunkLoadedAtClient(connection, chunk_x, chunk_z, !track, track);
        }
    }
}