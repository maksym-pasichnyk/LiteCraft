#pragma once

#include <cstdint>
#include <atomic>
#include <vector>

struct ChunkArray {
//private:
    int viewDistance = -1;
    int sideLength = -1;
    int loaded = 0;
    std::atomic_int centerX{0};
    std::atomic_int centerZ{0};
    std::vector<std::atomic<Chunk*>> chunks;

    static_assert(std::atomic<Chunk*>::is_always_lock_free);

public:
    explicit ChunkArray(int viewDistance)
        : viewDistance{viewDistance}
        , sideLength{viewDistance * 2 + 1}
        , chunks(sideLength * sideLength) {}

    auto getLoaded() const -> int {
        return loaded;
    }

    auto get(int32_t i) const -> Chunk* {
        return chunks.at(i).load();
    }

    auto set(int32_t i, Chunk* chunk) {
        auto old_chunk = chunks.at(i).exchange(chunk);

        loaded = loaded - (old_chunk ? 1 : 0) + (chunk ? 1 : 0);
    }

    auto getIndex(int32_t x, int32_t z) const -> int32_t {
        return floorMod(z, sideLength) * sideLength + floorMod(x, sideLength);
    }

    auto inView(int x, int z) const -> bool {
        return std::abs(x - centerX) <= viewDistance && std::abs(z - centerZ) <= viewDistance;
    }

    void setCenter(int32_t x, int32_t z) {
        centerX = x;
        centerZ = z;
    }

//private:
    static auto floorMod(int32_t x, int32_t y) -> int32_t {
        return ((x % y) + y) % y;
    }
};
