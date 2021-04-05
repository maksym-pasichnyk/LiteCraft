#pragma once

#include <cstdint>
#include <array>

enum class HeightmapType {
    WORLD_SURFACE_WG,
    WORLD_SURFACE,
    OCEAN_FLOOR_WG,
    OCEAN_FLOOR,
    MOTION_BLOCKING,
    MOTION_BLOCKING_NO_LEAVES
};

struct Heightmap {
    static constexpr uint64_t maxValue = 0x1FF;

    std::array<uint64_t, 37> data{};

    constexpr int getAt(int32_t i) const {
        const int32_t s = (i % 7) * 9;
        return static_cast<int>((data[i / 7] >> s) & maxValue);
    }

    constexpr void setAt(int32_t i, int32_t v) {
        const int32_t s = (i % 7) * 9;
        data[i / 7] = data[i / 7] & ~(maxValue << s) | ((static_cast<uint64_t>(v) & maxValue) << s);
    }

    constexpr int get(int32_t x, int32_t z) const {
        return getAt(x | (z << 4));
    }

    constexpr void set(int32_t x, int32_t z, int32_t v) {
        return setAt(x | (z << 4), v);
    }
};