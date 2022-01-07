#pragma once

#include <world/gen/feature/structure/Structure.hpp>

struct Village {
    static auto create() -> std::unique_ptr<Structure>;
};