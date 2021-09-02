#pragma once

#include <util/Registry.hpp>

struct ConfiguredCarver;
struct ConfiguredCarvers {
    static Registry<ConfiguredCarver> carvers;

    static ConfiguredCarver* CAVE;
    static ConfiguredCarver* CANYON;
    static ConfiguredCarver* OCEAN_CAVE;
    static ConfiguredCarver* NETHER_CAVE;

    static void configureCarvers();
};