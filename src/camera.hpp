#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera {
public:
    auto getProjection() const noexcept -> glm::mat4 {
        return _projection;
    }

    void setSize(const glm::ivec2& size) {
        const auto clip = glm::mat4{
            1.0f,  0.0f, 0.0f, 0.0f,
            0.0f, -1.0f, 0.0f, 0.0f,
            0.0f,  0.0f, 1.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 1.0f
        };

        _projection = clip * glm::infinitePerspective(glm::radians(fov), float(size.x) / float(size.y), z_near);
    }

private:
    float fov = 60.0f;
    float z_near = 0.15f;
    glm::mat4 _projection;
};
