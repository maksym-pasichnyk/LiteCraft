#pragma once

#include <GL/glew.h>
#include <cstdint>

#include <memory>

class VertexShader {
public:
    explicit VertexShader(GLuint id) : id(id) {}

    ~VertexShader() {
        glDeleteProgram(id);
    }

    auto getNativeHandle() const -> GLuint {
        return id;
    }

private:
    GLuint id = GL_NONE;
};

class PixelShader {
public:
    explicit PixelShader(GLuint id) : id(id) {}

    ~PixelShader() {
        glDeleteProgram(id);
    }

    auto getNativeHandle() const -> GLuint {
        return id;
    }

private:
    GLuint id = GL_NONE;
};

class GraphicsPipeline {
public:
    explicit GraphicsPipeline(GLuint id) : id(id) {}

    ~GraphicsPipeline() {
        glDeleteProgramPipelines(1, &id);
    }

    auto getNativeHandle() const -> GLuint {
        return id;
    }

private:
    GLuint id = GL_NONE;
};

class RenderDevice {
public:
    RenderDevice();

    auto createGraphicsPipeline(VertexShader& vertexShader, PixelShader& pixelShader) -> std::unique_ptr<GraphicsPipeline>;
    auto createVertexShader(const char *source) -> std::unique_ptr<VertexShader>;
    auto createPixelShader(const char *source) -> std::unique_ptr<PixelShader>;
};