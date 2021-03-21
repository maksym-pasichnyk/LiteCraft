#pragma once

#include <glm/vec3.hpp>

struct TemperatureModifiers {
    static float none(glm::ivec3 pos, float temperature);
    static float frozen(glm::ivec3 pos, float temperature);
};
