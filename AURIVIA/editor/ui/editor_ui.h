#pragma once

#include <string>
#include <functional>
#include <glm/glm.hpp>

namespace Aurivia {

class Engine;

/**
 * @brief Editor UI for AURIVIA game engine
 * Provides visual scene editing, inspector, and game controls
 */
class EditorUI
{
public:
    EditorUI(Engine* engine);
    ~EditorUI();
    
    bool Initialize();
    void Render();
    void Update(float deltaTime);
    void Shutdown();
    
    // UI Panels
    bool IsWindowOpen() const { return m_isRunning; }
    
    // Scene operations
    void SetSelectedObject(uint32_t objectID);
    uint32_t GetSelectedObject() const { return m_selectedObjectID; }

private:
    Engine* m_engine;
    bool m_isRunning;
    bool m_isPlaying;
    bool m_isPaused;
    
    // UI State
    uint32_t m_selectedObjectID;
    float m_frameTime;
    
    // Panel visibility
    bool m_showSceneHierarchy;
    bool m_showInspector;
    bool m_showAssets;
    bool m_showStats;
    bool m_showConsole;
    bool m_showProperties;
    
    // UI Methods
    void DrawMenuBar();
    void DrawSceneHierarchy();
    void DrawInspector();
    void DrawAssets();
    void DrawPlayControls();
    void DrawStatistics();
    void DrawConsole();
    void DrawProperties();
    void DrawViewport();
};

} // namespace Aurivia
