#include "aurivia/input_manager.h"
#include <GLFW/glfw3.h>

namespace Aurivia {

InputManager::InputManager()
    : m_keyPressed(512, false), m_keyDown(512, false), m_keyReleased(512, false),
      m_mouseButtonPressed(3, false), m_mouseButtonDown(3, false), m_mouseButtonReleased(3, false),
      m_mousePosition(0.0f), m_mouseDelta(0.0f), m_mouseScroll(0.0f)
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
    // Call GLFW to poll events
    glfwPollEvents();
    
    // Reset state was in previous frame
    for (auto& key : m_keyReleased)
        key = false;
    
    for (auto& btn : m_mouseButtonReleased)
        btn = false;
    
    m_mouseScroll = 0.0f;
    
    // Update mouse position
    double xpos, ypos;
    // glfwGetCursorPos would go here to update m_mousePosition and m_mouseDelta
}

bool InputManager::IsKeyPressed(KeyCode key) const
{
    return m_keyPressed[static_cast<int>(key)];
}

bool InputManager::IsKeyDown(KeyCode key) const
{
    return m_keyDown[static_cast<int>(key)];
}

bool InputManager::IsKeyReleased(KeyCode key) const
{
    return m_keyReleased[static_cast<int>(key)];
}

bool InputManager::IsMouseButtonPressed(MouseButton button) const
{
    return m_mouseButtonPressed[static_cast<int>(button)];
}

bool InputManager::IsMouseButtonDown(MouseButton button) const
{
    return m_mouseButtonDown[static_cast<int>(button)];
}

bool InputManager::IsMouseButtonReleased(MouseButton button) const
{
    return m_mouseButtonReleased[static_cast<int>(button)];
}

glm::vec2 InputManager::GetMousePosition() const
{
    return m_mousePosition;
}

glm::vec2 InputManager::GetMouseDelta() const
{
    return m_mouseDelta;
}

float InputManager::GetMouseScroll() const
{
    return m_mouseScroll;
}

} // namespace Aurivia
