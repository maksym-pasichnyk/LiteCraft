#pragma once

#include <SFML/Window.hpp>
#include <bitset>

class Input {
public:
    enum class Key {
        None,
        Left,
        Right,
        Up,
        Down,
        Esc,
        Jump
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
        lastFrameKeys = thisFrameKeys;

        thisFrameKeys.set((int) Key::Left,_isKeyPressed(sf::Keyboard::Left) || _isKeyPressed(sf::Keyboard::A));
        thisFrameKeys.set((int) Key::Right,_isKeyPressed(sf::Keyboard::Right) || _isKeyPressed(sf::Keyboard::D));
        thisFrameKeys.set((int) Key::Up,_isKeyPressed(sf::Keyboard::Up) || _isKeyPressed(sf::Keyboard::W));
        thisFrameKeys.set((int) Key::Down,_isKeyPressed(sf::Keyboard::Down) || _isKeyPressed(sf::Keyboard::S));
        thisFrameKeys.set((int) Key::Esc, _isKeyPressed(sf::Keyboard::Escape));
        thisFrameKeys.set((int) Key::Jump, _isKeyPressed(sf::Keyboard::Space));

        lastFrameMouse = thisFrameMouse;
        thisFrameMouse.set((int) MouseButton::Left, _isMouseButtonPressed(sf::Mouse::Left));
        thisFrameMouse.set((int) MouseButton::Right, _isMouseButtonPressed(sf::Mouse::Right));
        thisFrameMouse.set((int) MouseButton::Middle, _isMouseButtonPressed(sf::Mouse::Middle));
    }

private:
    static bool _isKeyPressed(sf::Keyboard::Key key) {
        return sf::Keyboard::isKeyPressed(key);
    }
    static bool _isMouseButtonPressed(sf::Mouse::Button button) {
        return sf::Mouse::isButtonPressed(button);
    }

    std::bitset<5> thisFrameMouse;
    std::bitset<5> lastFrameMouse;

    std::bitset<256> thisFrameKeys;
    std::bitset<256> lastFrameKeys;
};
