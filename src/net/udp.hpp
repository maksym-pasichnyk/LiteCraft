#pragma once

#include "sock.hpp"
#include "ip.hpp"

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2ipdef.h>
#endif

struct UdpSocket {
    Socket s;

    static auto bind(const SocketAddr& addr) -> std::optional<UdpSocket> {
        auto s = Socket::create(addr.inner.sin_family, SOCK_DGRAM, IPPROTO_UDP);
        if (!s.has_value()) {
            return std::nullopt;
        }
        auto name = std::bit_cast<sockaddr>(addr.inner);
        if (::bind(s->fd, &name, sizeof(sockaddr)) == -1) {
            s->close();
            return std::nullopt;
        }
        return UdpSocket{*s};
    }

    void close() {
        s.close();
    }

    void set_blocking(bool flag) const {
        s.set_blocking(flag);
    }

    void set_broadcast(bool flag) const {
        const int optval = flag ? 1 : 0;
#ifdef _WIN32
        setsockopt(s.fd, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&optval), sizeof(optval));
#else
        setsockopt(s.fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
#endif
    }

    void set_reuse_port(bool flag) const {
#ifdef _WIN32
#else
        const int optval = flag ? 1 : 0;
        setsockopt(s.fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif
    }

    void set_reuse_address(bool flag) const {
        const int optval = flag ? 1 : 0;
#ifdef _WIN32
        setsockopt(s.fd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&optval), sizeof(optval));
#else
        setsockopt(s.fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
#endif
    }

    void join_multicast_v4(Ipv4Addr imr_multiaddr, Ipv4Addr imr_interface) const {
        ip_mreq mreq{};
        mreq.imr_multiaddr = imr_multiaddr.inner;
        mreq.imr_interface = imr_interface.inner;
#ifdef _WIN32
        setsockopt(s.fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, reinterpret_cast<const char *>(&mreq), sizeof(mreq));
#else
        setsockopt(s.fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
#endif
    }

    void leave_multicast_v4(Ipv4Addr imr_multiaddr, Ipv4Addr imr_interface) const {
        ip_mreq mreq{};
        mreq.imr_multiaddr = imr_multiaddr.inner;
        mreq.imr_interface = imr_interface.inner;
#ifdef _WIN32
        setsockopt(s.fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, reinterpret_cast<const char *>(&mreq), sizeof(mreq));
#else
        setsockopt(s.fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
#endif
    }

    auto send(std::span<const std::byte> bytes) -> std::optional<size_t> {
        return s.send(bytes);
    }

    auto send_to(std::span<const std::byte> bytes, const SocketAddr& addr) -> std::optional<size_t> {
        return s.send_to(bytes, addr);
    }

    auto recv(std::span<std::byte> bytes) -> std::optional<std::pair<size_t, SocketAddr>> {
        return s.recv(bytes);
    }
};
