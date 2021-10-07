#pragma once

#include "Packet.hpp"

#include <span>
#include <vector>
#include <net/tcp.hpp>
#include <entt/entt.hpp>

struct Connection {
    entt::entity player;
    std::optional<TcpStream> socket;

    explicit Connection(entt::entity player, TcpStream socket) : player(player), socket(socket) {
        socket.set_blocking(false);
    }

    explicit Connection(entt::entity player, const SocketAddr& address) : player(player), socket(TcpStream::connect(address)) {
        if (socket.has_value()) {
            socket->set_blocking(false);
        }
    }

    ~Connection() {
        if (socket.has_value()) {
            socket->close();
        }
    }

    template <typename Packet>
    bool send(const Packet& packet) {
        if (!socket.has_value()) {
            return false;
        }

        auto buf = PacketData::with_write_offset(sizeof(PacketHeader));
        packet.write(buf);

        auto header = PacketHeader::from(static_cast<int>(Packet::ID), static_cast<int>(buf.data.size() - sizeof(PacketHeader)));

        std::memcpy(buf.data.data(), &header, sizeof(PacketHeader));

        return socket->send(buf.data).has_value();
    }

    auto recv() -> std::optional<std::pair<int, PacketData>> {
        if (!socket.has_value()) {
            return std::nullopt;
        }

        std::array<std::byte, sizeof(PacketHeader)> data{};
        auto len = socket->recv(data);
        if (!len.has_value() || len->first == 0) {
            return std::nullopt;
        }
        const auto header = std::bit_cast<PacketHeader>(data);
        std::vector<std::byte> bytes{static_cast<size_t>(header.size)};
        socket->recv(bytes);
        return std::pair{header.id, PacketData::from(std::move(bytes))};
    }
};
