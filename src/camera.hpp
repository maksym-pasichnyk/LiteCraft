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
//        _projection = glm::perspective(glm::radians(field_of_view), aspect_ratio, near_clipping_plane, far_clipping_plane);
        _projection = MakeInfReversedZProjRH(glm::radians(field_of_view), aspect_ratio, near_clipping_plane/*, far_clipping_plane*/);
    }

    static glm::mat4 MakeInfReversedZProjRH(float fovY_radians, float aspectWbyH, float zNear)
    {
        float f = 1.0f / glm::tan(fovY_radians / 2.0f);
        return glm::mat4(f / aspectWbyH, 0.0f,  0.0f,  0.0f,
                0.0f,    f,  0.0f,  0.0f,
                0.0f, 0.0f,  0.0f, -1.0f,
                0.0f, 0.0f, zNear,  0.0f);
    }

private:
    float field_of_view = 60.0f;
    float near_clipping_plane = 0.15f;//0.025f;
//    float far_clipping_plane = 250000.0f;

    glm::mat4 _projection;
};
