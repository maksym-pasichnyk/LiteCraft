#include "ChunkManager.hpp"
#include "ServerWorld.hpp"
#include "gen/NoiseChunkGenerator.hpp"
#include "light/WorldLightManager.hpp"
#include "../CraftServer.hpp"

ChunkManager::ChunkManager(ServerWorld *world, ChunkGenerator *generator) : world(world), generator(generator) {
    lightManager = std::make_unique<WorldLightManager>();
}

void ChunkManager::setChunkLoadedAtClient(int chunk_x, int chunk_z, bool wasLoaded, bool needLoad) {
    if (wasLoaded && !needLoad) {
        world->server->connection.sendPacket(SUnloadChunkPacket{
                .x = chunk_x,
                .z = chunk_z
        });
        chunks.erase(ChunkPos::asLong(chunk_x, chunk_z));
    } else if (needLoad && !wasLoaded) {
        auto chunk = provideChunk(chunk_x, chunk_z, &ChunkStatus::Full);
        if (chunk != nullptr) {
            world->server->connection.sendPacket(SLoadChunkPacket{
                    .chunk = chunk,
                    .x = chunk_x,
                    .z = chunk_z
            });
        }
    }
}

void ChunkManager::updatePlayerPosition(ChunkPos newChunkPos, ChunkPos oldChunkPos) {
    if (std::abs(newChunkPos.x - oldChunkPos.x) <= 2 * viewDistance && std::abs(newChunkPos.z - oldChunkPos.z) <= 2 * viewDistance) {
        const int xStart = std::min(newChunkPos.x, oldChunkPos.x) - viewDistance;
        const int zStart = std::min(newChunkPos.z, oldChunkPos.z) - viewDistance;
        const int xEnd = std::max(newChunkPos.x, oldChunkPos.x) + viewDistance;
        const int zEnd = std::max(newChunkPos.z, oldChunkPos.z) + viewDistance;

        for (int chunk_x = xStart; chunk_x <= xEnd; chunk_x++) {
            for (int chunk_z = zStart; chunk_z <= zEnd; chunk_z++) {
                const bool wasLoaded = getChunkDistance(oldChunkPos, chunk_x, chunk_z) <= viewDistance;
                const bool needLoad = getChunkDistance(newChunkPos, chunk_x, chunk_z) <= viewDistance;

                setChunkLoadedAtClient(chunk_x, chunk_z, wasLoaded, needLoad);
            }
        }
    } else {
        for (int32_t chunk_x = oldChunkPos.x - viewDistance; chunk_x <= oldChunkPos.x + viewDistance; chunk_x++) {
            for (int32_t chunk_z = oldChunkPos.z - viewDistance; chunk_z <= oldChunkPos.z + viewDistance; chunk_z++) {
                setChunkLoadedAtClient(chunk_x, chunk_z, true, false);
            }
        }

        for (int32_t chunk_x = newChunkPos.x - viewDistance; chunk_x <= newChunkPos.x + viewDistance; chunk_x++) {
            for (int32_t chunk_z = newChunkPos.z - viewDistance; chunk_z <= newChunkPos.z + viewDistance; chunk_z++) {
                setChunkLoadedAtClient(chunk_x, chunk_z, false, true);
            }
        }
    }
}

bool ChunkManager::fillChunks(std::span<Chunk *> _chunks, int32_t radius, int32_t chunk_x, int32_t chunk_z,const ChunkStatus *status) {
    size_t i = 0;
    for (int32_t z = chunk_z - radius; z <= chunk_z + radius; z++) {
        for (int32_t x = chunk_x - radius; x <= chunk_x + radius; x++) {
            auto chunk = provideChunk(x, z, status);
            if (chunk == nullptr) {
                return false;
            }
            _chunks[i++] = chunk;
        }
    }
    return true;
}

auto ChunkManager::chunkLoad(int32_t chunk_x, int32_t chunk_z) -> Chunk * {
    const auto pos = ChunkPos::from(chunk_x, chunk_z);
    auto it = chunks.find(pos.asLong());
    if (it == chunks.end()) {
        it = chunks.emplace(pos.asLong(), std::make_unique<Chunk>(pos)).first;
    }
    return it->second.get();
}

auto ChunkManager::provideChunk(int32_t chunk_x, int32_t chunk_z, const ChunkStatus *required) -> Chunk * {
    auto chunk = chunkLoad(chunk_x, chunk_z);

    std::vector<Chunk*> _chunks{};
    for (int i = chunk->status + 1; i <= required->ordinal; i++) {
        auto status = ChunkStatus::getById(i);
        auto parent = ChunkStatus::getById(i - 1);
        auto count = (status->range * 2 + 1) * (status->range * 2 + 1);

        if (count > _chunks.size()) _chunks.resize(count);
        if (fillChunks(_chunks, status->range, chunk_x, chunk_z, parent)) {
            status->generate(world, *lightManager, *generator, chunk_x, chunk_z, *chunk, std::span(_chunks.data(), count), world->seed);
            chunk->status = i;
        }
    }
    return chunk;
}

void ChunkManager::setPlayerTracking(ChunkPos pos, bool track) {
    for (int32_t chunk_x = pos.x - viewDistance; chunk_x <= pos.x + viewDistance; chunk_x++) {
        for (int32_t chunk_z = pos.z - viewDistance; chunk_z <= pos.z + viewDistance; chunk_z++) {
            setChunkLoadedAtClient(chunk_x, chunk_z, !track, track);
        }
    }
}
