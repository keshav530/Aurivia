#include "aurivia/renderer.h"
#include "aurivia/logger.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/gtc/type_ptr.hpp>

namespace Aurivia {

// ==================== Shader ====================

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
    : m_vertexID(0), m_fragmentID(0), m_programID(0),
      m_vertexSrc(vertexSrc), m_fragmentSrc(fragmentSrc)
{
}

Shader::~Shader()
{
    if (m_programID)
        glDeleteProgram(m_programID);
}

bool Shader::Compile()
{
    // Compile vertex shader
    m_vertexID = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSrcPtr = m_vertexSrc.c_str();
    glShaderSource(m_vertexID, 1, &vertexSrcPtr, nullptr);
    glCompileShader(m_vertexID);
    
    // Check vertex compilation
    int success;
    char infoLog[512];
    glGetShaderiv(m_vertexID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_vertexID, 512, nullptr, infoLog);
        AV_LOG_ERROR("Vertex shader compilation failed: " + std::string(infoLog));
        return false;
    }
    
    // Compile fragment shader
    m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSrcPtr = m_fragmentSrc.c_str();
    glShaderSource(m_fragmentID, 1, &fragmentSrcPtr, nullptr);
    glCompileShader(m_fragmentID);
    
    // Check fragment compilation
    glGetShaderiv(m_fragmentID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_fragmentID, 512, nullptr, infoLog);
        AV_LOG_ERROR("Fragment shader compilation failed: " + std::string(infoLog));
        return false;
    }
    
    // Link program
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);
    glLinkProgram(m_programID);
    
    // Check linking
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_programID, 512, nullptr, infoLog);
        AV_LOG_ERROR("Shader program linking failed: " + std::string(infoLog));
        return false;
    }
    
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    
    return true;
}

void Shader::Use() const
{
    glUseProgram(m_programID);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& matrix)
{
    GLint loc = glGetUniformLocation(m_programID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniform(const std::string& name, const glm::vec3& vec)
{
    GLint loc = glGetUniformLocation(m_programID, name.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(vec));
}

void Shader::SetUniform(const std::string& name, float value)
{
    GLint loc = glGetUniformLocation(m_programID, name.c_str());
    glUniform1f(loc, value);
}

void Shader::SetUniform(const std::string& name, int value)
{
    GLint loc = glGetUniformLocation(m_programID, name.c_str());
    glUniform1i(loc, value);
}

// ==================== Renderer ====================

Renderer::Renderer(uint32_t width, uint32_t height)
    : m_width(width), m_height(height),
      m_cubeVAO(0), m_cubeVBO(0), m_cubeIndexCount(0),
      m_sphereVAO(0), m_sphereVBO(0), m_sphereIndexCount(0),
      m_planeVAO(0), m_planeVBO(0), m_planeIndexCount(0),
      m_quadVAO(0), m_quadVBO(0), m_quadIndexCount(0),
      m_clearColor(0.1f, 0.1f, 0.1f, 1.0f)
{
    m_viewMatrix = glm::identity<glm::mat4>();
    m_projectionMatrix = glm::identity<glm::mat4>();
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
    AV_LOG_INFO("Initializing Renderer...");
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // Setup basic shader
    std::string vertexShader = R"(
        #version 430 core
        layout (location = 0) in vec3 aPosition;
        layout (location = 1) in vec3 aNormal;
        
        uniform mat4 uView;
        uniform mat4 uProjection;
        uniform mat4 uModel;
        
        out vec3 vNormal;
        out vec3 vFragPos;
        
        void main()
        {
            vFragPos = vec3(uModel * vec4(aPosition, 1.0));
            vNormal = mat3(transpose(inverse(uModel))) * aNormal;
            gl_Position = uProjection * uView * vec4(vFragPos, 1.0);
        }
    )";
    
    std::string fragmentShader = R"(
        #version 430 core
        in vec3 vNormal;
        in vec3 vFragPos;
        
        uniform vec3 uColor;
        
        out vec4 FragColor;
        
        void main()
        {
            vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
            float diff = max(dot(vNormal, lightDir), 0.2);
            vec3 result = uColor * diff;
            FragColor = vec4(result, 1.0);
        }
    )";
    
    m_basicShader = std::make_unique<Shader>(vertexShader, fragmentShader);
    if (!m_basicShader->Compile())
    {
        AV_LOG_ERROR("Failed to compile basic shader");
        return false;
    }
    
    // Create mesh data
    CreateCubeMesh();
    
    AV_LOG_INFO("Renderer initialized successfully");
    return true;
}

void Renderer::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::BeginFrame()
{
    m_basicShader->Use();
}

void Renderer::EndFrame()
{
    // Frame end logic
}

void Renderer::DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& color)
{
    m_basicShader->Use();
    
    glm::mat4 model = glm::identity<glm::mat4>();
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    
    m_basicShader->SetUniform("uModel", model);
    m_basicShader->SetUniform("uView", m_viewMatrix);
    m_basicShader->SetUniform("uProjection", m_projectionMatrix);
    m_basicShader->SetUniform("uColor", color);
    
    if (m_cubeVAO)
    {
        glBindVertexArray(m_cubeVAO);
        glDrawElements(GL_TRIANGLES, m_cubeIndexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}

void Renderer::DrawSphere(const glm::vec3& position, float radius, const glm::vec3& color)
{
    // TODO: Implement sphere rendering
}

void Renderer::DrawPlane(const glm::vec3& position, const glm::vec2& scale, const glm::vec3& color)
{
    // TODO: Implement plane rendering
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
{
    // TODO: Implement quad rendering
}

void Renderer::DrawLine(const glm::vec2& start, const glm::vec2& end, const glm::vec3& color)
{
    // TODO: Implement line rendering
}

void Renderer::SetViewMatrix(const glm::mat4& view)
{
    m_viewMatrix = view;
}

void Renderer::SetProjectionMatrix(const glm::mat4& projection)
{
    m_projectionMatrix = projection;
}

void Renderer::SetViewport(uint32_t width, uint32_t height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
    m_clearColor = glm::vec4(r, g, b, a);
}

void Renderer::CreateCubeMesh()
{
    // Cube vertices and normals
    float vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        
        // Back face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        
        // Top face
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        
        // Bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        
        // Right face
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
        
        // Left face
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
    };
    
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,       // Front
        4, 5, 6, 6, 7, 4,       // Back
        8, 9, 10, 10, 11, 8,    // Top
        12, 13, 14, 14, 15, 12, // Bottom
        16, 17, 18, 18, 19, 16, // Right
        20, 21, 22, 22, 23, 20  // Left
    };
    
    m_cubeIndexCount = 36;
    
    GLuint VBO, EBO;
    glGenVertexArrays(1, &m_cubeVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(m_cubeVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::CreateSphereMesh()
{
    // TODO: Implement sphere mesh creation
}

void Renderer::CreatePlaneMesh()
{
    // TODO: Implement plane mesh creation
}

void Renderer::CreateQuadMesh()
{
    // TODO: Implement quad mesh creation
}

} // namespace Aurivia
