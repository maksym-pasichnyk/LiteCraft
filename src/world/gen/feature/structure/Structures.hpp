#pragma once

#include "../../GenerationStage.hpp"

#include <util/Registry.hpp>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <map>

struct Structure;
struct Structures {
    static Registry<Structure> registry;
    static std::array<std::vector<Structure*>, 10> stages;

    template <typename T, typename... Args>
    static auto create(const std::string& name, GenerationStage::Decoration stage, Args&&... args) -> Structure* {
        auto structure = registry.add(name, std::make_unique<T>(std::forward<Args>(args)...));
        stages.at(static_cast<size_t>(stage)).emplace_back(structure);
        return structure;
    }

    static void init();
};