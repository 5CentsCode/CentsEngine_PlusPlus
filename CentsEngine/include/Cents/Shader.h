#pragma once
#include <string>
#include "Common.h"

class Shader
{
public:
    Shader(const std::string& vertexFile, const std::string& fragmentFile);
    ~Shader();

    void Bind();

    int32 GetUniformLocation(const char* name) const;

    void SetUniform(const char* name, const int32& value) const;
    void SetUniform(const char* name, const float& value) const;
    void SetUniform(const char* name, const glm::vec3& value) const;
    void SetUniform(const char* name, const glm::vec4& value) const;
    void SetUniform(const char* name, const glm::mat4& value) const;

private:
    void AttachAndLinkShaders(int32* shaderIds, int32 shaderCount);
    int32 CreateShader(int32 shaderType, const std::string& filepath);
    std::string ReadFile(const std::string& filepath);

private:
    int32 m_id;
};