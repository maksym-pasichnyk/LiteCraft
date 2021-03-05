#pragma once

#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "Packet.hpp"

struct NetworkConnection {
    int fd;

    template<Packet T>
    void sendPacket(const T& packet) {
        PacketHeader header {
                .id = T::ID,
                .size = sizeof(T)
        };

        write(fd, &header, sizeof(PacketHeader));
        write(fd, &packet, sizeof(T));
    }

    void readPacket() {
        PacketHeader header{};
        read(fd, &header, sizeof(PacketHeader));
    }
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

    auto client() const -> NetworkConnection {
        return {.fd = sockets[0]};
    }

    auto server() const -> NetworkConnection {
        return {.fd = sockets[1]};
    }
};