#pragma once

#include "addr.hpp"

#include <bit>
#include <span>
#include <optional>

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2ipdef.h>
#endif

#ifdef __APPLE__
#include <sys/fcntl.h>
#include <unistd.h>
#endif

struct Socket {
    #ifdef _WIN32
    SOCKET fd;
    #else
    int fd;
    #endif

    static auto create(int af, int type, int protocol) -> std::optional<Socket> {
        const auto fd = socket(af, type, protocol);
        if (fd == -1) {
            return std::nullopt;
        }
        return std::bit_cast<Socket>(fd);
    }

    void close() {
#ifdef _WIN32
        ::closesocket(fd);
#else
        ::close(fd);
#endif
    }

    auto send(std::span<const std::byte> bytes) -> std::optional<size_t> {
        size_t sent = 0;

        while (sent < bytes.size()) {
            const auto buf = bytes.subspan(sent);

            const int len = sendto(fd, reinterpret_cast<const char*>(buf.data()), static_cast<int>(buf.size()), 0, nullptr, sizeof(sockaddr_in));
            if (len <= 0) {
                return std::nullopt;
            }
            sent += len;
        }

        return sent;
    }

    auto send_to(std::span<const std::byte> bytes, const SocketAddr& addr) -> std::optional<size_t> {
        size_t sent = 0;

        while (sent < bytes.size()) {
            const auto buf = bytes.subspan(sent);

            const auto name = std::bit_cast<sockaddr>(addr.inner);
            const auto len = sendto(fd, reinterpret_cast<const char*>(buf.data()), static_cast<int>(buf.size()), 0, &name, sizeof(sockaddr));
            if (len <= 0) {
                return std::nullopt;
            }
            sent += len;
        }
        return sent;
    }

    auto recv(std::span<std::byte> bytes) -> std::optional<std::pair<size_t, SocketAddr>> {
#ifdef _WIN32
        int size = sizeof(sockaddr);
#else
        auto size = static_cast<socklen_t>(sizeof(sockaddr));
#endif
        sockaddr name{};
        const auto n = recvfrom(fd, reinterpret_cast<char *>(bytes.data()), static_cast<int>(bytes.size()), 0, &name, &size);

        if (n <= 0) {
#ifdef _WIN32
            if (WSAGetLastError() == WSAEWOULDBLOCK) {
#else
            if (errno == EWOULDBLOCK) {
#endif
                return std::pair{0, std::bit_cast<SocketAddr>(name)};
            }
            return std::nullopt;
        }
        return std::pair{n, std::bit_cast<SocketAddr>(name)};
    }

    void set_blocking(bool flag) const {
#ifdef _WIN32
        u_long mode = flag ? 0 : 1;
        ioctlsocket(fd, FIONBIO, &mode);
#else
        const auto flags = fcntl(fd, F_GETFL, 0);
        if (flags == -1) {
            return;
        }

        fcntl(fd, F_SETFL, flag ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK));
#endif
    }
};