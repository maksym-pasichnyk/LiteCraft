#pragma once

#include <bitset>
#include <SDL2/SDL.h>

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

    bool isMouseButtonPressed(MouseButton button) const {
        return thisFrameMouse.test(static_cast<int>(button));
    }
    bool isMouseButtonDown(MouseButton button) const {
        const bool lastFrame = lastFrameMouse.test(static_cast<int>(button));
        const bool thisFrame = thisFrameMouse.test(static_cast<int>(button));
        return thisFrame && !lastFrame;
    }
    bool isMouseButtonUp(MouseButton button) const {
        const bool lastFrame = lastFrameMouse.test(static_cast<int>(button));
        const bool thisFrame = thisFrameMouse.test(static_cast<int>(button));
        return !thisFrame && lastFrame;
    }
    bool isKeyPressed(Key keycode) const {
        return thisFrameKeys.test(static_cast<int>(keycode));
    }
    bool isKeyDown(Key keycode) const {
        const bool lastFrame = lastFrameKeys.test(static_cast<int>(keycode));
        const bool thisFrame = thisFrameKeys.test(static_cast<int>(keycode));
        return thisFrame && !lastFrame;
    }
    bool isKeyUp(Key keycode) const {
        const bool lastFrame = lastFrameKeys.test(static_cast<int>(keycode));
        const bool thisFrame = thisFrameKeys.test(static_cast<int>(keycode));
        return !thisFrame && lastFrame;
    }
    glm::ivec2 getMousePosition() const {
        return mousePosition;
    }

    void update() {
        const auto keys = SDL_GetKeyboardState(nullptr);

        lastFrameKeys = thisFrameKeys;
        thisFrameKeys.set(static_cast<int>(Key::Left), keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]);
        thisFrameKeys.set(static_cast<int>(Key::Right), keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]);
        thisFrameKeys.set(static_cast<int>(Key::Up), keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]);
        thisFrameKeys.set(static_cast<int>(Key::Down), keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]);
        thisFrameKeys.set(static_cast<int>(Key::Esc), keys[SDL_SCANCODE_ESCAPE]);
        thisFrameKeys.set(static_cast<int>(Key::Jump), keys[SDL_SCANCODE_SPACE]);
        thisFrameKeys.set(static_cast<int>(Key::Shift), keys[SDL_SCANCODE_LSHIFT]);
        thisFrameKeys.set(static_cast<int>(Key::X), keys[SDL_SCANCODE_X]);

        const auto mouse = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        lastFrameMouse = thisFrameMouse;
        thisFrameMouse.set(static_cast<int>(MouseButton::Left), (mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0);
        thisFrameMouse.set(static_cast<int>(MouseButton::Right), (mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0);
        thisFrameMouse.set(static_cast<int>(MouseButton::Middle), (mouse & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
    }

private:
    glm::ivec2 mousePosition{};
    std::bitset<5> thisFrameMouse{};
    std::bitset<5> lastFrameMouse{};
    std::bitset<256> thisFrameKeys{};
    std::bitset<256> lastFrameKeys{};
};
