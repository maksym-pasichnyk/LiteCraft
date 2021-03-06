#pragma once

#include "ModelFaceFormat.hpp"

#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>

struct ModelCubeFormat {
    glm::vec3 origin;
    glm::vec3 rotation;
    glm::vec3 size;

    bool uv_box = true;

    glm::vec2 uv;
    std::unordered_map<std::string, ModelFaceFormat> faces;
};