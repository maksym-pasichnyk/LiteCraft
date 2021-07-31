#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

template <typename T>
struct Registry {
    std::vector<std::unique_ptr<T>> entries{};
    std::map<std::string, T*> objects{};

    auto get(const std::string& name) -> T* {
        if (auto it = objects.find(name); it != objects.end()) {
            return it->second;
        }
        return nullptr;
    }

    auto add(std::string name, std::unique_ptr<T>&& obj) -> T* {
        auto ptr = entries.emplace_back(std::move(obj)).get();
        objects.insert_or_assign(std::move(name), ptr);
        return ptr;
    }
};