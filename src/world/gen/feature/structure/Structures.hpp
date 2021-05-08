#pragma once

#include "../../GenerationStage.hpp"

#include <map>
#include <array>
#include <string>
#include <memory>
#include <vector>

struct Structure;
struct Structures {
    static std::map<std::string, std::unique_ptr<Structure>> registry;
    static std::array<std::vector<Structure*>, 10> stages;

    static Structure* MINESHAFT;

    static void registerStructures();
};