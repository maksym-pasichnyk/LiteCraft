#pragma once

#include "NetworkManager.hpp"
#include "PacketManager.hpp"
#include "world/ServerWorld.hpp"
#include "util/math/ChunkPos.hpp"

#include <thread>
#include <memory>

struct CraftServer {
    PacketManager<CraftServer, 10> packetManager;

    NetworkConnection connection;
    std::unique_ptr<ServerWorld> world = nullptr;
    std::vector<std::jthread> workers{};
    ChunkPos last_player_position{};

    std::stop_source stop_source;

    explicit CraftServer(NetworkConnection connection);

    ~CraftServer() {
        stop_source.request_stop();
        workers.clear();
    }

    void runLoop(std::stop_token&& token);

    void processSpawnPlayer(const SSpawnPlayerPacket& packet);
    void processPlayerPosition(const PositionPacket& packet);
    void processPlayerDigging(const CPlayerDiggingPacket& packet);
};