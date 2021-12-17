#pragma once

#include "ModelBoneFormat.hpp"

#include <map>
#include <cmath>
#include <string>
#include <memory>
#include <optional>

struct ModelFormat {
    std::string name;
    std::optional<std::string> parent;

    int32_t visible_bounds_width;
    int32_t visible_bounds_height;
    glm::vec3 visible_bounds_offset;

    int32_t texture_width;
    int32_t texture_height;

    std::map<std::string, std::unique_ptr<ModelBoneFormat>> bones;
};