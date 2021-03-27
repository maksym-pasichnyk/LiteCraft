#pragma once

#include <bitset>
#include <SDL2/SDL.h>

class Input {
public:
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

    bool IsMouseButtonPressed(MouseButton button) {
        return thisFrameMouse.test((int)button);
    }
    bool IsMouseButtonDown(MouseButton button) {
        bool lastFrame = lastFrameMouse.test((int)button);
        bool thisFrame = thisFrameMouse.test((int)button);
        return thisFrame && !lastFrame;
    }
    bool IsMouseButtonUp(MouseButton button) {
        bool lastFrame = lastFrameMouse.test((int)button);
        bool thisFrame = thisFrameMouse.test((int)button);
        return !thisFrame && lastFrame;
    }

    bool IsKeyPressed(Key keycode) {
        return thisFrameKeys.test((int)keycode);
    }
    bool IsKeyDown(Key keycode) {
        bool lastFrame = lastFrameKeys.test((int)keycode);
        bool thisFrame = thisFrameKeys.test((int)keycode);
        return thisFrame && !lastFrame;
    }
    bool IsKeyUp(Key keycode) {
        bool lastFrame = lastFrameKeys.test((int)keycode);
        bool thisFrame = thisFrameKeys.test((int)keycode);
        return !thisFrame && lastFrame;
    }

    void update() {
        const auto keys = SDL_GetKeyboardState(nullptr);

        lastFrameKeys = thisFrameKeys;
        thisFrameKeys.set((int) Key::Left, keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]);
        thisFrameKeys.set((int) Key::Right, keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]);
        thisFrameKeys.set((int) Key::Up, keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]);
        thisFrameKeys.set((int) Key::Down, keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]);
        thisFrameKeys.set((int) Key::Esc, keys[SDL_SCANCODE_ESCAPE]);
        thisFrameKeys.set((int) Key::Jump, keys[SDL_SCANCODE_SPACE]);
        thisFrameKeys.set((int) Key::Shift, keys[SDL_SCANCODE_LSHIFT]);
        thisFrameKeys.set((int) Key::X, keys[SDL_SCANCODE_X]);

        const auto mouse = SDL_GetMouseState(nullptr, nullptr);

        lastFrameMouse = thisFrameMouse;
        thisFrameMouse.set((int) MouseButton::Left, (mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0);
        thisFrameMouse.set((int) MouseButton::Right, (mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0);
        thisFrameMouse.set((int) MouseButton::Middle, (mouse & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
    }
private:
    std::bitset<5> thisFrameMouse;
    std::bitset<5> lastFrameMouse;

    std::bitset<256> thisFrameKeys;
    std::bitset<256> lastFrameKeys;
};
