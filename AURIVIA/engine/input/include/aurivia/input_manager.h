#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Aurivia {

enum class KeyCode
{
    // Letter keys
    A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    
    // Number keys
    Num0 = 48, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    
    // Special keys
    Escape = 256,
    Enter = 257,
    Tab = 258,
    Backspace = 259,
    Insert = 260,
    Delete = 261,
    Right = 262,
    Left = 263,
    Down = 264,
    Up = 265,
    Space = 32,
    LeftShift = 340,
    LeftControl = 341,
    LeftAlt = 342,
    RightShift = 344,
    RightControl = 345,
    RightAlt = 346,
};

enum class MouseButton
{
    Left = 0,
    Right = 1,
    Middle = 2
};

/**
 * @brief Input management system
 */
class InputManager
{
public:
    InputManager();
    ~InputManager();
    
    void Update();
    
    // Keyboard input
    bool IsKeyPressed(KeyCode key) const;
    bool IsKeyDown(KeyCode key) const;
    bool IsKeyReleased(KeyCode key) const;
    
    // Mouse input
    bool IsMouseButtonPressed(MouseButton button) const;
    bool IsMouseButtonDown(MouseButton button) const;
    bool IsMouseButtonReleased(MouseButton button) const;
    
    glm::vec2 GetMousePosition() const;
    glm::vec2 GetMouseDelta() const;
    float GetMouseScroll() const;
    
    // Gamepad support (future)
    // bool IsGamepadButtonPressed(int gamepad, GamepadButton button);
    // float GetGamepadAxis(int gamepad, GamepadAxis axis);

private:
    // Key states
    std::vector<bool> m_keyPressed;
    std::vector<bool> m_keyDown;
    std::vector<bool> m_keyReleased;
    
    // Mouse states
    std::vector<bool> m_mouseButtonPressed;
    std::vector<bool> m_mouseButtonDown;
    std::vector<bool> m_mouseButtonReleased;
    
    glm::vec2 m_mousePosition;
    glm::vec2 m_mouseDelta;
    float m_mouseScroll;
};

} // namespace Aurivia
