#pragma once

#include "StructureFeature.hpp"

#include <util/Registry.hpp>
#include <memory>
#include <string>
#include <array>
#include <map>

struct StructureFeatures {
    static Registry<StructureFeature> registry;

    static auto configure(std::string name, Structure* structure, StructureConfig config) -> StructureFeature* {
        return registry.add(std::move(name), std::make_unique<StructureFeature>(StructureFeature{
            .structure = structure,
            .config = config
        }));
    }

    static void init();
};