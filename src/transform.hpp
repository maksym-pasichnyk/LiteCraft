#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct Transform {
    glm::vec3 position{};
    glm::vec2 rotation{};

    auto getRotationMatrix() const -> glm::mat4 {
        return getRotationMatrix(rotation);
    }

    auto getTransformMatrix() const -> glm::mat4 {
        return glm::translate(getRotationMatrix(), -position);
    }

    auto getTransformMatrix(glm::vec3 offset) const -> glm::mat4 {
        return glm::translate(getRotationMatrix(), -(position + offset));
    }

    auto forward() const -> glm::vec3 {
        return glm::vec3(0, 0, -1) * glm::mat3(getRotationMatrix());
    }

    static auto getRotationMatrix(const glm::vec2& rotation) -> glm::mat4 {
        return glm::eulerAngleXY(glm::radians(rotation.y), glm::radians(rotation.x));
    }
};

