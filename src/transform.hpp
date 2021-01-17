#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct Transform {
    float yaw = 0;
    float pitch = 0;
    glm::vec3 position{0, 0, -5};

    auto getRotationMatrix() -> glm::mat4 {
        return getRotationMatrix(yaw, pitch);
    }

    auto getTransformMatrix() -> glm::mat4 {
        return glm::translate(getRotationMatrix(), -position);
    }

	auto getViewMatrix() -> glm::mat4 {
        return glm::translate(getRotationMatrix(), -(position + glm::vec3(0, 1.68, 0)));
    }

    auto forward() -> glm::vec3 {
    	return glm::vec3(0, 0, 1) * glm::mat3(getRotationMatrix());
    }

    auto right() -> glm::vec3 {
    	return glm::vec3(1, 0, 0) * glm::mat3(getRotationMatrix());
    }

    static auto getRotationMatrix(float yaw, float pitch) -> glm::mat4 {
        yaw = glm::radians(yaw);
        pitch = glm::radians(pitch);

        float sp = glm::sin(pitch);
        float cp = glm::cos(pitch);

        float c = glm::cos(yaw);
        float s = glm::sin(yaw);

        return {
                c, sp * s, -cp * s, 0,
                0, cp, sp, 0,
                s, -sp * c, cp * c, 0,
                0, 0, 0, 1
        };
    }
};
