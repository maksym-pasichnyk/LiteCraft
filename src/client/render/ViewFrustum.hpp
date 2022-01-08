#pragma once

#include "chunk/ChunkRenderData.hpp"

#include <vector>

struct ViewFrustum {
    int stride;
    std::array<glm::vec4, 6> planes{};
    std::vector<ChunkRenderData> chunks{};

    explicit ViewFrustum(int viewDistance) : stride(viewDistance * 2 + 1), chunks(stride * stride) {}

    [[nodiscard]] static auto NormalizePlane(const glm::vec4& plane) -> glm::vec4 {
        const auto normal = glm::vec3(plane.x, plane.y, plane.z);
        return plane * glm::inversesqrt(glm::dot(normal, normal));
    }

    constexpr void ExtractPlanes(const glm::mat4x4& m, bool normalize) {
        // Left clipping plane
        planes[0] = m[3] + m[0];
        // Right clipping plane
        planes[1] = m[3] - m[0];
        // Top clipping plane
        planes[2] = m[3] - m[1];
        // Bottom clipping plane
        planes[3] = m[3] + m[1];
        // Near clipping plane
        planes[4] = m[3] + m[2];
        // Far clipping plane
        planes[5] = m[3] - m[2];

        // Normalize the plane equations, if requested
        if (normalize == true) {
            planes[0] = NormalizePlane(planes[0]);
            planes[1] = NormalizePlane(planes[1]);
            planes[2] = NormalizePlane(planes[2]);
            planes[3] = NormalizePlane(planes[3]);
            planes[4] = NormalizePlane(planes[4]);
            planes[5] = NormalizePlane(planes[5]);
        }
    }

    auto TestAABB(const glm::vec3& bounds_min, const glm::vec3& bounds_max) const -> bool {
        for (const auto& [nx, ny, nz, distance] : planes) {
            const auto normal = glm::vec3(nx, ny, nz);
            if (glm::dot(normal, glm::mix(bounds_max, bounds_min, glm::lessThan(normal, glm::vec3(0.0f)))) + distance < 0) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] auto getChunk(int x, int z) -> ChunkRenderData& {
        const auto ix = floorMod(x, stride);
        const auto iz = floorMod(z, stride);
        return chunks[ix + iz * static_cast<size_t>(stride)];
    }
    
    void markForRender(int x, int z) {
        const auto ix = floorMod(x, stride);
        const auto iz = floorMod(z, stride);
        const auto i = static_cast<size_t>(ix + iz * stride);
        chunks[i].needRender = true;
    }

private:
    static auto floorMod(int x, int y) -> int {
        return ((x % y) + y) % y;
    }
};
