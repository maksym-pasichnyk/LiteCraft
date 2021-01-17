#include "graphics.hpp"

#include "fmt/format.h"

namespace {
    void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const *message, void const *user_param) {
        auto source_str = [source]() -> std::string_view {
            switch (source) {
                case GL_DEBUG_SOURCE_API:
                    return "API";
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                    return "WINDOW SYSTEM";
                case GL_DEBUG_SOURCE_SHADER_COMPILER:
                    return "SHADER COMPILER";
                case GL_DEBUG_SOURCE_THIRD_PARTY:
                    return "THIRD PARTY";
                case GL_DEBUG_SOURCE_APPLICATION:
                    return "APPLICATION";
                case GL_DEBUG_SOURCE_OTHER:
                    return "OTHER";
                default:
                    return "UNKNOWN";
            }
        }();

        auto type_str = [type]() -> std::string_view {
            switch (type) {
                case GL_DEBUG_TYPE_ERROR:
                    return "ERROR";
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                    return "DEPRECATED_BEHAVIOR";
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                    return "UNDEFINED_BEHAVIOR";
                case GL_DEBUG_TYPE_PORTABILITY:
                    return "PORTABILITY";
                case GL_DEBUG_TYPE_PERFORMANCE:
                    return "PERFORMANCE";
                case GL_DEBUG_TYPE_MARKER:
                    return "MARKER";
                case GL_DEBUG_TYPE_OTHER:
                    return "OTHER";
                default:
                    return "UNKNOWN";
            }
        }();

        auto severity_str = [severity]() -> std::string_view {
            switch (severity) {
                case GL_DEBUG_SEVERITY_NOTIFICATION:
                    return "NOTIFICATION";
                case GL_DEBUG_SEVERITY_LOW:
                    return "LOW";
                case GL_DEBUG_SEVERITY_MEDIUM:
                    return "MEDIUM";
                case GL_DEBUG_SEVERITY_HIGH:
                    return "HIGH";
                default:
                    return "UNKNOWN";
            }
        }();

        fmt::print("{}, {}, {}, {}: {}\n", source_str, type_str, severity_str, id, message);
    }

    auto validateShader(const GLuint program) -> bool {
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            fmt::print("error: {}", infoLog.data());
            return false;
        }
        return true;
    }

    auto createShader(GLint type, const char *source) -> GLuint {
        const auto id = glCreateShaderProgramv(type, 1, &source);
        if (validateShader(id)) {
            return id;
        }
        glDeleteProgram(id);
        return GL_NONE;
    }

    auto createPipeline() -> GLuint {
        GLuint id;
        glGenProgramPipelines(1, &id);
        return id;
    }
}
auto RenderDevice::createGraphicsPipeline(VertexShader& vertexShader, PixelShader& pixelShader) -> std::unique_ptr<GraphicsPipeline> {
    const auto id = createPipeline();
    glBindProgramPipeline(id);

    glUseProgramStages(id, GL_VERTEX_SHADER_BIT, static_cast<GLuint>(vertexShader.getNativeHandle()));
    glUseProgramStages(id, GL_FRAGMENT_SHADER_BIT, static_cast<GLuint>(pixelShader.getNativeHandle()));

    return std::make_unique<GraphicsPipeline>(id);
}

auto RenderDevice::createVertexShader(const char *source) -> std::unique_ptr<VertexShader> {
    return std::make_unique<VertexShader>(createShader(GL_VERTEX_SHADER, source));
}

auto RenderDevice::createPixelShader(const char *source) -> std::unique_ptr<PixelShader> {
    return std::make_unique<PixelShader>(createShader(GL_FRAGMENT_SHADER, source));
}

RenderDevice::RenderDevice() {
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallback, nullptr);
}