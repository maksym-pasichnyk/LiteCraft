#pragma once

#include "../../GenerationStage.hpp"

#include <util/Registry.hpp>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <map>

struct Structure;
struct Structures {
    static Registry<Structure> registry;
    static std::array<std::vector<Structure*>, 10> stages;

    static void init();
};