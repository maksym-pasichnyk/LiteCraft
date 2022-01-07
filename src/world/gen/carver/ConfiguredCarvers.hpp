#pragma once

#include <util/Registry.hpp>

struct ResourceManager;
struct ConfiguredCarver;
struct ConfiguredCarvers {
    static Registry<ConfiguredCarver> carvers;

    static void init();
};