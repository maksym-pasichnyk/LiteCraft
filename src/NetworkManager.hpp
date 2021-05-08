#pragma once

#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <mutex>
#include <sys/types.h>
#include <sys/socket.h>
#include <fmt/format.h>

#include "Packet.hpp"

struct NetworkConnection {
    int fd;
    std::mutex guard;

    NetworkConnection(int fd) : fd(fd) {}

    template<Packet T>
    bool sendPacket(const T& packet) {
        PacketHeader header {
            .id = T::ID,
            .size = sizeof(T)
        };

        std::array<std::byte, sizeof(PacketHeader) + sizeof(T)> buf;
        std::memcpy(buf.data(), &header, sizeof(PacketHeader));
        std::memcpy(buf.data() + sizeof(PacketHeader), &packet, sizeof(T));

        return write(fd, buf.data(), buf.size()) > 0;
    }

    std::optional<PacketHeader> readHeader() {
        PacketHeader header{};
        if (read(fd, &header, sizeof(PacketHeader)) <= 0) {
            return std::nullopt;
        }
        return header;
    }

    template<Packet T>
    T readPacket(const PacketHeader& header) {
        T packet;
        while (read(fd, &packet, header.size) < 0) {
        }
        return packet;
    }
};

struct NetworkManager {
    std::shared_ptr<NetworkConnection> _client;
    std::shared_ptr<NetworkConnection> _server;

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

        return NetworkManager{
                std::make_shared<NetworkConnection>(sockets[0]),
                std::make_shared<NetworkConnection>(sockets[1]),
        };
    }

    auto client() const -> std::shared_ptr<NetworkConnection> {
        return _client;
    }

    auto server() const -> std::shared_ptr<NetworkConnection> {
        return _server;
    }
};