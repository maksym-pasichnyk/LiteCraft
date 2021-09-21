#pragma once

#include "ModelCubeFormat.hpp"

#include <vector>
#include <optional>

struct ModelBoneFormat {
    std::string name;
    std::optional<std::string> parent;

    glm::vec3 pivot;
    std::optional<glm::vec3> bind_pose_rotation;
    std::optional<glm::vec3> rotation;

    bool never_render = false;
    bool mirror = false;
    bool reset = false;

    std::vector<ModelCubeFormat> cubes;
};