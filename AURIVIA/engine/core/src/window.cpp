#include "aurivia/window.h"
#include "aurivia/logger.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

namespace Aurivia {

Window::Window(const std::string& title, uint32_t width, uint32_t height)
    : m_window(nullptr), m_title(title), m_width(width), m_height(height), m_isInitialized(false)
{
}

Window::~Window()
{
    if (m_isInitialized)
        Shutdown();
}

bool Window::Initialize()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        AV_LOG_ERROR("Failed to initialize GLFW");
        return false;
    }
    
    // Set OpenGL context hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create window
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        AV_LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }
    
    // Make context current
    glfwMakeContextCurrent(m_window);
    
    // Enable vsync
    glfwSwapInterval(1);
    
    m_isInitialized = true;
    return true;
}

void Window::Shutdown()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
    m_isInitialized = false;
}

void Window::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers()
{
    if (m_window)
        glfwSwapBuffers(m_window);
}

bool Window::ShouldClose() const
{
    return m_window && glfwWindowShouldClose(m_window);
}

void Window::SetShouldClose(bool value)
{
    if (m_window)
        glfwSetWindowShouldClose(m_window, value ? GLFW_TRUE : GLFW_FALSE);
}

void Window::SetFramebufferSizeCallback(void (*callback)(GLFWwindow*, int, int))
{
    if (m_window && callback)
        glfwSetFramebufferSizeCallback(m_window, callback);
}

} // namespace Aurivia
