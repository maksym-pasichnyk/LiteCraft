#pragma once

#include "StructureFeature.hpp"

#include <util/Registry.hpp>
#include <memory>
#include <string>
#include <array>
#include <map>

struct ResourceManager;
struct StructureFeatures {
    static Registry<StructureFeature> registry;

    static void init();
};