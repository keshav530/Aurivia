#pragma once

namespace Aurivia {

class EditorWindow
{
public:
    EditorWindow();
    ~EditorWindow();
    
    void Initialize();
    void Render();
    void ShowSceneHierarchy();
    void ShowInspector();
    void ShowProperties();
    void ShowPlayControls();

private:
    bool m_showSceneHierarchy;
    bool m_showInspector;
    bool m_showAssets;
    bool m_isPlaying;
};

} // namespace Aurivia
