#pragma once

#include "../../GenerationStage.hpp"

#include <map>
#include <string>
#include <memory>
#include <vector>

struct Structure;
struct Structures {
    static std::map<std::string, std::unique_ptr<Structure>> registry;
    static std::vector<std::vector<Structure*>> stages;

    static Structure* MINESHAFT;

    static void registerStructures();
};