#pragma once
#include "Common.h"
#include <string>

class Shader
{
public:
    Shader(const std::string& vertexFile, const std::string& fragmentFile);
    ~Shader();

    void Bind();

private:
    void AttachAndLinkShaders(int32* shaderIds, int32 shaderCount);
    int32 CreateShader(int32 shaderType, const std::string& filepath);
    std::string ReadFile(const std::string& filepath);

private:
    int32 m_id;
};