#pragma once

#include <memory>
#include <string>
#include <map>

struct WorldCarver;
struct Carvers {
    static std::map<std::string, std::unique_ptr<WorldCarver>> carvers;
    static WorldCarver* CAVE;
    static WorldCarver* NETHER_CAVE;
    static WorldCarver* CANYON;
//    static WorldCarver* UNDERWATER_CANYON;
//    static WorldCarver* UNDERWATER_CAVE;

    static void registerCarvers();
};