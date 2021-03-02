#pragma once

#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

struct NetworkClient {
    int fd;
};

struct NetworkServer {
    int fd;
};

struct NetworkManager {
    std::array<int, 2> sockets;

    static auto create() -> std::optional<NetworkManager> {
        std::array<int, 2> sockets{};

        if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets.data()) < 0) {
            return std::nullopt;
        }

        if (fcntl(sockets[0], F_SETFL, fcntl(sockets[0], F_GETFL) | O_NONBLOCK) < 0) {
            return std::nullopt;
        }

        if (fcntl(sockets[1], F_SETFL, fcntl(sockets[1], F_GETFL) | O_NONBLOCK) < 0) {
            return std::nullopt;
        }

        return NetworkManager{sockets};
    }

    auto client() const -> NetworkClient {
        return {.fd = sockets[0]};
    }

    auto server() const -> NetworkServer {
        return {.fd = sockets[1]};
    }
};