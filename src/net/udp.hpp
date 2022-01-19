#pragma once

#include "sock.hpp"

#include <span>
#include <tl/optional.hpp>

struct Ipv4Addr;
struct SocketAddr;

struct UdpSocket {
    Socket s;

    static auto bind(const SocketAddr& addr) -> tl::optional<UdpSocket>;

    void close();
    void set_blocking(bool flag) const;
    void set_broadcast(bool flag) const;
    void set_reuse_port(bool flag) const;
    void set_reuse_address(bool flag) const;
    void join_multicast_v4(const Ipv4Addr& imr_multiaddr, const Ipv4Addr& imr_interface) const;
    void leave_multicast_v4(const Ipv4Addr& imr_multiaddr, const Ipv4Addr& imr_interface) const;
    auto send(std::span<const std::byte> bytes) const -> tl::optional<size_t>;
    auto send_to(std::span<const std::byte> bytes, const SocketAddr& addr) const -> tl::optional<size_t>;
    auto recv(std::span<std::byte> bytes) const -> tl::optional<std::pair<size_t, SocketAddr>>;
};
