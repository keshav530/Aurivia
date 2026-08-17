#pragma once

#include "aurivia/renderer.h"
#include <glm/glm.hpp>
#include <string>

namespace Aurivia {

/**
 * @brief 2D Graphics rendering system
 * Handles sprites, text, UI elements
 */
class Graphics2D
{
public:
    Graphics2D(Renderer* renderer);
    ~Graphics2D();
    
    // Sprite rendering
    struct Sprite
    {
        glm::vec2 position;
        glm::vec2 size;
        glm::vec3 color;
        float rotation;
        uint32_t textureID;
    };
    
    void DrawSprite(const Sprite& sprite);
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
    void DrawCircle(const glm::vec2& position, float radius, const glm::vec3& color);
    void DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color, float thickness = 2.0f);
    void DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color, float thickness = 2.0f);
    
    // Text rendering (future)
    // void DrawText(const std::string& text, const glm::vec2& position, float size, const glm::vec3& color);
    
    // Texture management
    uint32_t LoadTexture(const std::string& filepath);
    void UnloadTexture(uint32_t textureID);
    
    // Batch rendering
    void BeginBatch();
    void EndBatch();
    void Flush();

private:
    Renderer* m_renderer;
    void CreateCircleMesh(float radius, int segments);
    void CreateLineMesh();
    
    uint32_t m_circleVAO, m_circleVBO, m_circleIndexCount;
    uint32_t m_lineVAO, m_lineVBO;
    uint32_t m_quadVAO, m_quadVBO;
};

} // namespace Aurivia
