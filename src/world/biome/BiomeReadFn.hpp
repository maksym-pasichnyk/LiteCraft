#pragma once

#include <functional>
#include <glm/vec3.hpp>

struct Biome;
using BiomeReadFn = std::function<Biome*(glm::ivec3)>;