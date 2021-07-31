#pragma once

#include "client/render/RenderBuffer.hpp"

#include <array>

struct ChunkRenderData {
    static constexpr std::array attributes {
        VertexArrayAttrib{0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos)},
        VertexArrayAttrib{1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, tex)},
        VertexArrayAttrib{2, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, color)},
        VertexArrayAttrib{3, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, light)}
    };

    static constexpr std::array bindings {
        VertexArrayBinding{0, 0},
        VertexArrayBinding{1, 0},
        VertexArrayBinding{2, 0},
        VertexArrayBinding{3, 0},
    };

    Mesh mesh{attributes, bindings, sizeof(Vertex), GL_DYNAMIC_DRAW};
    std::array<Submesh, 3> layers{};

    RenderBuffer rb{};
    bool needRender = false;

    void update() {
        glm::i32 index_count = 0;
        for (auto& subindices : rb.indices) {
            index_count += subindices.size();
        }

        mesh.SetVertices(std::span(rb.vertices));
        mesh.SetIndicesCount(index_count);

        glm::i32 submesh_index = 0;
        glm::i32 index_offset = 0;

        for (auto& submesh : rb.indices) {
            layers[submesh_index].index_offset = index_offset;
            layers[submesh_index].index_count = submesh.size();
            if (!submesh.empty()) {
                mesh.SetIndicesData(submesh, index_offset);
            }
            index_offset += layers[submesh_index].index_count;
            submesh_index++;
        }
    }
};
