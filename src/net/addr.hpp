#pragma once

#include "ip.hpp"

static constexpr auto to_be(uint16_t v) -> uint16_t {
    const auto bytes = std::bit_cast<std::array<uint8_t, 2>>(v);
    return (static_cast<uint16_t>(bytes[0]) << 8)
         | (static_cast<uint16_t>(bytes[1]) << 0);
}

static constexpr auto from_be(uint16_t v) -> uint16_t {
    return std::bit_cast<uint16_t>(std::array{
        static_cast<uint8_t>((v >> 8) & 0xFF),
        static_cast<uint8_t>((v >> 0) & 0xFF),
    });
}

struct SocketAddr {
    sockaddr_in inner;

    static constexpr auto from(Ipv4Addr ip, uint16_t port) -> SocketAddr {
        return SocketAddr{
            .inner{
                .sin_family = AF_INET,
                .sin_port = to_be(port),
                .sin_addr = ip.inner
            }
        };
    }

    auto ip() const -> Ipv4Addr {
        return Ipv4Addr{inner.sin_addr};
    }

    void set_ip(Ipv4Addr ip) {
        inner.sin_addr = ip.inner;
    }

    auto port() const -> uint16_t {
        return from_be(inner.sin_port);
    }

    void set_port(uint16_t port) {
        inner.sin_port = to_be(port);
    }
};

template <>
struct fmt::formatter<SocketAddr> : formatter<std::string> {
    template <typename FormatContext>
    auto format(SocketAddr addr, FormatContext& ctx) {
        return formatter::format(fmt::format("{}:{}", addr.ip(), addr.port()), ctx);
    }
};