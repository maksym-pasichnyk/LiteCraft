#pragma once

#include <fmt/format.h>
#include <string_view>
#include <optional>
#include <array>
#include <bit>

#ifdef _WIN32
#include <WinSock2.h>
#endif

struct Ipv4Addr {
    in_addr inner;

    constexpr auto octets() const -> std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> {
        const auto octets = std::bit_cast<std::array<uint8_t, 4>>(inner.s_addr);
        return {octets[0], octets[1], octets[2], octets[3]};
    }

    static constexpr auto from(uint8_t a, uint8_t b, uint8_t c, uint8_t d) -> Ipv4Addr {
        in_addr inner{};
        inner.s_addr = std::bit_cast<uint32_t>(std::array{a, b, c, d});
        return {.inner = inner};
    }

    static constexpr auto from(std::string_view ip) -> std::optional<Ipv4Addr> {
        std::array<uint32_t, 4> parts{};

        size_t components = 0;
        for (size_t i = 0; i < ip.size() && ip[i] >= '0' && ip[i] <= '9'; ++i) {
            uint32_t val = ip[i] - '0';
            for (++i; i < ip.size() && (ip[i] >= '0' && ip[i] <= '9'); ++i) {
                val = val * 10 + (ip[i] - '0');
            }
            if (val > 0xFF) {
                return std::nullopt;
            }
            parts[components++] = val;

            if (i < ip.size() && (components == 4 || ip[i] != '.')) {
                return std::nullopt;
            }
        }

        if (components != 4) {
            return std::nullopt;
        }

        return from(parts[0], parts[1], parts[2], parts[3]);
    }

    static constexpr auto localhost() -> Ipv4Addr {
        return from(127, 0, 0, 1);
    }

    static constexpr auto any() -> Ipv4Addr {
        return from(0, 0, 0, 0);
    }

    static constexpr auto broadcast() -> Ipv4Addr {
        return from(255, 255, 255, 255);
    }
};

template <>
struct fmt::formatter<Ipv4Addr> : formatter<std::string> {
    template <typename FormatContext>
    auto format(const Ipv4Addr& addr, FormatContext& ctx) {
        const auto [a, b, c, d] = addr.octets();
        return formatter<std::string>::format(fmt::format("{}.{}.{}.{}", a, b, c, d), ctx);
    }
};
