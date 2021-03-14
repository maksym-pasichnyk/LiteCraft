#pragma once

#include "../../biome/Biome.hpp"
#include "../../../util/linked_unordered_map.hpp"
#include "../../../util/math/ChunkPos.hpp"

#include <functional>
#include <memory>
#include <map>

#include <fmt/format.h>

struct IPixelTransformer : private std::function<int(int, int)> {
    using function::function;

    int apply(int x, int z) const {
        return (*this)(x, z);
    }
};

template <typename T>
concept IArea = requires(T& self, int x, int z) {
    {self.getValue(x, z)} -> std::same_as<int>;
};

class LazyArea {
    IPixelTransformer pixelTransformer;
    mutable linked_unordered_map<int64_t, int> cache;
    int maxCacheSize;

public:
    explicit LazyArea(IPixelTransformer&& pixelTransformer, int maxCacheSize)
        : pixelTransformer(std::move(pixelTransformer))
        , maxCacheSize(maxCacheSize) {}

    int getValue(int x, int z) const {
        const auto i = ChunkPos::asLong(x, z);
        if (cache.contains(i)) {
            return cache.at(i);
        }
        auto v = pixelTransformer.apply(x, z);
        cache.insert(std::pair{i, v});
        if (cache.size() > maxCacheSize) {
            for (int j = 0; j < maxCacheSize / 16; ++j) {
                if (cache.empty()) break;
                cache.pop_front();
            }
        }
        return v;
    }

    int getMaxCacheSize() const {
        return maxCacheSize;
    }
};

