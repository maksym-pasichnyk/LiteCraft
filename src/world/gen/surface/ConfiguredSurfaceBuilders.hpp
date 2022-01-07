#pragma once

#include "ConfiguredSurfaceBuilder.hpp"

#include <util/Registry.hpp>
#include <memory>
#include <map>

struct ResourceManager;
struct ConfiguredSurfaceBuilders {
    static Registry<ConfiguredSurfaceBuilder> builders;

    static void init();
};