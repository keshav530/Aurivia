#include "aurivia/graphics2d.h"
#include "aurivia/logger.h"
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

namespace Aurivia {

Graphics2D::Graphics2D(Renderer* renderer)
    : m_renderer(renderer),
      m_circleVAO(0), m_circleVBO(0), m_circleIndexCount(0),
      m_lineVAO(0), m_lineVBO(0),
      m_quadVAO(0), m_quadVBO(0)
{
    AV_LOG_INFO("Initializing 2D Graphics System");
    
    // Create circle mesh for circles/diagrams
    CreateCircleMesh(1.0f, 32);
    CreateLineMesh();
}

Graphics2D::~Graphics2D()
{
    if (m_circleVAO)
        glDeleteVertexArrays(1, &m_circleVAO);
    if (m_lineVAO)
        glDeleteVertexArrays(1, &m_lineVAO);
}

void Graphics2D::DrawSprite(const Sprite& sprite)
{
    if (!m_renderer)
        return;
    
    // TODO: Implement sprite rendering with texture
    // For now, render as colored quad
    DrawQuad(sprite.position, sprite.size, sprite.color);
}

void Graphics2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
{
    if (!m_renderer)
        return;
    
    glm::mat4 model = glm::identity<glm::mat4>();
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
    
    // Draw using renderer (extends to 2D)
    m_renderer->DrawQuad(position, size, color);
}

void Graphics2D::DrawCircle(const glm::vec2& position, float radius, const glm::vec3& color)
{
    if (!m_renderer || !m_circleVAO)
        return;
    
    // Bind circle VAO and draw
    glBindVertexArray(m_circleVAO);
    glDrawElements(GL_TRIANGLES, m_circleIndexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Graphics2D::DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color, float thickness)
{
    if (!m_renderer)
        return;
    
    m_renderer->DrawLine(start, end, color);
}

void Graphics2D::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color, float thickness)
{
    // Draw rectangle outline using 4 lines
    glm::vec2 topLeft = position;
    glm::vec2 topRight = position + glm::vec2(size.x, 0);
    glm::vec2 bottomRight = position + size;
    glm::vec2 bottomLeft = position + glm::vec2(0, size.y);
    
    DrawLine(topLeft, topRight, color, thickness);
    DrawLine(topRight, bottomRight, color, thickness);
    DrawLine(bottomRight, bottomLeft, color, thickness);
    DrawLine(bottomLeft, topLeft, color, thickness);
}

uint32_t Graphics2D::LoadTexture(const std::string& filepath)
{
    // TODO: Implement texture loading using stb_image or similar
    AV_LOG_WARN("Texture loading not yet implemented: " + filepath);
    return 0;
}

void Graphics2D::UnloadTexture(uint32_t textureID)
{
    if (textureID > 0)
        glDeleteTextures(1, &textureID);
}

void Graphics2D::BeginBatch()
{
    // TODO: Setup batch rendering
}

void Graphics2D::EndBatch()
{
    // TODO: Flush batched draws
}

void Graphics2D::Flush()
{
    // TODO: Submit all batched draws
}

void Graphics2D::CreateCircleMesh(float radius, int segments)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    // Center vertex
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    
    // Perimeter vertices
    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.0f * 3.14159265f * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }
    
    // Create triangles
    for (int i = 1; i <= segments; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    
    m_circleIndexCount = indices.size();
    
    GLuint VBO, EBO;
    glGenVertexArrays(1, &m_circleVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(m_circleVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    AV_LOG_DEBUG("Circle mesh created with " + std::to_string(segments) + " segments");
}

void Graphics2D::CreateLineMesh()
{
    // Line mesh data (2D)
    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };
    
    GLuint VBO;
    glGenVertexArrays(1, &m_lineVAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(m_lineVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

} // namespace Aurivia
