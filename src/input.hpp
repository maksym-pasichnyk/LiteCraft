#pragma once

#include <bitset>
//#include <SDL2/SDL.h>

struct Input {
    enum class Key {
        None,
        Left,
        Right,
        Up,
        Down,
        Esc,
        Jump,
        Shift,

        X
    };

    enum class MouseButton {
        Left,
        Right,
        Middle,
    };

    auto isMouseButtonPressed(MouseButton button) const -> bool {
        return thisFrameMouse.test(static_cast<int>(button));
    }
    auto isMouseButtonDown(MouseButton button) const -> bool {
        const bool lastFrame = lastFrameMouse.test(static_cast<int>(button));
        const bool thisFrame = thisFrameMouse.test(static_cast<int>(button));
        return thisFrame && !lastFrame;
    }
    auto isMouseButtonUp(MouseButton button) const -> bool {
        const bool lastFrame = lastFrameMouse.test(static_cast<int>(button));
        const bool thisFrame = thisFrameMouse.test(static_cast<int>(button));
        return !thisFrame && lastFrame;
    }
    auto isKeyPressed(Key keycode) const -> bool {
        return thisFrameKeys.test(static_cast<int>(keycode));
    }
    auto isKeyDown(Key keycode) const -> bool {
        const bool lastFrame = lastFrameKeys.test(static_cast<int>(keycode));
        const bool thisFrame = thisFrameKeys.test(static_cast<int>(keycode));
        return thisFrame && !lastFrame;
    }
    auto isKeyUp(Key keycode) const -> bool {
        const bool lastFrame = lastFrameKeys.test(static_cast<int>(keycode));
        const bool thisFrame = thisFrameKeys.test(static_cast<int>(keycode));
        return !thisFrame && lastFrame;
    }
    auto getMousePosition() const -> glm::ivec2 {
        return mousePosition;
    }

    void update() {
        auto window = glfwGetCurrentContext();

        glm::dvec2 pos{};
        glfwGetCursorPos(window, &pos.x, &pos.y);

        mousePosition = glm::ivec2(pos);

        lastFrameKeys = thisFrameKeys;
        thisFrameKeys.set(static_cast<int>(Key::Left), glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
        thisFrameKeys.set(static_cast<int>(Key::Right), glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
        thisFrameKeys.set(static_cast<int>(Key::Up), glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
        thisFrameKeys.set(static_cast<int>(Key::Down), glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);
        thisFrameKeys.set(static_cast<int>(Key::Esc), glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
        thisFrameKeys.set(static_cast<int>(Key::Jump), glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
        thisFrameKeys.set(static_cast<int>(Key::Shift), glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
        thisFrameKeys.set(static_cast<int>(Key::X), glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS);

        lastFrameMouse = thisFrameMouse;
        thisFrameMouse.set(static_cast<int>(MouseButton::Left), glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
        thisFrameMouse.set(static_cast<int>(MouseButton::Right), glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
        thisFrameMouse.set(static_cast<int>(MouseButton::Middle), glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
    }

    static auto get() -> Input& {
        static Input instance;
        return instance;
    }

private:
    glm::ivec2 mousePosition{};
    std::bitset<5> thisFrameMouse{};
    std::bitset<5> lastFrameMouse{};
    std::bitset<256> thisFrameKeys{};
    std::bitset<256> lastFrameKeys{};
};
