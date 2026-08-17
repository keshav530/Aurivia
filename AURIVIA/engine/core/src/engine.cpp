#include "aurivia/engine.h"
#include "aurivia/window.h"
#include "aurivia/renderer.h"
#include "aurivia/input_manager.h"
#include "aurivia/audio_system.h"
#include "aurivia/logger.h"
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Aurivia {

Engine::Engine(const std::string& title, uint32_t width, uint32_t height)
    : m_windowTitle(title), m_windowWidth(width), m_windowHeight(height),
      m_isRunning(false), m_isPaused(false), 
      m_deltaTime(0.0f), m_frameTime(0.0f), m_frameCount(0)
{
    Logger::Info("AURIVIA Engine v0.1.0 initialized");
}

Engine::~Engine()
{
    Shutdown();
}

bool Engine::Initialize()
{
    AV_LOG_INFO("Initializing AURIVIA Engine...");
    
    // Create subsystems
    m_window = std::make_unique<Window>(m_windowTitle, m_windowWidth, m_windowHeight);
    m_renderer = std::make_unique<Renderer>(m_windowWidth, m_windowHeight);
    m_inputManager = std::make_unique<InputManager>();
    m_audioSystem = std::make_unique<AudioSystem>();
    
    // Initialize window
    if (!m_window->Initialize())
    {
        AV_LOG_ERROR("Failed to initialize window");
        return false;
    }
    AV_LOG_INFO("Window initialized: " + std::to_string(m_windowWidth) + "x" + std::to_string(m_windowHeight));
    
    // Initialize renderer
    if (!m_renderer->Initialize())
    {
        AV_LOG_ERROR("Failed to initialize renderer");
        return false;
    }
    AV_LOG_INFO("Renderer initialized");
    
    // Initialize audio system
    if (!m_audioSystem->Initialize())
    {
        AV_LOG_WARN("Failed to initialize audio system (non-critical)");
    }
    AV_LOG_INFO("Audio system initialized");
    
    m_isRunning = true;
    return true;
}

void Engine::Update(float deltaTime)
{
    m_deltaTime = deltaTime;
    m_frameCount++;
    
    // Update input
    m_inputManager->Update();
    
    // Check window close
    if (m_window->ShouldClose())
    {
        m_isRunning = false;
    }
}

void Engine::Render()
{
    m_renderer->Clear();
    m_renderer->BeginFrame();
    
    // Setup camera
    glm::mat4 view = glm::lookAt(
        glm::vec3(3.0f, 3.0f, 3.0f),  // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f),  // Look at
        glm::vec3(0.0f, 1.0f, 0.0f)   // Up vector
    );
    
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        m_renderer->GetWidth() / static_cast<float>(m_renderer->GetHeight()),
        0.1f,
        100.0f
    );
    
    m_renderer->SetViewMatrix(view);
    m_renderer->SetProjectionMatrix(projection);
    
    // Render a test cube
    m_renderer->DrawCube(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.2f, 0.5f, 1.0f));
    
    m_renderer->EndFrame();
    m_window->SwapBuffers();
}

void Engine::Shutdown()
{
    AV_LOG_INFO("Shutting down AURIVIA Engine...");
    
    if (m_audioSystem)
        m_audioSystem->Shutdown();
    
    if (m_window)
        m_window->Shutdown();
    
    m_isRunning = false;
    AV_LOG_INFO("Engine shutdown complete");
}

bool Engine::IsRunning() const
{
    return m_isRunning;
}

int Engine::Run()
{
    if (!Initialize())
    {
        AV_LOG_ERROR("Failed to initialize engine");
        return -1;
    }
    
    auto lastTime = std::chrono::high_resolution_clock::now();
    
    while (IsRunning())
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        Update(deltaTime);
        Render();
        m_frameTime = deltaTime;
        
        if (m_frameCount % 60 == 0)
        {
            AV_LOG_DEBUG("FPS: " + std::to_string(static_cast<int>(1.0f / deltaTime)));
        }
    }
    
    Shutdown();
    return 0;
}

} // namespace Aurivia
