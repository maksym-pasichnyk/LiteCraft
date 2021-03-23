#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera {
public:
    auto getProjection() const noexcept -> glm::mat4 {
        return _projection;
    }

    void setSize(uint32_t width, uint32_t height) {
        const float aspect_ratio = float(width) / float(height);
//        const float tanHalfFovy = glm::tan(glm::radians(field_of_view) * 0.5f);
//
//        const float a = 1.0f / (aspect_ratio * tanHalfFovy);
//        const float b = 1.0f / tanHalfFovy;
//        const float c = (far_clipping_plane + near_clipping_plane) / (far_clipping_plane - near_clipping_plane);
//        const float d = 2.0f * (near_clipping_plane * far_clipping_plane) / (near_clipping_plane - far_clipping_plane);
//
//        _projection[0][0] = a;
//        _projection[1][1] = b;
//        _projection[2][2] = c;
//        _projection[2][3] = 1.0f;
//        _projection[3][2] = 2.0f * d;

        _projection = glm::perspective(glm::radians(field_of_view), aspect_ratio, near_clipping_plane, far_clipping_plane);
    }

private:
    float field_of_view = 60.0f;
    float near_clipping_plane = 0.025f;
    float far_clipping_plane = 2500.0f;

    glm::mat4 _projection;
};
