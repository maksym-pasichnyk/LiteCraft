#pragma once

#include <memory>
#include <thread>
#include <vector>
#include <map>

#include "WorldLightManager.hpp"
#include "world/gen/NoiseChunkGenerator.hpp"
#include "util/math/ChunkPos.hpp"

struct ServerWorld {
    NetworkConnection connection;
    NoiseChunkGenerator generator;
    WorldLightManager lightManager;

    std::vector<std::jthread> workers{};
    std::map<int64_t, std::unique_ptr<Chunk>> chunks{};

    ChunkPos last_player_position{};

    int64_t seed = 0;

    ServerWorld(NetworkConnection connection) : connection{connection} {
        workers.emplace_back(std::bind_front(&ServerWorld::runWorker, this));
    }

    ~ServerWorld() {
    	workers.clear();
    }

    static auto getChunkDistance(ChunkPos chunkPos, int chunk_x, int chunk_z) -> int {
        return std::max(std::abs(chunkPos.x - chunk_x), std::abs(chunkPos.z - chunk_z));
    }

    void setChunkLoadedAtClient(int chunk_x, int chunk_z, bool wasLoaded, bool needLoad) {
        if (wasLoaded && !needLoad) {
            connection.sendPacket(SUnloadChunkPacket{
                .x = chunk_x,
                .z = chunk_z
            });

            chunks.erase(ChunkPos::asLong(chunk_x, chunk_z));
        } else if (needLoad && !wasLoaded) {
            auto chunk = provideChunk(chunk_x, chunk_z, ChunkState::Full);
            if (chunk != nullptr) {
                connection.sendPacket(SLoadChunkPacket{
                    .chunk = chunk,
                    .x = chunk_x,
                    .z = chunk_z
                });
            }
        }
    }

    void updatePlayerPosition(ChunkPos newChunkPos, ChunkPos oldChunkPos) {
        if (std::abs(newChunkPos.x - oldChunkPos.x) <= 2 * 8 && std::abs(newChunkPos.z - oldChunkPos.z) <= 2 * 8) {
            const int xStart = std::min(newChunkPos.x, oldChunkPos.x) - 8;
            const int zStart = std::min(newChunkPos.z, oldChunkPos.z) - 8;
            const int xEnd = std::max(newChunkPos.x, oldChunkPos.x) + 8;
            const int zEnd = std::max(newChunkPos.z, oldChunkPos.z) + 8;

            for (int chunk_x = xStart; chunk_x <= xEnd; chunk_x++) {
                for (int chunk_z = zStart; chunk_z <= zEnd; chunk_z++) {
                    const bool wasLoaded = getChunkDistance(oldChunkPos, chunk_x, chunk_z) <= 8;
                    const bool needLoad = getChunkDistance(newChunkPos, chunk_x, chunk_z) <= 8;

                    setChunkLoadedAtClient(chunk_x, chunk_z, wasLoaded, needLoad);
                }
            }
        } else {
            for (int32_t chunk_x = oldChunkPos.x - 8; chunk_x <= oldChunkPos.x + 8; chunk_x++) {
                for (int32_t chunk_z = oldChunkPos.z - 8; chunk_z <= oldChunkPos.z + 8; chunk_z++) {
                    setChunkLoadedAtClient(chunk_x, chunk_z, true, false);
                }
            }

            for (int32_t chunk_x = newChunkPos.x - 8; chunk_x <= newChunkPos.x + 8; chunk_x++) {
                for (int32_t chunk_z = newChunkPos.z - 8; chunk_z <= newChunkPos.z + 8; chunk_z++) {
                    setChunkLoadedAtClient(chunk_x, chunk_z, false, true);
                }
            }
        }
    }

    void executor_execute() {
        while (true) {
            PacketHeader header{};
            if (read(connection.fd, &header, sizeof(PacketHeader)) <= 0) {
                break;
            }

            switch (header.id) {
                case 1: {
                    SpawnPlayerPacket packet{};
                    while (read(connection.fd, &packet, header.size) < 0) {
                    }

                    last_player_position = ChunkPos::from(
                        static_cast<int32_t>(packet.pos.x) >> 4,
                        static_cast<int32_t>(packet.pos.z) >> 4
                    );

                    for (int32_t chunk_x = last_player_position.x - 8; chunk_x <= last_player_position.x + 8; chunk_x++) {
                        for (int32_t chunk_z = last_player_position.z - 8; chunk_z <= last_player_position.z + 8; chunk_z++) {
                            setChunkLoadedAtClient(chunk_x, chunk_z, false, true);
                        }
                    }
                    break;
                }
                case 2: {
                    PositionPacket packet{};
                    while (read(connection.fd, &packet, header.size) < 0) {
                    }

                    const auto player_pos = ChunkPos::from(
                        static_cast<int32_t>(packet.pos.x) >> 4,
                        static_cast<int32_t>(packet.pos.z) >> 4
                    );

                    if (last_player_position != player_pos) {
                        updatePlayerPosition(player_pos, last_player_position);
                        last_player_position = player_pos;
                    }
                    break;
                }
                case 3: {
                    SChangeBlockPacket packet{};
                    while (read(connection.fd, &packet, header.size) < 0) {
                    }

                    const auto pos = packet.pos;

                    auto chunksInRadius = getChunksInRadius(1, pos.x >> 4, pos.z >> 4, ChunkState::Full);

                    WorldGenRegion region{*chunksInRadius, 1, pos.x >> 4, pos.z >> 4, seed};

                    auto old = region.getData(packet.pos);
                    region.setData(packet.pos, packet.data);

                    lightManager.update(region, pos.x, pos.y, pos.z, old, packet.data);

                    std::set<ChunkPos> positions;
                    for (int x = pos.x - 1; x <= pos.x + 1; x++) {
                        for (int z = pos.z - 1; z <= pos.z + 1; z++) {
                            positions.emplace(ChunkPos::from(x >> 4, z >> 4));
                        }
                    }

                    for (auto [x, z] : positions) {
                        region.getChunk(x, z)->needRender = true;
                    }
                }
            }
        }
    }

    void runWorker(std::stop_token&& token) {
        ChunkPos player_pos{};
        while (!token.stop_requested()) {
            executor_execute();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    auto getChunk(int32_t chunk_x, int32_t chunk_z, ChunkState state) -> Chunk* {
        const auto pos = ChunkPos::from(chunk_x, chunk_z);
        auto it = chunks.find(pos.asLong());
        if (it != chunks.end()) {
            auto chunk = it->second.get();
            if (chunk->state >= state) {
                return chunk;
            }
        }
        return nullptr;
    }

    auto getChunksInRadius(int32_t radius, int32_t chunk_x, int32_t chunk_z, ChunkState state) -> std::optional<std::vector<Chunk*>> {
        if (radius == -1) return {};

        const size_t count = radius * 2 + 1;
        std::vector<Chunk*> ret{count * count};

        size_t i = 0;
        for (int32_t z = chunk_z - radius; z <= chunk_z + radius; z++) {
            for (int32_t x = chunk_x - radius; x <= chunk_x + radius; x++) {
                auto chunk = provideChunk(x, z, state);
                if (chunk == nullptr) {
                    return std::nullopt;
                }
                ret.at(i++) = chunk;
            }
        }

        return std::move(ret);
    }

    auto getTaskRange(ChunkState state) {
        switch (state) {
            case ChunkState::Empty:
                return -1;
            case ChunkState::StructureStart:
                return 0;
            case ChunkState::StructureReferences:
                return 0;
            case ChunkState::Noise:
                return 0;
            case ChunkState::Surface:
                return 0;
            case ChunkState::Features:
                return 0;
            case ChunkState::Light:
                return 1;
            case ChunkState::Full:
                return 0;
        }
        return -1;
    }

    auto chunkLoad(int32_t chunk_x, int32_t chunk_z) -> Chunk* {
        const auto pos = ChunkPos::from(chunk_x, chunk_z);
        auto it = chunks.find(pos.asLong());
        if (it == chunks.end()) {
            it = chunks.emplace(pos.asLong(), std::make_unique<Chunk>(pos)).first;
        }
        return it->second.get();
    }

    auto provideChunk(int32_t chunk_x, int32_t chunk_z, ChunkState state = ChunkState::Full) -> Chunk* {
        auto chunk = chunkLoad(chunk_x, chunk_z);

        for (int i = (int) chunk->state + 1; i <= (int) state; i++) {
            const auto parent_state = (ChunkState) ((int) i - 1);
            const auto range = getTaskRange((ChunkState) i);
            auto chunksInRadius = getChunksInRadius(range, chunk_x, chunk_z, parent_state);

            WorldGenRegion region{*chunksInRadius, range, chunk_x, chunk_z, seed};

            switch ((ChunkState) i) {
                case ChunkState::Empty:
                    break;
                case ChunkState::StructureStart:
                    generator.generateStructures(region, *chunk);
                    break;
            case ChunkState::StructureReferences:
//                    generator.getStructureReferences(region, *chunk);
                    break;
                case ChunkState::Noise:
                    generator.generateTerrain(*chunk);
                    break;
                case ChunkState::Surface:
                    generator.generateSurface(region, *chunk);
                    break;
                case ChunkState::Features:
                    generator.generateFeatures(region, *chunk);
                    break;
                case ChunkState::Light:
                    lightManager.calculate(region, chunk_x * 16, chunk_z * 16);
                    break;
                case ChunkState::Full:
                    break;
            }

            chunk->state = (ChunkState) i;
        }
		return chunk;
    }
};
