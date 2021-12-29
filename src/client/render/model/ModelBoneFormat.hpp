#pragma once

#include "ModelCubeFormat.hpp"

#include <vector>
#include <tl/optional.hpp>

struct ModelBoneFormat {
    std::string name;
    tl::optional<std::string> parent;

    glm::vec3 pivot;
    tl::optional<glm::vec3> bind_pose_rotation;
    tl::optional<glm::vec3> rotation;

    bool never_render = false;
    bool mirror = false;
    bool reset = false;

    std::vector<ModelCubeFormat> cubes;
};