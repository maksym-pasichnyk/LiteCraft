#pragma once

#include "TexturedQuad.hpp"
#include "model/ModelFormat.hpp"

struct ModelVertex {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 coords;
};

struct ModelVertexBuilder {
    std::vector<ModelVertex> vertices;
    std::vector<int> indices;

    void clear() {
        vertices.clear();
        indices.clear();
    }

    void quad() {
        auto i = vertices.size();
        indices.push_back(i + 0);
        indices.push_back(i + 2);
        indices.push_back(i + 1);
        indices.push_back(i + 0);
        indices.push_back(i + 3);
        indices.push_back(i + 2);
    }
    void quadInv() {
        auto i = vertices.size();
        indices.push_back(i + 0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i + 0);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
    }

    void vertex(float x, float y, float z, float u, float v, float r, float g, float b) {
        vertices.push_back(ModelVertex{
            .vertex{x, y, z},
            .normal{r, g, b},
            .coords{u, v}
        });
    }
};

struct ModelMesh {
    GLuint vao = GL_NONE;
    GLuint vbo = GL_NONE;
    GLuint ibo = GL_NONE;
    GLsizeiptr vbo_size{0};
    GLsizeiptr ibo_size{0};
    int index_count{0};
    int vertex_count{0};

    ModelMesh() {
        glCreateVertexArrays(1, &vao);
        glCreateBuffers(1, &vbo);
        glCreateBuffers(1, &ibo);

        glVertexArrayElementBuffer(vao, ibo);
        glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(ModelVertex));

        glEnableVertexArrayAttrib(vao, 0);
        glEnableVertexArrayAttrib(vao, 1);
        glEnableVertexArrayAttrib(vao, 2);

        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(ModelVertex, vertex));
        glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, offsetof(ModelVertex, normal));
        glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(ModelVertex, coords));

        glVertexArrayAttribBinding(vao, 0, 0);
        glVertexArrayAttribBinding(vao, 1, 0);
        glVertexArrayAttribBinding(vao, 2, 0);
    }

    ~ModelMesh() {
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void SetVertices(std::span<const ModelVertex> vertices) {
        vertex_count = vertices.size();
        if (vertices.size_bytes() > vbo_size) {
            vbo_size = vertices.size_bytes();
            glNamedBufferData(vbo, vertices.size_bytes(), vertices.data(), GL_DYNAMIC_DRAW);
        } else {
            glNamedBufferSubData(vbo, 0, vertices.size_bytes(), vertices.data());
        }
    }

    void SetIndicesCount(int32_t count) {
        GLsizeiptr buf_size = sizeof(int32_t) * count;

        index_count = count;
        if (buf_size > ibo_size) {
            ibo_size = buf_size;
            glNamedBufferData(ibo, buf_size, nullptr, GL_DYNAMIC_DRAW);
        }
    }

    void SetIndicesData(std::span<const int32_t> indices, int32_t offset) {
        glNamedBufferSubData(ibo, offset * sizeof(int32_t), indices.size_bytes(), indices.data());
    }

    void SetIndices(std::span<const int32_t> indices) {
        index_count = indices.size();
        if (indices.size_bytes() > ibo_size) {
            ibo_size = indices.size_bytes();
            glNamedBufferData(ibo, indices.size_bytes(), indices.data(), GL_DYNAMIC_DRAW);
        } else {
            glNamedBufferSubData(ibo, 0, indices.size_bytes(), indices.data());
        }
    }
};

struct ModelRendered {
    explicit ModelRendered(const ModelFormat& model_format) /*: material(material)*/ {
        const auto tex_width = model_format.texture_width;
        const auto tex_height = model_format.texture_height;

        ModelVertexBuilder buf{};

        for (auto& [name, bone] : model_format.bones) {
            if (bone->neverRender) continue;

            auto origin = bone->pivot;

            for (auto& cube : bone->cubes) {
                auto& faces = cube.faces;
                auto& from = cube.origin;
                auto& size = cube.size;

                auto x0 = from.x / 16.0f;
                auto y0 = from.y / 16.0f;
                auto z0 = from.z / 16.0f;

                auto x1 = x0 + size.x / 16.0f;
                auto y1 = y0 + size.y / 16.0f;
                auto z1 = z0 + size.z / 16.0f;

                if (cube.uv_box) {
                    auto [u, v] = cube.uv;

                    auto u0 = (u) / tex_width;
                    auto u1 = (u + size.z) / tex_width;
                    auto u2 = (u + size.z + size.x) / tex_width;
                    auto u3 = (u + size.z + size.x + size.x) / tex_width;
                    auto u4 = (u + size.z + size.x + size.z) / tex_width;
                    auto u5 = (u + size.z + size.x + size.z + size.x) / tex_width;

                    auto v0 = (v) / tex_height;
                    auto v1 = (v + size.z) / tex_height;
                    auto v2 = (v + size.z + size.y) / tex_height;

                    buildQuad(buf, {0, 0, -1.0f}, {
                        PositionTextureVertex{x0, y0, z0, u1, v2},
                        PositionTextureVertex{x0, y1, z0, u1, v1},
                        PositionTextureVertex{x1, y1, z0, u2, v1},
                        PositionTextureVertex{x1, y0, z0, u2, v2}
                    });

                    buildQuad(buf, {1.0f, 0, 0}, {
                        PositionTextureVertex{x1, y0, z0, u1, v2},
                        PositionTextureVertex{x1, y1, z0, u1, v1},
                        PositionTextureVertex{x1, y1, z1, u0, v1},
                        PositionTextureVertex{x1, y0, z1, u0, v2}
                    });

                    buildQuad(buf, {0, 0, 1.0f}, {
                        PositionTextureVertex{x1, y0, z1, u4, v2},
                        PositionTextureVertex{x1, y1, z1, u4, v1},
                        PositionTextureVertex{x0, y1, z1, u5, v1},
                        PositionTextureVertex{x0, y0, z1, u5, v2}
                    });

                    buildQuad(buf, {-1.0f, 0, 0}, {
                        PositionTextureVertex{x0, y0, z1, u0, v2},
                        PositionTextureVertex{x0, y1, z1, u0, v1},
                        PositionTextureVertex{x0, y1, z0, u1, v1},
                        PositionTextureVertex{x0, y0, z0, u1, v2}
                    });

                    buildQuad(buf, {0, 1.0f, 0}, {
                        PositionTextureVertex{x0, y1, z0, u1, v1},
                        PositionTextureVertex{x0, y1, z1, u1, v0},
                        PositionTextureVertex{x1, y1, z1, u2, v0},
                        PositionTextureVertex{x1, y1, z0, u2, v1}
                    });

                    buildQuad(buf, {0, -1.0f, 0}, {
                        PositionTextureVertex{x0, y0, z1, u2, v0},
                        PositionTextureVertex{x0, y0, z0, u2, v1},
                        PositionTextureVertex{x1, y0, z0, u3, v1},
                        PositionTextureVertex{x1, y0, z1, u3, v0}
                    });
                } else {
                    const glm::vec3 p0{x0, y0, z0};
                    const glm::vec3 p1{x1, y0, z0};
                    const glm::vec3 p2{x1, y0, z1};
                    const glm::vec3 p3{x0, y0, z1};
                    const glm::vec3 p4{x0, y1, z0};
                    const glm::vec3 p5{x1, y1, z0};
                    const glm::vec3 p6{x1, y1, z1};
                    const glm::vec3 p7{x0, y1, z1};

                    if (auto face = cube.faces.find("south"); face != cube.faces.end()) {
                        auto uv = face->second.uv;
                        auto u = uv.x;
                        auto v = uv.y;

                        buildFace(buf, p0, p4, p5, p1, u, v, u + size.x, v + size.y, tex_width, tex_height, {0, 0, -1.0f});
                    }

                    if (auto face = cube.faces.find("east"); face != cube.faces.end()) {
                        auto uv = face->second.uv;
                        auto u = uv.x;
                        auto v = uv.y;

                        buildFace(buf, p1, p5, p6, p2, u, v, u + size.z, v + size.y, tex_width, tex_height, {1.0f, 0, 0});
                    }

                    if (auto face = cube.faces.find("north"); face != cube.faces.end()) {
                        auto uv = face->second.uv;
                        auto u = uv.x;
                        auto v = uv.y;

                        buildFace(buf, p2, p6, p7, p3, u, v, u + size.x, v + size.y, tex_width, tex_height, {0, 0, 1.0f});
                    }

                    if (auto face = cube.faces.find("west"); face != cube.faces.end()) {
                        auto uv = face->second.uv;
                        auto u = uv.x;
                        auto v = uv.y;

                        buildFace(buf, p3, p7, p4, p0, u, v, u + size.z, v + size.y, tex_width, tex_height, {-1.0f, 0, 0});
                    }

                    if (auto face = cube.faces.find("up"); face != cube.faces.end()) {
                        auto uv = face->second.uv;
                        auto u = uv.x;
                        auto v = uv.y;

                        buildFace(buf, p4, p7, p6, p5, u, v, u + size.x, v + size.z, tex_width, tex_height, {0, 1.0f, 0});
                    }

                    if (auto face = cube.faces.find("down"); face != cube.faces.end()) {
                        auto uv = face->second.uv;
                        auto u = uv.x;
                        auto v = uv.y;

                        buildFace(buf, p3, p0, p1, p2, u, v, u + size.x, v + size.z, tex_width, tex_height, {0, -1.0f, 0});
                    }
                }
            }
        }

        mesh.SetIndices(buf.indices);
        mesh.SetVertices(buf.vertices);
    }

//private:
    ModelMesh mesh{};

    static void buildFace(ModelVertexBuilder& builder, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4, float u0, float v0, float u1, float v1, int texWidth, int texHeight, const glm::vec3& normal) {
        builder.quad();

        builder.vertex(p1.x, p1.y, p1.z, u0 / static_cast<float>(texWidth), v0 / static_cast<float>(texHeight), normal.x, normal.y, normal.z);
        builder.vertex(p2.x, p2.y, p2.z, u0 / static_cast<float>(texWidth), v1 / static_cast<float>(texHeight), normal.x, normal.y, normal.z);
        builder.vertex(p3.x, p3.y, p3.z, u1 / static_cast<float>(texWidth), v1 / static_cast<float>(texHeight), normal.x, normal.y, normal.z);
        builder.vertex(p4.x, p4.y, p4.z, u1 / static_cast<float>(texWidth), v0 / static_cast<float>(texHeight), normal.x, normal.y, normal.z);
    }

    static void buildQuad(ModelVertexBuilder& builder, const glm::vec3& normal, const std::array<PositionTextureVertex, 4>& vertices) {
        builder.quad();
        for (const auto& vertex : vertices) {
            builder.vertex(vertex.x, vertex.y, vertex.z, vertex.u, vertex.v, normal.x, normal.y, normal.z);
        }
    }
};