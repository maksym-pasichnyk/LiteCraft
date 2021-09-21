#pragma once

#include "ModelFaceFormat.hpp"

#include <string>
#include <variant>
#include <glm/vec3.hpp>
#include <unordered_map>

using ModelTexFormat = std::variant<glm::vec2, std::unordered_map<std::string, ModelFaceFormat>>;

struct ModelCubeFormat {
    glm::vec3 origin;
    glm::vec3 rotation;
    glm::vec3 size;
    ModelTexFormat tex;
};