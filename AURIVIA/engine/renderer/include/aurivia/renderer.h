#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <memory>
#include <vector>

namespace Aurivia {

/**
 * @brief Shader program for rendering
 */
class Shader
{
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();
    
    bool Compile();
    void Use() const;
    void SetUniform(const std::string& name, const glm::mat4& matrix);
    void SetUniform(const std::string& name, const glm::vec3& vec);
    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, int value);
    
    uint32_t GetID() const { return m_programID; }

private:
    uint32_t m_vertexID;
    uint32_t m_fragmentID;
    uint32_t m_programID;
    std::string m_vertexSrc;
    std::string m_fragmentSrc;
};

/**
 * @brief 3D Renderer for both 3D and 2D graphics
 */
class Renderer
{
public:
    Renderer(uint32_t width, uint32_t height);
    ~Renderer();
    
    bool Initialize();
    void Clear(float r = 0.1f, float g = 0.1f, float b = 0.1f, float a = 1.0f);
    void BeginFrame();
    void EndFrame();
    
    // Rendering primitives
    void DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& color);
    void DrawSphere(const glm::vec3& position, float radius, const glm::vec3& color);
    void DrawPlane(const glm::vec3& position, const glm::vec2& scale, const glm::vec3& color);
    
    // 2D rendering
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
    void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color);
    
    // Camera
    void SetViewMatrix(const glm::mat4& view);
    void SetProjectionMatrix(const glm::mat4& projection);
    
    // Viewport
    void SetViewport(uint32_t width, uint32_t height);
    void SetClearColor(float r, float g, float b, float a = 1.0f);
    
    // Getters
    uint32_t GetWidth() const { return m_width; }
    uint32_t GetHeight() const { return m_height; }

private:
    void CreateCubeMesh();
    void CreateSphereMesh();
    void CreatePlaneMesh();
    void CreateQuadMesh();
    
    // Rendering state
    uint32_t m_width;
    uint32_t m_height;
    
    // Shaders
    std::unique_ptr<Shader> m_basicShader;
    
    // Mesh data (VAO/VBO handles)
    uint32_t m_cubeVAO, m_cubeVBO, m_cubeIndexCount;
    uint32_t m_sphereVAO, m_sphereVBO, m_sphereIndexCount;
    uint32_t m_planeVAO, m_planeVBO, m_planeIndexCount;
    uint32_t m_quadVAO, m_quadVBO, m_quadIndexCount;
    
    // Camera
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    
    // Clear color
    glm::vec4 m_clearColor;
};

} // namespace Aurivia
