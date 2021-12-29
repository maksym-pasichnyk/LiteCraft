#pragma once

#include "Connection.hpp"
#include "Packet.hpp"

#include <span>
#include <iostream>
#include <util/match.hpp>

template <typename... Packets>
struct PacketHandler {
    template<typename T>
    void handlePackets(T& obj, Connection& connection) {
        while (auto received = connection.recv()) {
            auto [id, data] = std::move(*received);
            if (!try_call_on_packet<T, Packets...>(obj, connection, id, data)) {
                spdlog::error("unknown packet: {}", id);
            }
        }
    }

private:
    template <typename T>
    auto try_call_on_packet(T& obj, Connection& connection, size_t id, PacketData& data) -> bool {
        return false;
    }

    template <typename T, typename Packet, typename... PacketTail>
    auto try_call_on_packet(T& obj, Connection& connection, size_t id, PacketData& data) -> bool {
        if (static_cast<size_t>(Packet::ID) == id) {
            auto packet = Packet{};
            packet.read(data);
            obj.onPacket(connection, packet);
            return true;
        }
        return try_call_on_packet<T, PacketTail...>(obj, connection, id, data);
    }
};