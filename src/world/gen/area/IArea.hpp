#pragma once

#include "../../biome/Biome.hpp"
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

#include <list>

template <typename K, typename V>
class linked_hash_map {
    std::unordered_map<K, V> hash;
    std::list<K> ls;

public:
    size_t size() const noexcept { return ls.size(); }
    bool empty() const noexcept { return ls.empty(); }

    void insert(std::pair<K, V> kv) {
        const auto p = hash.find(kv.first);
        if (p != hash.end()) {
            p->second = std::move(kv.second);
        } else {
            ls.emplace_back(kv.first);
            hash.emplace(std::move(kv));
        }
    }

    void pop_front() {
        hash.erase(ls.front());
        ls.pop_front();
    }

    bool contains(const K& k) const noexcept {
        return hash.contains(k);
    }

    V& at(const K& k) noexcept {
        return hash.at(k);
    }

    const V& at(const K& k) const noexcept {
        return hash.at(k);
    }
};

class LazyArea {
    IPixelTransformer pixelTransformer;
    mutable linked_hash_map<int64_t, int> cache;
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

