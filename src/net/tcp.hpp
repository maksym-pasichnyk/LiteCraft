#pragma once

#include "sock.hpp"

struct TcpStream {
    Socket s;

    static auto connect(const SocketAddr& addr) -> std::optional<TcpStream> {
        auto s = Socket::create(addr.inner.sin_family, SOCK_STREAM, 0);
        if (!s.has_value()) {
            return std::nullopt;
        }
        auto name = std::bit_cast<sockaddr>(addr.inner);
        if (::connect(s->fd, &name, sizeof(sockaddr_in)) == -1) {
            s->close();
            return std::nullopt;
        }
        return TcpStream{*s};
    }

    void close() {
        s.close();
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

    void set_blocking(bool flag) const {
        s.set_blocking(flag);
    }
};

struct TcpListener {
    Socket s;

    static auto bind(const SocketAddr& addr) -> std::optional<TcpListener> {
        auto s = Socket::create(addr.inner.sin_family, SOCK_STREAM, 0);
        if (!s.has_value()) {
            return std::nullopt;
        }
        auto name = std::bit_cast<sockaddr>(addr.inner);
        if (::bind(s->fd, &name, sizeof(sockaddr_in)) == -1) {
            s->close();
            return std::nullopt;
        }
        if (::listen(s->fd, SOMAXCONN) == -1) {
            s->close();
            return std::nullopt;
        }
        return TcpListener{*s};
    }

    void close() {
        s.close();
    }

    auto accept() const -> std::optional<std::pair<TcpStream, SocketAddr>> {
        sockaddr addr{};
        int len = sizeof(sockaddr);

        Socket c {::accept(s.fd, &addr, &len)};
        if (c.fd == -1) {
            return std::nullopt;
        }
        return std::pair{TcpStream{c}, std::bit_cast<SocketAddr>(addr)};
    }

    auto local_addr() const -> std::optional<SocketAddr> {
        sockaddr name{};
        int size = sizeof(sockaddr);
        if (getsockname(s.fd, &name, &size) == -1) {
            return std::nullopt;
        }
        return std::bit_cast<SocketAddr>(name);
    }
    void set_blocking(bool flag) const {
        s.set_blocking(flag);
    }
};
