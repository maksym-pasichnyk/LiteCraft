#include "CraftServer.hpp"
#include "world/ServerWorld.hpp"
#include "world/ChunkManager.hpp"

#include <functional>

// todo: fix cleanup crash (wait for chunk tasks finished? check around chunks?)

CraftServer::CraftServer(std::shared_ptr<NetworkConnection> connection, int viewDistance) : connection(std::move(connection)), viewDistance(viewDistance) {
    packetManager.bind<SSpawnPlayerPacket, &CraftServer::processSpawnPlayer>();
    packetManager.bind<PositionPacket, &CraftServer::processPlayerPosition>();
    packetManager.bind<CPlayerDiggingPacket, &CraftServer::processPlayerDigging>();
    packetManager.bind<SChangeBlockPacket, &CraftServer::processChangeBlock>();

    workers.emplace_back(&CraftServer::runLoop, this, stop_source.get_token());
}

void CraftServer::runLoop(std::stop_token &&token) {
    try {
        world = std::make_unique<ServerWorld>(this, viewDistance);

        while (!token.stop_requested()) {
            packetManager.handlePackets(this, *connection);
            world->manager->tick();

            const auto stride = (world->manager->viewDistance + 10 + 2) * 2 + 1;
            if (world->manager->holders.size() > stride * stride) {
                std::erase_if(world->manager->holders, [this](auto &it) {
                    const auto pos = ChunkPos::from(it.first);
                    const auto distance = ChunkManager::getChunkDistance(last_player_position, pos);
                    if (distance > (world->manager->viewDistance + 10)) {
                        for (size_t i = 0; i < 7; ++i) {
//                            if (it.second->chunks[i].has_value()) {
//                                fmt::print("{}\n", it.second->chunks[i]->get().use_count());
//                                fmt::print("{}\n", it.second->chunks[i]->get().use_count());
//                                fmt::print("\n");
//                            }
                            if (it.second->chunks[i].has_value() && !it.second->chunks[i]->ready()) {
                                return false;
                            }
                        }
                        return true;
                    }
                    return false;
                });
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    } catch (const std::exception& e) {
        fmt::print("{}", e.what());
    }
}

void CraftServer::processSpawnPlayer(const SSpawnPlayerPacket &packet) {
    last_player_position = ChunkPos::from(glm::ivec3(packet.pos));
    world->manager->setPlayerTracking(last_player_position, true);
}

void CraftServer::processPlayerPosition(const PositionPacket &packet) {
    const auto pos = ChunkPos::from(glm::ivec3(packet.pos));

    if (last_player_position != pos) {
        world->manager->updatePlayerPosition(pos, last_player_position);
        last_player_position = pos;
    }
}

void CraftServer::processPlayerDigging(const CPlayerDiggingPacket& packet) {
    const auto pos = packet.pos;

    const auto [chunk_x, chunk_z] = ChunkPos::from(pos);

    auto chunk = world->getChunk(chunk_x, chunk_z);
    if (chunk != nullptr) {
        const auto new_block = Blocks::AIR->getDefaultState();
        const auto old_block = chunk->getData(pos);
        if (chunk->setData(pos, new_block)) {
            world->manager->lightManager->update(*world, pos.x, pos.y, pos.z, old_block, new_block);

            connection->sendPacket(SChangeBlockPacket{
                .pos = pos,
                .data = new_block
            });
        } else {
            connection->sendPacket(SChangeBlockPacket{
                .pos = pos,
                .data = old_block
            });
        }
    }
}

void CraftServer::processChangeBlock(const SChangeBlockPacket &packet) {
    const auto pos = packet.pos;

    const auto [chunk_x, chunk_z] = ChunkPos::from(pos);

    auto chunk = world->getChunk(chunk_x, chunk_z);
    if (chunk != nullptr) {
        const auto new_block = packet.data;
        const auto old_block = chunk->getData(pos);
        if (chunk->setData(pos, new_block)) {
            world->manager->lightManager->update(*world, pos.x, pos.y, pos.z, old_block, new_block);

            connection->sendPacket(SChangeBlockPacket{
                .pos = pos,
                .data = new_block
            });
        } else {
            connection->sendPacket(SChangeBlockPacket{
                .pos = pos,
                .data = old_block
            });
        }
    }
}
