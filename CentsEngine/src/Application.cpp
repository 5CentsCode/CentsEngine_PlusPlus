#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

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
}

void Application::UnLoad()
{
}

void Application::UpdateFrame()
{
}

void Application::RenderFrame()
{
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
