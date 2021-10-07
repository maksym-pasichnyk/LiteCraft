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
        _projection = MakeInfReversedZProjRH(glm::radians(field_of_view), aspect_ratio, near_clipping_plane);
    }

    static auto MakeInfReversedZProjRH(float fovY_radians, float aspectWbyH, float zNear) -> glm::mat4 {
        const auto f = 1.0f / glm::tan(fovY_radians * 0.5f);
        const auto a = f / aspectWbyH;
        const auto b = f;
        const auto c = -1.0f;
        const auto d = zNear;

        return {
            a, 0, 0, 0,
            0, b, 0, 0,
            0, 0, 0, c,
            0, 0, d, 0
        };
    }

private:
    float field_of_view = 60.0f;
    float near_clipping_plane = 0.15f;

    glm::mat4 _projection;
};
