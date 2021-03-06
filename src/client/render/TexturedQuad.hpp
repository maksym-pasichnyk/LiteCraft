#pragma once

#include "PositionTextureVertex.hpp"

#include <array>
#include <glm/vec3.hpp>

struct TexturedQuad {
    std::array<PositionTextureVertex, 4> vertices;
    glm::vec3 normal;
};