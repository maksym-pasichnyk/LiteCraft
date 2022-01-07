#pragma once

#include "Connection.hpp"
#include "PacketManager.hpp"
#include "world/ServerWorld.hpp"
#include "util/math/ChunkPos.hpp"

#include <memory>
#include <thread>
#include <entt/entt.hpp>
#include <ResourceManager.hpp>
#include <range/v3/algorithm.hpp>

using ClientNetHandler = PacketHandler<
    CHandshakePacket,
    CLoginStartPacket,
    CEncryptionResponsePacket,
    PositionPacket,
    CPlayerDiggingPacket
>;

struct CraftServer {
    entt::registry ecs;

    ClientNetHandler handler;

    std::unique_ptr<ServerWorld> world = nullptr;
    std::vector<std::thread> workers{};
    TcpListener listener{};

//    std::stop_source stop_source;
    bool request_stop = false;
    int viewDistance = -1;

    explicit CraftServer(int viewDistance);

    ~CraftServer() {
        listener.close();
        request_stop = true;
//        stop_source.request_stop();
        ranges::for_each(workers, std::mem_fn(&std::thread::join));
        workers.clear();

        world.reset();
    }

    void runLoop(/*std::stop_token&& token*/);

    auto getLocalAddress() const -> SocketAddr {
        return listener.local_addr().value();
    }

    void onPacket(Connection& _, const CHandshakePacket& packet);
    void onPacket(Connection& _, const CLoginStartPacket& packet);
    void onPacket(Connection& _, const CEncryptionResponsePacket& packet);
    void onPacket(Connection& _, const PositionPacket& packet);
    void onPacket(Connection& _, const CPlayerDiggingPacket& packet);
//    void processChangeBlock(Connection& _, const SChangeBlockPacket& packet);
};