#include "Application.h"
#include "Common.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

// All of this is TEMPORARY
GLFWwindow* window;
Shader* shader;

std::vector<glm::vec3> vertices
{
    glm::vec3(-0.5f, -0.5f, 0.0f),
    glm::vec3(0.5f, -0.5f, 0.0f),
    glm::vec3(0.0f, 0.5f, 0.0f),
};

std::vector<uint32> indices
{
    0, 1, 2
};

uint32 vao;
uint32 vbo;
uint32 ibo;

Application::Application()
{
}

void Application::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, 800, 600);
}

void Application::Load()
{
    shader = new Shader("content/shaders/white.vert", "content/shaders/white.frag");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(uint32), indices.data(), GL_STATIC_DRAW);
}

void Application::UnLoad()
{
    delete shader;
}

void Application::UpdateFrame()
{
}

void Application::RenderFrame()
{
    shader->Bind();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void Application::Loop()
{
    while (glfwWindowShouldClose(window) == false)
    {
        glfwPollEvents();

        UpdateFrame();

        RenderFrame();

        glfwSwapBuffers(window);
    }
}
