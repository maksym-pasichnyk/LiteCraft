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

    static Structure* MINESHAFT;
    static Structure* SWAMP_HUT;
    static Structure* JUNGLE_PYRAMID;
    static Structure* DESERT_PYRAMID;

    template <typename T, typename... Args>
    static auto create(const std::string& name, GenerationStage::Decoration stage, Args&&... args) -> T* {
        auto structure = registry.add(name, std::make_unique<T>(std::forward<Args>(args)...));
        stages.at(static_cast<int>(stage)).emplace_back(structure);
        return dynamic_cast<T*>(structure);
    }

    static void registerStructures();
};