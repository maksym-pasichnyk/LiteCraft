#pragma once

#include "Packet.hpp"
#include "NetworkManager.hpp"

#include <span>

template <typename T>
struct PacketManager {
    std::vector<void(*)(T& obj, NetworkConnection& connection, std::span<const std::byte> bytes)> callbacks{};

    template <typename Packet, void(T::*callback)(NetworkConnection& connection, const Packet& packet)>
    void bind() {
        constexpr auto id = static_cast<size_t>(Packet::ID);

        if (id >= callbacks.size()) {
            callbacks.resize(id + 1);
        }

        callbacks[id] = [](T& obj, NetworkConnection& connection, std::span<const std::byte> bytes) {
            if (bytes.size() != sizeof(Packet)) {
                fmt::print(stderr, "Wrong packet data!\n");
                return;
            }

            Packet packet;
            std::memcpy(&packet, bytes.data(), bytes.size());

            (obj.*callback)(connection, packet);
        };
    }

    void handlePackets(T& obj, NetworkConnection& connection) {
        while (auto received = connection.recv()) {
            const auto& [header, bytes] = *received;
            callbacks[header.id](obj, connection, std::span(bytes));
        }
    }
};