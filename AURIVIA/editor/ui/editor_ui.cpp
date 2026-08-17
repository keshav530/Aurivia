#include "editor_ui.h"
#include "aurivia/engine.h"
#include "aurivia/logger.h"
#include <iostream>

namespace Aurivia {

EditorUI::EditorUI(Engine* engine)
    : m_engine(engine), m_isRunning(true), m_isPlaying(false), m_isPaused(false),
      m_selectedObjectID(0), m_frameTime(0.0f),
      m_showSceneHierarchy(true), m_showInspector(true), m_showAssets(true),
      m_showStats(true), m_showConsole(true), m_showProperties(true)
{
}

EditorUI::~EditorUI()
{
    Shutdown();
}

bool EditorUI::Initialize()
{
    AV_LOG_INFO("Initializing Editor UI");
    
    // ImGui initialization would go here
    // For now, this is a stub implementation
    
    return true;
}

void EditorUI::Render()
{
    // ImGui rendering would happen here
    DrawMenuBar();
    DrawSceneHierarchy();
    DrawInspector();
    DrawPlayControls();
    DrawStatistics();
}

void EditorUI::Update(float deltaTime)
{
    m_frameTime = deltaTime;
}

void EditorUI::Shutdown()
{
    AV_LOG_INFO("Shutting down Editor UI");
}

void EditorUI::SetSelectedObject(uint32_t objectID)
{
    m_selectedObjectID = objectID;
    AV_LOG_DEBUG("Selected object: " + std::to_string(objectID));
}

void EditorUI::DrawMenuBar()
{
    // File menu
    // Edit menu
    // View menu
    // Assets menu
    // Help menu
    std::cout << "[Menu Bar] File | Edit | View | Assets | Help\n";
}

void EditorUI::DrawSceneHierarchy()
{
    if (!m_showSceneHierarchy)
        return;
    
    std::cout << "[Scene Hierarchy]\n";
    std::cout << "  - Cube (Selected)\n";
    std::cout << "  - Light\n";
    std::cout << "  - Camera\n";
}

void EditorUI::DrawInspector()
{
    if (!m_showInspector)
        return;
    
    std::cout << "[Inspector]\n";
    if (m_selectedObjectID > 0)
    {
        std::cout << "  Object ID: " << m_selectedObjectID << "\n";
        std::cout << "  Transform: Position (0, 0, 0)\n";
        std::cout << "  Rotation: (0, 0, 0)\n";
        std::cout << "  Scale: (1, 1, 1)\n";
    }
}

void EditorUI::DrawAssets()
{
    if (!m_showAssets)
        return;
    
    std::cout << "[Assets Panel]\n";
    std::cout << "  - Models/\n";
    std::cout << "  - Textures/\n";
    std::cout << "  - Scripts/\n";
}

void EditorUI::DrawPlayControls()
{
    std::cout << "[";
    if (m_isPlaying)
        std::cout << "PLAYING";
    else if (m_isPaused)
        std::cout << "PAUSED";
    else
        std::cout << "STOPPED";
    std::cout << "] Play | Pause | Stop\n";
}

void EditorUI::DrawStatistics()
{
    if (!m_showStats)
        return;
    
    std::cout << "[Statistics]\n";
    std::cout << "  Frame Time: " << (m_frameTime * 1000.0f) << " ms\n";
    std::cout << "  FPS: " << (m_frameTime > 0 ? 1.0f / m_frameTime : 0) << "\n";
    std::cout << "  Memory: 256 MB\n";
}

void EditorUI::DrawConsole()
{
    if (!m_showConsole)
        return;
    
    std::cout << "[Console]\n";
}

void EditorUI::DrawProperties()
{
    if (!m_showProperties)
        return;
    
    std::cout << "[Properties]\n";
}

void EditorUI::DrawViewport()
{
    // The main 3D viewport is rendered by the engine
    // This just shows the UI overlay
    std::cout << "[3D Viewport - Rendering here]\n";
}

} // namespace Aurivia
