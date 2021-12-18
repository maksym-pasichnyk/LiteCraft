#pragma once

#include <array>
#include <Mesh.hpp>
#include <client/render/RenderBuffer.hpp>
#include <client/render/ModelComponent.hpp>

struct ChunkRenderData {
    Mesh mesh{};
    RenderBuffer rb{};
    bool needRender = false;

    void update() {
        glm::i32 index_count = 0;
        for (auto& subindices : rb.indices) {
            index_count += static_cast<glm::i32>(subindices.size());
        }

        mesh.setSubmeshCount(glm::i32(rb.indices.size()));
        mesh.setIndexBufferParams(index_count, sizeof(glm::u32));
        mesh.setVertexBufferParams(glm::i32(rb.vertices.size()), sizeof(BlockVertex));

        if (!rb.vertices.empty()) {
            mesh.setVertexBufferData(std::as_bytes(std::span(rb.vertices)), 0);
        }

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
