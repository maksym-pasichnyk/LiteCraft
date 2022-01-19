#pragma once

#include "addr.hpp"

#include <bit>
#include <span>
#include <tl/optional.hpp>

struct Socket {
    uintptr_t fd;

    static auto create(int af, int type, int protocol) -> tl::optional<Socket>;

    void close() const;
    auto send(std::span<const std::byte> bytes) const -> tl::optional<size_t>;
    auto send_to(std::span<const std::byte> bytes, const SocketAddr& addr) const -> tl::optional<size_t>;
    auto recv(std::span<std::byte> bytes) const -> tl::optional<std::pair<size_t, SocketAddr>>;
    void set_blocking(bool flag) const;
};