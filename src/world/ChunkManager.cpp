#include "ChunkManager.hpp"
#include "ServerWorld.hpp"
#include "../CraftServer.hpp"

#include <memory>
#include <Iter.hpp>

//todo: remove promise.hpp lib
//todo: task chain
//todo: merge tasks
//todo: promise allocator
//todo: priority queue
//todo: save/load from file
//todo: chunk allocator

ChunkManager::ChunkManager(ServerWorld *world, ChunkGenerator *generator, TemplateManager* templates)
    : world(world)
    , generator(generator)
    , templates(templates)
    , viewDistance(world->viewDistance) {}

void ChunkManager::tick(Connection & connection) {
//    while (auto pos = complete.try_pop()) {
//        const auto [x, z] = *pos;
//        auto chunk = getChunk(x, z).get();
//
//        if (connection.send(SLoadChunkPacket{chunk, x, z})) {
//            continue;
//        }
//        complete.emplace(*pos);
//        break;
//    }
}

void ChunkManager::setChunkLoadedAtClient(Connection& connection, int chunk_x, int chunk_z, bool wasLoaded, bool needLoad) {
    if (wasLoaded && !needLoad) {
        connection.send(SUnloadChunkPacket{chunk_x, chunk_z});
    } else if (needLoad && !wasLoaded) {
        if (auto chunk = getChunk(chunk_x, chunk_z)) {
            connection.send(SLoadChunkPacket{chunk->to_json(), chunk_x, chunk_z});
        }
    }
}

void ChunkManager::updatePlayerPosition(Connection & connection, const ChunkPos& newChunkPos, const ChunkPos& oldChunkPos) {
    if (std::abs(newChunkPos.x - oldChunkPos.x) <= 2 * viewDistance && std::abs(newChunkPos.z - oldChunkPos.z) <= 2 * viewDistance) {
        const auto xStart = std::min(newChunkPos.x, oldChunkPos.x) - viewDistance;
        const auto zStart = std::min(newChunkPos.z, oldChunkPos.z) - viewDistance;
        const auto xEnd = std::max(newChunkPos.x, oldChunkPos.x) + viewDistance;
        const auto zEnd = std::max(newChunkPos.z, oldChunkPos.z) + viewDistance;

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

auto ChunkManager::getHolder(int32_t x, int32_t z) -> std::shared_ptr<ChunkHolder> {
    auto holder_ptr = holders[ChunkPos::asLong(x, z)];
    if (holder_ptr == nullptr) {
        holder_ptr = std::make_unique<ChunkHolder>(ChunkPos::from(x, z));
        holders[ChunkPos::asLong(x, z)] = holder_ptr;
    }
    return holder_ptr;
}

auto ChunkManager::getChunksAsync(int32_t range, int32_t chunk_x, int32_t chunk_z, ChunkStatus* status) -> std::vector<ChunkResult> {
    const auto stride = static_cast<size_t>(range * 2 + 1);

    std::vector<ChunkResult> results{};
    results.reserve(stride * stride);

    for (int32_t z = chunk_z - range; z <= chunk_z + range; z++) {
        for (int32_t x = chunk_x - range; x <= chunk_x + range; x++) {
            results.emplace_back(getChunkAsync(x, z, status));
        }
    }

    return std::move(results);
}

auto ChunkManager::getChunk(int32_t chunk_x, int32_t chunk_z, ChunkStatus *status) -> std::shared_ptr<Chunk> {
    auto result = getChunkAsync(chunk_x, chunk_z, status);
    return result.ready() ? result.get() : nullptr;
}

//ChunkResult ChunkManager::tryLoadFromFile(int32_t chunk_x, int32_t chunk_z) {
////    return executor.schedule([this, chunk_x, chunk_z]() mutable {
////        return std::make_shared<Chunk>(ChunkPos{chunk_x, chunk_z});
////    });
//
//    return promise_hpp::make_resolved_promise(std::make_shared<Chunk>(ChunkPos{chunk_x, chunk_z}));
//}

auto ChunkManager::generateChunk(int32_t chunk_x, int32_t chunk_z, ChunkStatus* status) -> ChunkResult {
    if (status == ChunkStatus::Empty) {
        return async::make_task(std::make_shared<Chunk>(ChunkPos::from(chunk_x, chunk_z))).share();
    }

    auto results = getChunksAsync(status->range, chunk_x, chunk_z, status->parent);

    return async::when_all(results).then(*executor, [this, status](const std::vector<ChunkResult>& results) {
        auto chunks = cpp_iter(results).map(&ChunkResult::get).collect();
        auto chunk = chunks[chunks.size() / 2];
        status->generate(world, *lightManager, *generator, *templates, chunk->coords.x, chunk->coords.z, *chunk, chunks, world->seed);
        if (status == ChunkStatus::Full) {
            complete.emplace(chunk->coords);
        }
        return chunk;
    }).share();
}

auto ChunkManager::getChunkAsync(int32_t chunk_x, int32_t chunk_z, ChunkStatus *status) -> ChunkResult {
    auto holder = getHolder(chunk_x, chunk_z);
    auto& result = holder->chunks[status->ordinal];
    if (!result.has_value()) {
        auto task = generateChunk(chunk_x, chunk_z, status);
        holder->updateChunkToSave(task);
        result.emplace(task);
    }
    return *result;
}

void ChunkManager::setPlayerTracking(Connection& connection, const ChunkPos& pos, bool track) {
    for (int32_t chunk_x = pos.x - viewDistance; chunk_x <= pos.x + viewDistance; chunk_x++) {
        for (int32_t chunk_z = pos.z - viewDistance; chunk_z <= pos.z + viewDistance; chunk_z++) {
            setChunkLoadedAtClient(connection, chunk_x, chunk_z, !track, track);
        }
    }
}