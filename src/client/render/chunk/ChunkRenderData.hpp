#pragma once

#include "client/render/RenderBuffer.hpp"

#include <array>

struct Submesh {
    glm::i32 index_offset = 0;
    glm::i32 index_count = 0;
};

struct ChunkRenderData {
    Mesh mesh;
//    std::array<Submesh, 3> layers{};

    RenderBuffer rb{};
    bool needRender = false;

    void update() {
        glm::i32 index_count = 0;
        for (auto& subindices : rb.indices) {
            index_count += static_cast<glm::i32>(subindices.size());
        }

        mesh.setIndexBufferParams(index_count, sizeof(glm::u32));

        mesh.setVertexBufferParams(rb.vertices.size(), sizeof(BlockVertex));
        mesh.setVertexBufferData(std::as_bytes(std::span(rb.vertices)), 0);

        mesh.setSubmeshCount(rb.indices.size());

        glm::i32 index_offset = 0;
        for (glm::i32 i = 0; i < rb.indices.size(); ++i) {
            auto& subindices = rb.indices[i];

            mesh.setSubmesh(i, SubMesh{
                .indexCount = static_cast<glm::i32>(subindices.size()),
                .indexOffset = index_offset
            });
            if (!subindices.empty()) {
                mesh.setIndexBufferData(std::as_bytes(std::span(subindices)), index_offset * sizeof(glm::u32));
            }
            index_offset += static_cast<glm::i32>(subindices.size());
        }
    }
};
