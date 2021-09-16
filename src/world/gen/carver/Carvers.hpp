#pragma once

#include <util/Registry.hpp>
#include <memory>
#include <vector>
#include <string>
#include <map>

struct WorldCarver;
struct Carvers {
    static Registry<WorldCarver> carvers;

    static WorldCarver* CAVE;
    static WorldCarver* NETHER_CAVE;
    static WorldCarver* CANYON;
//    static WorldCarver* UNDERWATER_CANYON;
//    static WorldCarver* UNDERWATER_CAVE;

    static void init();
};