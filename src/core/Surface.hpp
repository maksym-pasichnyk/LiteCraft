#pragma once

#include <chrono>
#include <memory>
#include <concepts>

#include <glm/gtc/type_ptr.hpp>
#include <core/FrameInfo.hpp>
#include <core/Viewport.hpp>
#include <core/Device.hpp>
#include <core/Window.hpp>

struct Surface {
    Window& window;
    Device& device;
    glm::ivec2 size{};
    size_t frameIndex = 0;
    std::array<std::unique_ptr<RenderTarget>, 2> frames{};

    Surface(Window& window, Device& device) : window(window), device(device) {
        const auto [width, height] = window.getWindowSize();

        resize(width, height);
    }

    void resize(int width, int height) {
        size = {width, height};

        for (size_t i = 0; i < 2; ++i) {
            if (width > 0 && height > 0) {
                frames[i] = device.createRenderTarget(width, height);
            } else {
                frames[i] = nullptr;
            }
        }
    }

    auto getFramesCount() const -> size_t {
        return frames.size();
    }

    auto getFrameIndex() const -> size_t {
        return frameIndex;
    }

    auto getSize() const -> glm::ivec2 {
        return size;
    }

    auto begin(const glm::vec4& color) -> FrameInfo {
        auto& frame = *frames[frameIndex];
        glBindFramebuffer(GL_FRAMEBUFFER, frame.framebuffer);
        glViewport(0, 0, frame.size.x, frame.size.y);
        glClearNamedFramebufferfv(frame.framebuffer, GL_COLOR, 0, glm::value_ptr(color));
        glClearNamedFramebufferfi(frame.framebuffer, GL_DEPTH_STENCIL, 0, 0, 0);

        return FrameInfo{
            .index = frameIndex
        };
    }

    void present() {
        auto& frame = *frames[frameIndex];

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBlitNamedFramebuffer(frame.framebuffer, 0, 0, 0, frame.size.x, frame.size.y, 0, 0, frame.size.x, frame.size.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

        frameIndex = (frameIndex + 1) % frames.size();
    }
};