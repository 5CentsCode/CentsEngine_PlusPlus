#pragma once
#include <string>
#include "Common.h"

class Texture
{
public:
    Texture(const std::string& textureFile);
    ~Texture();

    void Bind();
    uint32 GetId();

private:
    void Upload(uint8* const data);

private:
    uint32 m_id;

    int32 m_width;
    int32 m_height;
    int32 m_channels;
};