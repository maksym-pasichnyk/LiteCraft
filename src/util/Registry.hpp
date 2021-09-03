#pragma once

#include <optional>
#include <memory>
#include <vector>
#include <string>
#include <map>

template <typename T>
struct Registry {
    std::vector<std::unique_ptr<T>> entries{};
    std::map<std::string, T*> objects{};

    auto name(T* obj) const -> std::optional<std::string> {
        for (const auto& [key, val] : objects) {
            if (val == obj) {
                return key;
            }
        }
        return std::nullopt;
    }

    auto get(const std::string& name) -> std::optional<T*> {
        if (auto it = objects.find(name); it != objects.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    auto add(std::string name, std::unique_ptr<T>&& obj) -> T* {
        auto ptr = entries.emplace_back(std::move(obj)).get();
        objects.insert_or_assign(std::move(name), ptr);
        return ptr;
    }

    auto add(size_t id, std::string name, std::unique_ptr<T>&& obj) -> T* {
        if (entries.size() < id + 1) {
            entries.resize(id + 1);
        }
        auto ptr = (entries[id] = std::move(obj)).get();
        objects.insert_or_assign(std::move(name), ptr);
        return ptr;
    }
};