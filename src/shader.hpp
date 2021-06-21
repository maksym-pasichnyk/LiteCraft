#pragma once

#include <string>
#include <fstream>
#include <sstream>

struct Shader {
    static std::string source(const std::string &path) {
        std::ifstream file(path, std::ios::in);
        std::stringstream stream{};
        stream << file.rdbuf();
        file.close();
        return stream.str();
    }

    static bool validate(const GLuint program) {
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            std::basic_string<GLchar> infoLog{};
            infoLog.resize(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            fmt::print("{}\n", infoLog);
            return false;
        }
        return true;
    }

    static GLuint compile(const std::string &source, GLenum type) {
        auto data = source.data();
        auto size = GLint(source.size());

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &data, &size);
        glCompileShader(shader);

        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            std::basic_string<GLchar> infoLog{};
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

    static GLuint create(const std::string &vertex_path, const std::string &fragment_path) {
        auto vertex = compile(source(vertex_path), GL_VERTEX_SHADER);
        auto fragment = compile(source(fragment_path), GL_FRAGMENT_SHADER);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);

        glLinkProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            std::basic_string<GLchar> infoLog{};
            infoLog.resize(length);
            glGetProgramInfoLog(program, length, &length, &infoLog[0]);
            fmt::print("{}\n", infoLog);
        }

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            glDeleteProgram(program);
            return 0;
        }
        return program;
    }
};
