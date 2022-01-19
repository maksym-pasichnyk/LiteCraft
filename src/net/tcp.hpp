#pragma once

#include "sock.hpp"

#include <span>
#include <tl/optional.hpp>

struct TcpStream {
    Socket s;

    static auto connect(const SocketAddr& addr) -> tl::optional<TcpStream>;

    void close() const;
    auto send(std::span<const std::byte> bytes) const -> tl::optional<size_t>;
    auto send_to(std::span<const std::byte> bytes, const SocketAddr& addr) const -> tl::optional<size_t>;
    auto recv(std::span<std::byte> bytes) const -> tl::optional<std::pair<size_t, SocketAddr>>;
    void set_blocking(bool flag) const;
};

struct TcpListener {
    Socket s;

    static auto bind(const SocketAddr& addr) -> tl::optional<TcpListener>;

    void close() const;
    auto accept() const -> tl::optional<std::pair<TcpStream, SocketAddr>>;
    auto local_addr() const -> tl::optional<SocketAddr>;
    void set_blocking(bool flag) const;
};
