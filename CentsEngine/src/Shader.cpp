#include "Shader.h"
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
{
    m_id = glCreateProgram();

    int32 shaderIds[2]
    {
        CreateShader(GL_VERTEX_SHADER, vertexFile),
        CreateShader(GL_FRAGMENT_SHADER, fragmentFile)
    };
    AttachAndLinkShaders(shaderIds, 2);
}

Shader::~Shader()
{
}

int32 Shader::CreateShader(int32 shaderType, const std::string& filepath)
{
    std::string shaderCode = ReadFile(filepath.c_str());
    const char* code = shaderCode.c_str();

    int32 shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::OpenGLShader::%i\n", shaderType);
        printf("\t%s\n", infoLog);
    };

    return shader;
}

void Shader::Bind()
{
    glUseProgram(m_id);
}

void Shader::SetUniform(const char* name, const int32& value) const
{
    int32 uniformLocation = GetUniformLocation(name);
    glUniform1i(uniformLocation, value);
}

void Shader::SetUniform(const char* name, const float& value) const
{
    int32 uniformLocation = GetUniformLocation(name);
    glUniform1f(uniformLocation, value);
}

int32 Shader::GetUniformLocation(const char* name) const
{
    int uniformLocation = glGetUniformLocation(m_id, name);
    return uniformLocation;
}

void Shader::SetUniform(const char* name, const glm::vec3& value) const
{
    int32 uniformLocation = GetUniformLocation(name);
    glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const char* name, const glm::vec4& value) const
{
    int32 uniformLocation = GetUniformLocation(name);
    glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
}

void Shader::SetUniform(const char* name, const glm::mat4& value) const
{
    int32 uniformLocation = GetUniformLocation(name);
    glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(value));
}

void Shader::AttachAndLinkShaders(int32* shaderIds, int32 shaderCount)
{
    for (int32 i = 0; i < shaderCount; i++)
    {
        int32 shaderId = *(shaderIds + i);
        glAttachShader(m_id, shaderId);
    }

    int success;
    char infoLog[512];
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_id, 512, NULL, infoLog);
        printf("ERROR::OpenGLShader::PROGRAM::LINKING_FAILED\n");
        printf("\t%s\n", infoLog);
    };

    for (int32 i = 0; i < shaderCount; i++)
    {
        int32 shaderId = *(shaderIds + i);
        glDeleteShader(shaderId);
    }
}

std::string Shader::ReadFile(const std::string& filepath)
{
    std::string buffer;
    bool fileExists = std::filesystem::exists(filepath);
    if (fileExists)
    {
        std::ifstream file(filepath);
        buffer.resize((size_t)std::filesystem::file_size(filepath));
        file.read(buffer.data(), buffer.size());
        file.close();
    }

    return buffer;
}
