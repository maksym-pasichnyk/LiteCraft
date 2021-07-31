#pragma once

#include "Packet.hpp"
#include "net/tcp.hpp"

#include <vector>
#include <span>

struct NetworkConnection {
    explicit NetworkConnection(TcpStream socket) : socket(socket) {
        socket.set_blocking(false);
    }

    explicit NetworkConnection(const SocketAddr& address) : socket(TcpStream::connect(address)) {
        if (socket.has_value()) {
            socket->set_blocking(false);
        }
    }

    ~NetworkConnection() {
        if (socket.has_value()) {
            socket->close();
        }
    }

    template <typename Packet>
    bool send(const Packet& packet) {
        if (!socket.has_value()) {
            return false;
        }

        PacketHeader header {
            .id = Packet::ID,
            .size = sizeof(Packet)
        };

        std::array<std::byte, sizeof(PacketHeader) + sizeof(Packet)> bytes;
        std::memcpy(bytes.data(), &header, sizeof(PacketHeader));
        std::memcpy(bytes.data() + sizeof(PacketHeader), &packet, sizeof(Packet));

        return socket->send(bytes).has_value();
    }

    auto recv() -> std::optional<std::pair<PacketHeader, std::vector<std::byte>>> {
        if (!socket.has_value()) {
            return std::nullopt;
        }

        std::array<std::byte, sizeof(PacketHeader)> data{};
        auto len = socket->recv(std::as_writable_bytes(std::span(data)));
        if (!len.has_value() || len->first == 0) {
            return std::nullopt;
        }

        const auto header = std::bit_cast<PacketHeader>(data);
        std::vector<std::byte> bytes{static_cast<size_t>(header.size)};
        socket->recv(std::span(bytes));
        return std::pair{header, bytes};
    }

private:
    std::optional<TcpStream> socket;
};
