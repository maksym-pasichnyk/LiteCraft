#pragma once

#include <GL/gl3w.h>
#include <glm/vec2.hpp>

struct RenderTarget {
    glm::ivec2 size;
    GLuint framebuffer;
    GLuint color_attachment;
    GLuint depth_attachment;

    ~RenderTarget() {
        if (color_attachment != 0) {
            glDeleteTextures(1, &color_attachment);
            color_attachment = 0;
        }
        if (depth_attachment != 0) {
            glDeleteRenderbuffers(1, &depth_attachment);
            depth_attachment = 0;
        }
        if (framebuffer != 0) {
            glDeleteFramebuffers(1, &framebuffer);
            depth_attachment = 0;
        }
    }
};
