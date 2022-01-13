#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

enum class RenderType;

struct Vertex {
    glm::vec3 pos;
    glm::vec2 tex;
    glm::u8vec4 color;
    glm::u8vec4 light;
};

struct RenderLayerBuilder {
    std::vector<Vertex>& vertices;
    std::vector<glm::u32>& indices;

    void quad() {
        const auto i = vertices.size();
        indices.push_back(static_cast<glm::u32>(i + 0));
        indices.push_back(static_cast<glm::u32>(i + 1));
        indices.push_back(static_cast<glm::u32>(i + 2));
        indices.push_back(static_cast<glm::u32>(i + 0));
        indices.push_back(static_cast<glm::u32>(i + 2));
        indices.push_back(static_cast<glm::u32>(i + 3));
    }

    void quadInv() {
        const auto i = vertices.size();
        indices.push_back(static_cast<glm::u32>(i + 0));
        indices.push_back(static_cast<glm::u32>(i + 2));
        indices.push_back(static_cast<glm::u32>(i + 1));
        indices.push_back(static_cast<glm::u32>(i + 0));
        indices.push_back(static_cast<glm::u32>(i + 3));
        indices.push_back(static_cast<glm::u32>(i + 2));
    }

    void vertex(float x, float y, float z, float u, float v, uint8_t r, uint8_t g, uint8_t b, int32_t packedLight, float ao) {
        vertices.push_back(Vertex{
            .pos{x, y, z},
            .tex{u, v},
            .color{r, g, b, ao * 255},
            .light{
                ((packedLight >> 0) & 0xF) * 17,
                0,
                0,
                ((packedLight >> 4) & 0xF) * 17
            }
        });
    }
};

struct RenderBuffer {
    std::vector<Vertex> vertices;
    std::array<std::vector<glm::u32>, 3> indices{};

    RenderBuffer() {
        vertices.reserve(20000);
        indices[0].reserve(20000);
        indices[1].reserve(20000);
        indices[2].reserve(20000);
    }

    auto get(RenderType layer) -> RenderLayerBuilder {
        return RenderLayerBuilder {
            .vertices = vertices,
            .indices = indices[static_cast<size_t>(layer)]
        };
    }

    void clear() {
        vertices.clear();
        for (auto& submesh : indices) {
            submesh.clear();
        }
    }
};
