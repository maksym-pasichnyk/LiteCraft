#pragma once

#include "Connection.hpp"
#include "PacketManager.hpp"
#include "util/math/ChunkPos.hpp"
#include "world/ServerWorld.hpp"

#include <range/v3/algorithm.hpp>
#include <resource_manager.hpp>
#include <thread>
#include <memory>

struct CraftServer {
    ResourceManager& resources;
    PacketManager<CraftServer> packetManager;
    std::vector<std::unique_ptr<Connection>> connections;

    std::unique_ptr<ServerWorld> world = nullptr;
    std::vector<std::thread> workers{};
    ChunkPos last_player_position{};
    TcpListener listener{};

    std::stop_source stop_source;
    int viewDistance = -1;

    explicit CraftServer(int viewDistance, ResourceManager& resources);

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

    void processHandshake(Connection& _, const CHandshakePacket& packet);
    void processLoginStart(Connection& _, const CLoginStartPacket& packet);
    void processEncryptionResponse(Connection& _, const CEncryptionResponsePacket& packet);
    void processPlayerPosition(Connection& _, const PositionPacket& packet);
    void processPlayerDigging(Connection& _, const CPlayerDiggingPacket& packet);
//    void processChangeBlock(Connection& _, const SChangeBlockPacket& packet);
};