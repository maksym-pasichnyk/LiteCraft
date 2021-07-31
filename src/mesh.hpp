#pragma once

#include <span>
#include <vector>
#include <GL/gl3w.h>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Vertex {
    glm::vec3 pos;
    glm::vec2 tex;
    glm::u8vec4 color;
    glm::u8vec4 light;
};

struct VertexArrayAttrib {
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLuint offset;
};

struct VertexArrayBinding {
    GLuint index;
    GLuint binding;
};

struct Submesh {
    glm::i32 index_offset = 0;
    glm::i32 index_count = 0;
};

struct Mesh {
    GLuint vao = GL_NONE;
    GLuint vbo = GL_NONE;
    GLuint ibo = GL_NONE;
    GLsizeiptr vbo_size{0};
    GLsizeiptr ibo_size{0};
    int index_count{0};
    int vertex_count{0};
    GLenum usage;

    Mesh(std::span<const VertexArrayAttrib> attributes, std::span<const VertexArrayBinding> bindings, GLsizei size, GLenum usage) : usage(usage) {
        glCreateVertexArrays(1, &vao);
        glCreateBuffers(1, &vbo);
        glCreateBuffers(1, &ibo);

        glVertexArrayElementBuffer(vao, ibo);
        glVertexArrayVertexBuffer(vao, 0, vbo, 0, size);

        for (const auto& attrib : attributes) {
            glEnableVertexArrayAttrib(vao, attrib.index);
            glVertexArrayAttribFormat(vao, attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.offset);
        }

        for (const auto& binding : bindings) {
            glVertexArrayAttribBinding(vao, binding.index, binding.binding);
        }
    }

    ~Mesh() {
        glDeleteBuffers(1, &ibo);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    template<typename _Type, size_t _Extent = std::dynamic_extent>
    void SetVertices(std::span<_Type, _Extent> vertices) {
        vertex_count = vertices.size();
        if (vertices.size_bytes() > vbo_size) {
            vbo_size = vertices.size_bytes();
            glNamedBufferData(vbo, vertices.size_bytes(), vertices.data(), usage);
        } else {
            glNamedBufferSubData(vbo, 0, vertices.size_bytes(), vertices.data());
        }
    }

    void SetIndicesCount(int32_t count) {
    	const GLsizeiptr buf_size = sizeof(int32_t) * count;

        index_count = count;
    	if (buf_size > ibo_size) {
            ibo_size = buf_size;
            glNamedBufferData(ibo, buf_size, nullptr, usage);
        }
    }

    void SetIndicesData(std::span<const int32_t> indices, int32_t offset) {
		glNamedBufferSubData(ibo, offset * sizeof(int32_t), indices.size_bytes(), indices.data());
    }

    void SetIndices(std::span<const int32_t> indices) {
        index_count = indices.size();
        if (indices.size_bytes() > ibo_size) {
            ibo_size = indices.size_bytes();
            glNamedBufferData(ibo, indices.size_bytes(), indices.data(), usage);
        } else {
            glNamedBufferSubData(ibo, 0, indices.size_bytes(), indices.data());
        }
    }
};
