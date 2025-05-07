#include "Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& texCoords, std::vector<uint16>& indices)
{
    Vertices = vertices;
    Normals = normals;
    TexCoords = texCoords;
    Indices = indices;

    Upload();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);

    for (int i = 0; i < 4; i++)
    {
        glDeleteBuffers(1, &m_vbos[i]);
    }
}

void Mesh::Draw()
{
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, (int32)Indices.size(), GL_UNSIGNED_SHORT, 0);
}

void Mesh::Upload()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Vertices
    int index = 0;
    glGenBuffers(1, &m_vbos[index]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[index]);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(glm::vec3), Vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(index);

    // Normals
    index++;
    glGenBuffers(1, &m_vbos[index]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[index]);
    glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(glm::vec3), Normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(index);

    // TexCoords
    index++;
    glGenBuffers(1, &m_vbos[index]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[index]);
    glBufferData(GL_ARRAY_BUFFER, TexCoords.size() * sizeof(glm::vec2), TexCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
    glEnableVertexAttribArray(index);

    // Indices
    index++;
    glGenBuffers(1, &m_vbos[index]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[index]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(uint16), Indices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(index);
}
