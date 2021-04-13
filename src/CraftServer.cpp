#include "CraftServer.hpp"
#include "world/ServerWorld.hpp"
#include "world/ChunkManager.hpp"

#include <functional>

CraftServer::CraftServer(NetworkConnection connection) : connection(connection) {
    workers.emplace_back(std::bind_front(&CraftServer::runWorker, this));
    world = std::make_unique<ServerWorld>(this);
}

void CraftServer::executor_execute() {
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

                last_player_position = ChunkPos::from(glm::ivec3(packet.pos));
                world->manager->setPlayerTracking(last_player_position, true);
                break;
            }
            case 2: {
                PositionPacket packet{};
                while (read(connection.fd, &packet, header.size) < 0) {
                }

                const auto player_pos = ChunkPos::from(glm::ivec3(packet.pos));

                if (last_player_position != player_pos) {
                    world->manager->updatePlayerPosition(player_pos, last_player_position);
                    last_player_position = player_pos;
                }
                break;
            }
            case 3: {
                SChangeBlockPacket packet{};
                while (read(connection.fd, &packet, header.size) < 0) {
                }

                const auto pos = packet.pos;

                std::array<Chunk*, 9> _chunks{};
                world->manager->fillChunks(_chunks, 1, pos.x >> 4, pos.z >> 4, &ChunkStatus::Full);
                WorldGenRegion region{world.get(), _chunks, 1, pos.x >> 4, pos.z >> 4, world->seed};

                const auto old = region.getData(pos);
                if (region.setData(pos, packet.data)) {
                    world->manager->lightManager->update(region, pos.x, pos.y, pos.z, old, packet.data);

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
}
