#pragma once

#include <util/Registry.hpp>
#include <memory>
#include <vector>
#include <string>
#include <map>

struct WorldCarver;
struct Carvers {
    static Registry<WorldCarver> carvers;

    template <typename T, typename... Args>
    static auto create(std::string name, Args&&... args) -> WorldCarver* {
        return carvers.add(std::move(name), std::make_unique<T>(std::forward<Args>(args)...));
    }

    static void init();
};