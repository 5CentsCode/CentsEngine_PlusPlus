#include "Debug.h"
#include <glad/glad.h>

void Debug::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color)
{
    UNUSED_PARAM(color);

    glm::vec3 vertices[2] =
    {
        start,
        end
    };

    uint32 vao;
    uint32 vbo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    int index = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(index);

    glDrawArrays(GL_LINES, 0, 2);

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
