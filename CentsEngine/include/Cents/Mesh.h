#pragma once
#include "Common.h"
#include <vector>

class Mesh
{
public:
    Mesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& textCoords, std::vector<uint16>& indices);
    ~Mesh();

    std::vector<glm::vec3> Vertices;
    std::vector<glm::vec3> Normals;
    std::vector<glm::vec2> TexCoords;
    std::vector<uint16> Indices;

    void Draw();

private:
    void Upload();

    uint32 m_vao = 0;
    uint32 m_vbos[4];
};