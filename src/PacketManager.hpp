#pragma once

#include "Connection.hpp"
#include "Packet.hpp"

#include <iostream>
#include <span>

template <typename T>
struct PacketManager {
    std::vector<void(*)(T& obj, Connection& connection, PacketData buf)> callbacks{};

    template <typename Packet, void(T::*callback)(Connection & connection, const Packet& packet)>
    void bind() {
        constexpr auto id = static_cast<size_t>(Packet::ID);

        if (id >= callbacks.size()) {
            callbacks.resize(id + 1);
        }

        callbacks[id] = [](T& obj, Connection& connection, PacketData data) {
            Packet packet{};
            packet.read(data);
            (obj.*callback)(connection, packet);
        };
    }

    void handlePackets(T& obj, Connection& connection) {
        while (auto received = connection.recv()) {
            auto [id, data] = std::move(*received);
            callbacks[id](obj, connection, std::move(data));
        }
    }
};