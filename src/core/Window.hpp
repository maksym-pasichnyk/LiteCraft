#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <optional>
#include <queue>

struct Window {
    Window(const char* title, int width, int height) : _size(width, height) {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(_window);
        glfwSwapInterval(1);

        glfwSetWindowUserPointer(_window, this);

        glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
//            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            self->pushEvent(KeyEvent{key, scancode, action, mods});
        });

        glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
//            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            self->pushEvent(MouseMoveEvent{xpos, ypos});
        });

        glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
//            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            self->pushEvent(MouseButtonEvent{button, action, mods});
        });

        glfwSetWindowFocusCallback(_window, [](GLFWwindow* window, int focused) {
//            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            self->pushEvent(FocusEvent{focused == 1});
        });

        glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
//            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            self->_size = {width, height};
//            self->pushEvent(WindowResizeEvent{width, height});
        });

        glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
//            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            self->_size = {width, height};
//            self->pushEvent(FramebufferResizeEvent{width, height});
        });

        glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
//            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
//            self->pushEvent(WindowCloseEvent{});
        });
    }

    ~Window() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void setMousePosition(const glm::ivec2& pos) {
        glfwSetCursorPos(_window, static_cast<double>(pos.x), static_cast<double>(pos.y));
    }

    glm::ivec2 getWindowSize() const {
        return _size;
    }

    glm::ivec2 getFramebufferSize() const {
        glm::ivec2 size{};
        glfwGetFramebufferSize(_window, &size.x, &size.y);
        return size;
    }

    bool shouldClose() const {
        return glfwWindowShouldClose(_window);
    }

//    void pushEvent(const Event& event) {
//        _events.push(event);
//    }

    void swapBuffers() {
        glfwSwapBuffers(_window);
    }

    void pumpEvents() {
        glfwPollEvents();
//        _frameEvents = std::exchange(_events, std::queue<Event>{});
    }

//    std::optional<Event> pollEvent() {
//        if (_frameEvents.empty()) {
//            return std::nullopt;
//        }
//        auto event = _frameEvents.front();
//        return _frameEvents.pop(), event;
//    }

private:
    GLFWwindow* _window;
    glm::ivec2 _size;
//    std::queue<Event> _events{};
//    std::queue<Event> _frameEvents{};
};