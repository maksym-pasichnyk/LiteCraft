#include "CraftServer.hpp"
#include "world/ServerWorld.hpp"
#include "world/ChunkManager.hpp"

#include <functional>

CraftServer::CraftServer(NetworkConnection connection) : connection(connection) {
    packetManager.bind<SSpawnPlayerPacket, &CraftServer::processSpawnPlayer>();
    packetManager.bind<PositionPacket, &CraftServer::processPlayerPosition>();
    packetManager.bind<CPlayerDiggingPacket, &CraftServer::processPlayerDigging>();

    world = std::make_unique<ServerWorld>(this);

    workers.emplace_back(&CraftServer::runLoop, this, stop_source.get_token());
}

void CraftServer::runLoop(std::stop_token &&token) {
    while (!token.stop_requested()) {
        packetManager.handlePackets(this, connection);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

    std::array<Chunk*, 9> _chunks{};
    world->manager->fillChunks(_chunks, 1, pos.x >> 4, pos.z >> 4, &ChunkStatus::Full);
    WorldGenRegion region{world.get(), _chunks, 1, pos.x >> 4, pos.z >> 4, world->seed};

    const auto AIR = Blocks::AIR->getDefaultState();
    const auto old = region.getData(pos);
    if (region.setData(pos, AIR)) {
        world->manager->lightManager->update(region, pos.x, pos.y, pos.z, old, AIR);

        connection.sendPacket(SChangeBlockPacket{
            .pos = pos,
            .data = AIR
        });
    } else {
        connection.sendPacket(SChangeBlockPacket{
            .pos = pos,
            .data = old
        });
    }
}