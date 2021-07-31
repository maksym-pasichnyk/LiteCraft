#pragma once

#include "../../GenerationStage.hpp"

#include <string>
#include <memory>
#include <vector>
#include <array>
#include <map>

struct Structure;
struct Structures {
    static std::map<std::string, std::unique_ptr<Structure>> registry;
    static std::array<std::vector<Structure*>, 10> stages;

    static Structure* MINESHAFT;

    static void registerStructures();
};