#include "tcp.hpp"

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif

#ifdef __APPLE__
#include <sys/fcntl.h>
#include <unistd.h>
#endif

auto TcpStream::connect(const SocketAddr &addr) -> tl::optional<TcpStream> {
    auto s = Socket::create(addr.inner.sin_family, SOCK_STREAM, 0);
    if (!s.has_value()) {
        return tl::nullopt;
    }
    auto name = std::bit_cast<sockaddr>(addr.inner);
    if (::connect(s->fd, &name, sizeof(sockaddr_in)) == -1) {
        s->close();
        return tl::nullopt;
    }
    return TcpStream{*s};
}

void TcpStream::close() const {
    s.close();
}

auto TcpStream::send(std::span<const std::byte> bytes) const -> tl::optional<size_t> {
    return s.send(bytes);
}

auto TcpStream::send_to(std::span<const std::byte> bytes, const SocketAddr &addr) const -> tl::optional<size_t> {
    return s.send_to(bytes, addr);
}

auto TcpStream::recv(std::span<std::byte> bytes) const -> tl::optional<std::pair<size_t, SocketAddr>> {
    return s.recv(bytes);
}

void TcpStream::set_blocking(bool flag) const {
    s.set_blocking(flag);
}

auto TcpListener::bind(const SocketAddr &addr) -> tl::optional<TcpListener> {
    auto s = Socket::create(addr.inner.sin_family, SOCK_STREAM, 0);
    if (!s.has_value()) {
        return tl::nullopt;
    }
    auto name = std::bit_cast<sockaddr>(addr.inner);
    if (::bind(s->fd, &name, sizeof(sockaddr_in)) == -1) {
        s->close();
        return tl::nullopt;
    }
    if (::listen(s->fd, SOMAXCONN) == -1) {
        s->close();
        return tl::nullopt;
    }
    return TcpListener{*s};
}

void TcpListener::close() const {
    s.close();
}

auto TcpListener::accept() const -> tl::optional<std::pair<TcpStream, SocketAddr>> {
    auto len = static_cast<socklen_t>(sizeof(sockaddr));

    sockaddr addr{};

    Socket c {::accept(s.fd, &addr, &len)};
    if (c.fd == -1) {
        return tl::nullopt;
    }
    return std::pair{TcpStream{c}, std::bit_cast<SocketAddr>(addr)};
}

auto TcpListener::local_addr() const -> tl::optional<SocketAddr> {
    auto len = static_cast<socklen_t>(sizeof(sockaddr));

    sockaddr name{};
    if (getsockname(s.fd, &name, &len) == -1) {
        return tl::nullopt;
    }
    return std::bit_cast<SocketAddr>(name);
}

void TcpListener::set_blocking(bool flag) const {
    s.set_blocking(flag);
}
