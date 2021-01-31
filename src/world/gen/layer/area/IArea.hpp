#pragma once

#include "../../../biome/Biome.hpp"
#include "../../../../util/math/ChunkPos.hpp"

#include <functional>
#include <memory>
#include <map>

struct IArea : private std::function<int(int, int)> {
    mutable std::unordered_map<int64_t, int> cache{};
    using function::function;

    int getValue(int x, int z) const {
        const auto i = ChunkPos::asLong(x, z);
        if (cache.contains(i)) {
            return cache.at(i);
        }
        auto v = (*this)(x, z);
        cache.emplace(i, v);
        return v;
    }
};

//struct LazyArea {
//    std::unordered_map<int64_t, int> cache{};
//    IArea area;
//
//    LazyArea(IArea&& area) : area(std::move(area)) {}
//
//    int getValue(int x, int z) {
//        const auto i = ChunkPos::asLong(x, z);
//        if (cache.contains(i)) {
//            return cache.at(i);
//        }
//        auto v = area.getValue(x, z);
//        cache.emplace(i, v);
//        return i;
//    }
//};

