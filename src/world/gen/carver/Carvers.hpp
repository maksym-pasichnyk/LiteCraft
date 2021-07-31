#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

struct WorldCarver;
struct Carvers {
    static std::vector<std::unique_ptr<WorldCarver>> carvers;
    static std::map<std::string, WorldCarver*> registry;

    static WorldCarver* CAVE;
    static WorldCarver* NETHER_CAVE;
    static WorldCarver* CANYON;
//    static WorldCarver* UNDERWATER_CANYON;
//    static WorldCarver* UNDERWATER_CAVE;

    static void registerCarvers();
};