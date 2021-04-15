#pragma once

#include "Packet.hpp"
#include "NetworkManager.hpp"

template <typename T, size_t maxSize>
struct PacketManager {
    std::array<void(*)(T*, NetworkConnection&, const PacketHeader&), maxSize> callbacks {};

    template <Packet _Packet, void(T::*process)(const _Packet& packet)>
    static void handle(T* server, NetworkConnection& connection, const PacketHeader& header) {
        (server->*process)(connection.readPacket<_Packet>(header));
    }

    template <Packet _Packet, void(T::*process)(const _Packet& packet)>
    void bind() {
        callbacks[_Packet::ID] = &PacketManager::handle<_Packet, process>;
    }

    void handlePackets(T* self, NetworkConnection& connection) {
        while (const auto header = connection.readHeader()) {
            callbacks[header->id](self, connection, *header);
        }
    }
};