#pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <span>
#include <vector>

#include <stdint.hpp>

struct Vertex {
    glm::vec3 point;
    glm::vec2 tex;
    glm::u8vec4 color;

    static auto from(glm::vec3 point, glm::vec2 tex, glm::u8vec4 color) -> Vertex {
        return {point, tex, color};
    }
};

struct VertexBuilder {
    std::vector<Vertex> vertices;
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

    void vertex(f32 x, f32 y, f32 z, f32 u, f32 v, uint8 r, uint8 g, uint8 b, uint8 light) {
        vertices.push_back(Vertex{
                .point{x, y, z},
                .tex{u, v},
                .color{r, g, b, light}
        });
    }
};

struct Mesh {
    GLuint vao = GL_NONE;
    GLuint vbo = GL_NONE;
    GLuint ibo = GL_NONE;
    GLsizeiptr vbo_size{0};
    GLsizeiptr ibo_size{0};
    int index_count{0};
    int vertex_count{0};

    Mesh() {
        glCreateVertexArrays(1, &vao);
        glCreateBuffers(1, &vbo);
        glCreateBuffers(1, &ibo);

        glVertexArrayElementBuffer(vao, ibo);
        glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));

        glEnableVertexArrayAttrib(vao, 0);
        glEnableVertexArrayAttrib(vao, 1);
        glEnableVertexArrayAttrib(vao, 2);

        glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, point));
        glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, tex));
        glVertexArrayAttribFormat(vao, 2, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, color));

        glVertexArrayAttribBinding(vao, 0, 0);
        glVertexArrayAttribBinding(vao, 1, 0);
        glVertexArrayAttribBinding(vao, 2, 0);
    }

    ~Mesh() {
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void SetVertices(std::span<const Vertex> vertices) {
        vertex_count = vertices.size();
        if (vertices.size_bytes() > vbo_size) {
            vbo_size = vertices.size_bytes();
            glNamedBufferData(vbo, vertices.size_bytes(), vertices.data(), GL_DYNAMIC_DRAW);
        } else {
            glNamedBufferSubData(vbo, 0, vertices.size_bytes(), vertices.data());
        }
    }

    void SetIndicesCount(int32 count) {
    	GLsizeiptr buf_size = sizeof(int32) * count;

        index_count = count;
    	if (buf_size > ibo_size) {
            ibo_size = buf_size;
            glNamedBufferData(ibo, buf_size, nullptr, GL_DYNAMIC_DRAW);
        }
    }

    void SetIndicesData(std::span<const int32> indices, int32 offset) {
		glNamedBufferSubData(ibo, offset * sizeof(int32), indices.size_bytes(), indices.data());
    }

    void SetIndices(std::span<const int32> indices) {
        index_count = indices.size();
        if (indices.size_bytes() > ibo_size) {
            ibo_size = indices.size_bytes();
            glNamedBufferData(ibo, indices.size_bytes(), indices.data(), GL_DYNAMIC_DRAW);
        } else {
            glNamedBufferSubData(ibo, 0, indices.size_bytes(), indices.data());
        }
    }
};
