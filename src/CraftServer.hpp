#pragma once

#include "NetworkManager.hpp"
#include "PacketManager.hpp"
#include "world/ServerWorld.hpp"
#include "util/math/ChunkPos.hpp"

#include <thread>
#include <memory>

struct CraftServer {
    PacketManager<CraftServer, 10> packetManager;

    std::shared_ptr<NetworkConnection> connection;
    std::unique_ptr<ServerWorld> world = nullptr;
    std::vector<std::thread> workers{};
    ChunkPos last_player_position{};

    std::stop_source stop_source;
    int viewDistance = -1;

    explicit CraftServer(std::shared_ptr<NetworkConnection> connection, int viewDistance);

    ~CraftServer() {
        stop_source.request_stop();
        std::ranges::for_each(workers, std::mem_fn(&std::thread::join));
        workers.clear();

        world.reset();
    }

    void runLoop(std::stop_token&& token);

    void processSpawnPlayer(const SSpawnPlayerPacket& packet);
    void processPlayerPosition(const PositionPacket& packet);
    void processPlayerDigging(const CPlayerDiggingPacket& packet);
    void processChangeBlock(const SChangeBlockPacket& packet);
};