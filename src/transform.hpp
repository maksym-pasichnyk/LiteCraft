#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

struct Transform {
    glm::vec3 position{};
    glm::vec2 rotation{};

    auto orientation() const -> glm::mat4 {
        return glm::yawPitchRoll(glm::radians(rotation.x), glm::radians(rotation.y), 0.0f);
    }

    auto forward() const -> glm::vec3 {
        return glm::normalize(glm::vec3(orientation() * glm::vec4(0, 0, -1, 1)));
    }

    auto right() const -> glm::vec3 {
        return glm::normalize(glm::vec3(orientation() * glm::vec4(1, 0, 0, 1)));
    }

    auto up() const -> glm::vec3 {
        return glm::normalize(glm::vec3(orientation() * glm::vec4(0, 1, 0, 1)));
    }

    auto localToWorldMatrix() const -> glm::mat4 {
        return glm::translate(glm::mat4(1.0f), position) * orientation();
    }

    auto transformPoint(const glm::vec3& p) const -> glm::vec3 {
        return position + glm::mat3(orientation()) * p;
    }
};

