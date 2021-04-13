#pragma once

#include "NetworkManager.hpp"
#include "world/ServerWorld.hpp"
#include "util/math/ChunkPos.hpp"

#include <thread>
#include <memory>

struct CraftServer {
    NetworkConnection connection;
    std::unique_ptr<ServerWorld> world = nullptr;
    std::vector<std::jthread> workers{};
    ChunkPos last_player_position{};

    explicit CraftServer(NetworkConnection connection);

    void runWorker(std::stop_token&& token) {
        while (!token.stop_requested()) {
            executor_execute();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    void executor_execute();
};