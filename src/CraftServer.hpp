#pragma once

#include "NetworkManager.hpp"
#include "PacketManager.hpp"
#include "world/ServerWorld.hpp"
#include "util/math/ChunkPos.hpp"

#include <range/v3/algorithm.hpp>
#include <thread>
#include <memory>

struct CraftServer {
    PacketManager<CraftServer> packetManager;

    std::vector<std::unique_ptr<NetworkConnection>> connections;

    std::unique_ptr<ServerWorld> world = nullptr;
    std::vector<std::thread> workers{};
    ChunkPos last_player_position{};
    TcpListener listener{};

    std::stop_source stop_source;
    int viewDistance = -1;

    explicit CraftServer(int viewDistance);

    ~CraftServer() {
        listener.close();
        stop_source.request_stop();
        ranges::for_each(workers, std::mem_fn(&std::thread::join));
        workers.clear();

        world.reset();
    }

    void runLoop(std::stop_token&& token);

    auto getLocalAddress() const -> SocketAddr {
        return listener.local_addr().value();
    }

    void processSpawnPlayer(NetworkConnection& _, const SSpawnPlayerPacket& packet);
    void processPlayerPosition(NetworkConnection& _, const PositionPacket& packet);
    void processPlayerDigging(NetworkConnection& _, const CPlayerDiggingPacket& packet);
    void processChangeBlock(NetworkConnection& _, const SChangeBlockPacket& packet);
};