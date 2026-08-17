#include "editor_window.h"
#include "aurivia/logger.h"

namespace Aurivia {

EditorWindow::EditorWindow()
    : m_showSceneHierarchy(true), m_showInspector(true), m_showAssets(true), m_isPlaying(false)
{
}

EditorWindow::~EditorWindow()
{
}

void EditorWindow::Initialize()
{
    AV_LOG_INFO("Initializing Editor Window");
}

void EditorWindow::Render()
{
    // ImGui rendering will go here
    ShowPlayControls();
    ShowSceneHierarchy();
    ShowInspector();
}

void EditorWindow::ShowSceneHierarchy()
{
    // Scene hierarchy panel
}

void EditorWindow::ShowInspector()
{
    // Inspector panel
}

void EditorWindow::ShowProperties()
{
    // Properties panel
}

void EditorWindow::ShowPlayControls()
{
    // Play/Pause/Stop controls
}

} // namespace Aurivia
