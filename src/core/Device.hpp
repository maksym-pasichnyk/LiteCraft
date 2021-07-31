#pragma once

#include <core/RenderTarget.hpp>
#include <core/Window.hpp>
#include <fmt/format.h>
#include <string_view>
#include <string>

struct Device {
    Device(Window& window) {
        gl3wInit();

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(debug, nullptr);
    }

    auto compileShader(std::string_view source, GLenum type) -> GLuint {
        auto data = source.data();
        auto size = GLint(source.size());

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &data, &size);
        glCompileShader(shader);

        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            std::string infoLog{};
            infoLog.resize(length);
            glGetShaderInfoLog(shader, length, &length, infoLog.data());
            fmt::print("{}\n", infoLog);
        }

        GLint status = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    auto createShader(std::string_view vertex_source, std::string_view fragment_source) -> GLuint {
        auto vertex = compileShader(vertex_source, GL_VERTEX_SHADER);
        auto fragment = compileShader(fragment_source, GL_FRAGMENT_SHADER);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            std::string infoLog{};
            infoLog.resize(length);
            glGetProgramInfoLog(program, length, &length, infoLog.data());
            fmt::print("{}\n", infoLog);
        }

        GLint status = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            glDeleteProgram(program);
            return 0;
        }
        return program;
    }

    auto createFramebuffer(GLuint color_attachment, GLuint depth_attachment) -> GLuint {
        GLuint framebuffer;
        glCreateFramebuffers(1, &framebuffer);
        glNamedFramebufferTexture(framebuffer, GL_COLOR_ATTACHMENT0, color_attachment, 0);
        glNamedFramebufferRenderbuffer(framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_attachment);
        return framebuffer;
    }

    auto createColorAttachment(int width, int height) -> GLuint {
        GLuint color_attachment;
        glCreateTextures(GL_TEXTURE_2D, 1, &color_attachment);
        glTextureStorage2D(color_attachment, 1, GL_RGB8, width, height);
        glTextureParameteri(color_attachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(color_attachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        return color_attachment;
    }

    auto createDepthAttachment(int width, int height) -> GLuint {
        GLuint depth_attachment;
        glCreateRenderbuffers(1, &depth_attachment);
        glNamedRenderbufferStorage(depth_attachment, GL_DEPTH32F_STENCIL8, width, height);
        return depth_attachment;
    }

    auto createRenderTarget(int width, int height) -> std::unique_ptr<RenderTarget> {
        const auto color_attachment = createColorAttachment(width, height);
        const auto depth_attachment = createDepthAttachment(width, height);
        const auto framebuffer = createFramebuffer(color_attachment, depth_attachment);

        if (glCheckNamedFramebufferStatus(framebuffer, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            fmt::print("Framebuffer is not complete!: {}\n", glGetError());
        }

        auto renderTarget = std::make_unique<RenderTarget>();
        renderTarget->size = {width, height};
        renderTarget->framebuffer = framebuffer;
        renderTarget->color_attachment = color_attachment;
        renderTarget->depth_attachment = depth_attachment;
        return renderTarget;
    }

private:
    static void debug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param) {
        const auto source_str = [source]() -> std::string_view {
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

        const auto type_str = [type]() -> std::string_view {
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

        const auto severity_str = [severity]() -> std::string_view {
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
};
