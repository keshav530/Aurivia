#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

namespace Aurivia {

/**
 * @brief Window management and rendering surface
 */
class Window
{
public:
    Window(const std::string& title, uint32_t width, uint32_t height);
    ~Window();
    
    bool Initialize();
    void Shutdown();
    
    // Window operations
    void Clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.0f);
    void SwapBuffers();
    bool ShouldClose() const;
    void SetShouldClose(bool value);
    
    // Getters
    GLFWwindow* GetNativeWindow() const { return m_window; }
    uint32_t GetWidth() const { return m_width; }
    uint32_t GetHeight() const { return m_height; }
    float GetAspectRatio() const { return static_cast<float>(m_width) / static_cast<float>(m_height); }
    
    // Event callbacks
    void SetFramebufferSizeCallback(void (*callback)(GLFWwindow*, int, int));

private:
    GLFWwindow* m_window;
    std::string m_title;
    uint32_t m_width;
    uint32_t m_height;
    bool m_isInitialized;
};

} // namespace Aurivia
