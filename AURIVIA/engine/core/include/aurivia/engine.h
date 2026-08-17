#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace Aurivia {

class Window;
class Renderer;
class InputManager;
class AudioSystem;

/**
 * @brief Main game engine class
 * Manages the game loop, subsystems, and lifecycle
 */
class Engine
{
public:
    Engine(const std::string& title, uint32_t width, uint32_t height);
    ~Engine();
    
    // Lifecycle
    bool Initialize();
    void Update(float deltaTime);
    void Render();
    void Shutdown();
    
    // Query
    bool IsRunning() const;
    float GetDeltaTime() const { return m_deltaTime; }
    float GetFrameTime() const { return m_frameTime; }
    
    // Subsystem access
    Window* GetWindow() { return m_window.get(); }
    Renderer* GetRenderer() { return m_renderer.get(); }
    InputManager* GetInputManager() { return m_inputManager.get(); }
    AudioSystem* GetAudioSystem() { return m_audioSystem.get(); }
    
    // Main loop
    int Run();

private:
    // Subsystems
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<InputManager> m_inputManager;
    std::unique_ptr<AudioSystem> m_audioSystem;
    
    // Engine state
    bool m_isRunning;
    bool m_isPaused;
    
    // Timing
    float m_deltaTime;
    float m_frameTime;
    uint32_t m_frameCount;
    
    // Configuration
    std::string m_windowTitle;
    uint32_t m_windowWidth;
    uint32_t m_windowHeight;
};

} // namespace Aurivia
