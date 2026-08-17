#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <string>

namespace Aurivia {

/**
 * @brief Internal shader utilities
 */
namespace ShaderUtils
{
    /**
     * Compile a shader source and check for errors
     */
    inline uint32_t CompileShader(const std::string& source, GLenum type)
    {
        uint32_t shader = glCreateShader(type);
        const char* src = source.c_str();
        
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);
        
        // Check for compilation errors
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            throw std::runtime_error(std::string("Shader compilation error: ") + infoLog);
        }
        
        return shader;
    }
    
    /**
     * Link shader program
     */
    inline uint32_t LinkProgram(uint32_t vertexShader, uint32_t fragmentShader)
    {
        uint32_t program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        
        // Check for linking errors
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            throw std::runtime_error(std::string("Shader linking error: ") + infoLog);
        }
        
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        
        return program;
    }
}

} // namespace Aurivia
