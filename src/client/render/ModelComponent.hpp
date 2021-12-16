#pragma once

#include "TexturedQuad.hpp"
#include "model/ModelFormat.hpp"

#include <Mesh.hpp>
#include <util/match.hpp>

struct BlockVertex {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 coords;
};

struct ModelVertexBuilder {
    std::vector<BlockVertex> vertices;
    std::vector<int> indices;

    void clear() {
        vertices.clear();
        indices.clear();
    }

    void quad() {
        auto i = vertices.size();
        indices.push_back(i + 0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i + 0);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
    }
    void quadInv() {
        auto i = vertices.size();
        indices.push_back(i + 0);
        indices.push_back(i + 2);
        indices.push_back(i + 1);
        indices.push_back(i + 0);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }

    void vertex(float x, float y, float z, float u, float v, float r, float g, float b) {
        vertices.push_back(BlockVertex{
            .vertex{x, y, z},
            .normal{r, g, b},
            .coords{u, v}
        });
    }
};

struct ModelComponent {
    Mesh mesh;
    
    explicit ModelComponent(const ModelFormat& model_format) /*: material(material)*/ {
//        const auto attributes = std::array{
//            VertexArrayAttrib{0, 3, GL_FLOAT, GL_FALSE, offsetof(BlockVertex, vertex)},
//            VertexArrayAttrib{1, 3, GL_FLOAT, GL_FALSE, offsetof(BlockVertex, normal)},
//            VertexArrayAttrib{2, 2, GL_FLOAT, GL_FALSE, offsetof(BlockVertex, coords)},
//        };
//
//        const auto bindings = std::array{
//            VertexArrayBinding{0, 0},
//            VertexArrayBinding{1, 0},
//            VertexArrayBinding{2, 0}
//        };
//
//        mesh = std::make_unique<Mesh>(attributes, bindings, sizeof(BlockVertex), GL_STREAM_DRAW);
        
        const auto tex_width = model_format.texture_width;
        const auto tex_height = model_format.texture_height;

        ModelVertexBuilder builder{};

        for (auto&& [name, bone] : model_format.bones) {
            if (bone->never_render) continue;

            for (auto&& cube : bone->cubes) {
                auto&& from = cube.origin;
                auto&& size = cube.size;

                const auto x0 = from.x / 16.0f;
                const auto y0 = from.y / 16.0f;
                const auto z0 = from.z / 16.0f;
                const auto x1 = x0 + size.x / 16.0f;
                const auto y1 = y0 + size.y / 16.0f;
                const auto z1 = z0 + size.z / 16.0f;

                match(cube.tex,
                    [&](const glm::vec2& uv) {
                        const auto inv_w = 1.0f / static_cast<float>(tex_width);
                        const auto inv_h = 1.0f / static_cast<float>(tex_height);

                        const auto [u, v] = uv;
                        const auto u0 = (u) * inv_w;
                        const auto u1 = (u + size.z) * inv_w;
                        const auto u2 = (u + size.z + size.x) * inv_w;
                        const auto u3 = (u + size.z + size.x + size.x) * inv_w;
                        const auto u4 = (u + size.z + size.x + size.z) * inv_w;
                        const auto u5 = (u + size.z + size.x + size.z + size.x) * inv_w;
                        const auto v0 = (v) * inv_h;
                        const auto v1 = (v + size.z) * inv_h;
                        const auto v2 = (v + size.z + size.y) * inv_h;

                        create_quad(builder, {0, 0, -1.0f}, {
                            PositionTextureVertex{x0, y0, z0, u1, v2},
                            PositionTextureVertex{x0, y1, z0, u1, v1},
                            PositionTextureVertex{x1, y1, z0, u2, v1},
                            PositionTextureVertex{x1, y0, z0, u2, v2}
                        });

                        create_quad(builder, {1.0f, 0, 0}, {
                            PositionTextureVertex{x1, y0, z0, u1, v2},
                            PositionTextureVertex{x1, y1, z0, u1, v1},
                            PositionTextureVertex{x1, y1, z1, u0, v1},
                            PositionTextureVertex{x1, y0, z1, u0, v2}
                        });

                        create_quad(builder, {0, 0, 1.0f}, {
                            PositionTextureVertex{x1, y0, z1, u4, v2},
                            PositionTextureVertex{x1, y1, z1, u4, v1},
                            PositionTextureVertex{x0, y1, z1, u5, v1},
                            PositionTextureVertex{x0, y0, z1, u5, v2}
                        });

                        create_quad(builder, {-1.0f, 0, 0}, {
                            PositionTextureVertex{x0, y0, z1, u0, v2},
                            PositionTextureVertex{x0, y1, z1, u0, v1},
                            PositionTextureVertex{x0, y1, z0, u1, v1},
                            PositionTextureVertex{x0, y0, z0, u1, v2}
                        });

                        create_quad(builder, {0, 1.0f, 0}, {
                            PositionTextureVertex{x0, y1, z0, u1, v1},
                            PositionTextureVertex{x0, y1, z1, u1, v0},
                            PositionTextureVertex{x1, y1, z1, u2, v0},
                            PositionTextureVertex{x1, y1, z0, u2, v1}
                        });

                        create_quad(builder, {0, -1.0f, 0}, {
                            PositionTextureVertex{x0, y0, z1, u2, v0},
                            PositionTextureVertex{x0, y0, z0, u2, v1},
                            PositionTextureVertex{x1, y0, z0, u3, v1},
                            PositionTextureVertex{x1, y0, z1, u3, v0}
                        });
                    },
                    [&](const std::unordered_map<std::string, ModelFaceFormat>& faces) {
                        const auto p0 = glm::vec3{x0, y0, z0};
                        const auto p1 = glm::vec3{x1, y0, z0};
                        const auto p2 = glm::vec3{x1, y0, z1};
                        const auto p3 = glm::vec3{x0, y0, z1};
                        const auto p4 = glm::vec3{x0, y1, z0};
                        const auto p5 = glm::vec3{x1, y1, z0};
                        const auto p6 = glm::vec3{x1, y1, z1};
                        const auto p7 = glm::vec3{x0, y1, z1};

                        if (auto face = faces.find("south"); face != faces.end()) {
                            const auto [u, v] = face->second.uv;
                            create_face(builder, p0, p4, p5, p1, u, v, u + size.x, v + size.y, tex_width, tex_height, {0, 0, -1.0f});
                        }

                        if (auto face = faces.find("east"); face != faces.end()) {
                            const auto [u, v] = face->second.uv;
                            create_face(builder, p1, p5, p6, p2, u, v, u + size.z, v + size.y, tex_width, tex_height, {1.0f, 0, 0});
                        }

                        if (auto face = faces.find("north"); face != faces.end()) {
                            const auto [u, v] = face->second.uv;
                            create_face(builder, p2, p6, p7, p3, u, v, u + size.x, v + size.y, tex_width, tex_height, {0, 0, 1.0f});
                        }

                        if (auto face = faces.find("west"); face != faces.end()) {
                            const auto [u, v] = face->second.uv;
                            create_face(builder, p3, p7, p4, p0, u, v, u + size.z, v + size.y, tex_width, tex_height, {-1.0f, 0, 0});
                        }

                        if (auto face = faces.find("up"); face != faces.end()) {
                            const auto [u, v] = face->second.uv;
                            create_face(builder, p4, p7, p6, p5, u, v, u + size.x, v + size.z, tex_width, tex_height, {0, 1.0f, 0});
                        }

                        if (auto face = faces.find("down"); face != faces.end()) {
                            const auto [u, v] = face->second.uv;
                            create_face(builder, p3, p0, p1, p2, u, v, u + size.x, v + size.z, tex_width, tex_height, {0, -1.0f, 0});
                        }
                    }
                );
            }
        }

        mesh.setIndexBufferParams(builder.indices.size(), sizeof(glm::u32));
        mesh.setIndexBufferData(std::as_bytes(std::span(builder.indices)), 0);

        mesh.setVertexBufferParams(builder.vertices.size(), sizeof(BlockVertex));
        mesh.setVertexBufferData(std::as_bytes(std::span(builder.vertices)), 0);
    }

    static void create_face(ModelVertexBuilder& builder, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, float u0, float v0, float u1, float v1, int texWidth, int texHeight, const glm::vec3& normal) {
        const auto inv_w = 1.0f / static_cast<float>(texWidth);
        const auto inv_h = 1.0f / static_cast<float>(texHeight);

        builder.quad();
        builder.vertex(p1.x, p1.y, p1.z, u0 * inv_w, v0 * inv_h, normal.x, normal.y, normal.z);
        builder.vertex(p2.x, p2.y, p2.z, u0 * inv_w, v1 * inv_h, normal.x, normal.y, normal.z);
        builder.vertex(p3.x, p3.y, p3.z, u1 * inv_w, v1 * inv_h, normal.x, normal.y, normal.z);
        builder.vertex(p4.x, p4.y, p4.z, u1 * inv_w, v0 * inv_h, normal.x, normal.y, normal.z);
    }

    static void create_quad(ModelVertexBuilder& builder, const glm::vec3& normal, const std::array<PositionTextureVertex, 4>& vertices) {
        builder.quad();
        for (const auto& vertex : vertices) {
            builder.vertex(vertex.x, vertex.y, vertex.z, vertex.u, vertex.v, normal.x, normal.y, normal.z);
        }
    }
};