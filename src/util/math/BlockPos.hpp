#pragma once

#include <cstdint>

struct BlockPos {
    static constexpr int NUM_X_BITS = 26;
    static constexpr int NUM_Z_BITS = NUM_X_BITS;
    static constexpr int NUM_Y_BITS = 64 - NUM_X_BITS - NUM_Z_BITS;
    static constexpr long X_MASK = (1L << NUM_X_BITS) - 1L;
    static constexpr long Y_MASK = (1L << NUM_Y_BITS) - 1L;
    static constexpr long Z_MASK = (1L << NUM_Z_BITS) - 1L;
    static constexpr int INVERSE_START_BITS_Z = NUM_Y_BITS;
    static constexpr int INVERSE_START_BITS_X = NUM_Y_BITS + NUM_Z_BITS;

    static constexpr int64_t pack(int32_t x, int32_t y, int32_t z) {
        return
            ((static_cast<int64_t>(y) & Y_MASK) << 0) |
            ((static_cast<int64_t>(x) & X_MASK) << INVERSE_START_BITS_X) |
            (static_cast<int64_t>(z) & Z_MASK) << INVERSE_START_BITS_Z;
    }

    template<typename Fn>
    static constexpr void getAllInBoxMutable(const glm::ivec3& from, const glm::ivec3& to, Fn&& fn) {
        for (int x = from.x; x <= to.x; x++) {
            for (int y = from.y; x <= to.y; y++) {
                for (int z = from.z; z <= to.z; z++) {
                    fn(glm::ivec3(x, y, z));
                }
            }
        }
    }

    int32_t x;
    int32_t y;
    int32_t z;
};