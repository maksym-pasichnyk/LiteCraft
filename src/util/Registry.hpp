#pragma once

#include <tl/optional.hpp>
#include <memory>
#include <vector>
#include <string>
#include <map>

template <typename K, typename T>
struct DynamicRegistry {
    std::vector<std::unique_ptr<T>> entries{};
    std::map<K, T*> objects{};

    auto name(T* obj) const -> tl::optional<K> {
        for (const auto& [key, val] : objects) {
            if (val == obj) {
                return key;
            }
        }
        return tl::nullopt;
    }

    auto get(const K& name) -> tl::optional<T*> {
        if (auto it = objects.find(name); it != objects.end()) {
            return it->second;
        }
        return tl::nullopt;
    }

    auto add(K name, std::unique_ptr<T>&& obj) -> T* {
        auto ptr = entries.emplace_back(std::move(obj)).get();
        objects.insert_or_assign(std::move(name), ptr);
        return ptr;
    }

    auto add(size_t id, K name, std::unique_ptr<T>&& obj) -> T* {
        if (entries.size() < id + 1) {
            entries.resize(id + 1);
        }
        auto ptr = (entries[id] = std::move(obj)).get();
        objects.insert_or_assign(std::move(name), ptr);
        return ptr;
    }

    void clear() {
        objects.clear();
        entries.clear();
    }
};

template <typename T>
using Registry = DynamicRegistry<std::string, T>;