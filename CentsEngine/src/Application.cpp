#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Common.h"
#include "Input.h"

Application::Application()
{
}

void Application::Init()
{
    m_window = new Window();
}

void Application::Load()
{
}

void Application::Unload()
{
    delete m_window;
}

void Application::UpdateFrame(float deltaTime)
{
    UNUSED_PARAM(deltaTime);
}

void Application::RenderFrame(float deltaTime)
{
    UNUSED_PARAM(deltaTime);
}

void Application::Loop()
{
    long frame = 0;
    float lastFrameTime = (float)glfwGetTime();
    float currentFrameTime = lastFrameTime;
    float deltaTime = currentFrameTime - lastFrameTime;

    while (m_window->ShouldClose() == false)
    {
        frame++;
        lastFrameTime = currentFrameTime;
        currentFrameTime = (float)glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;

        Input::PollInputEvents();

        UpdateFrame(deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderFrame(deltaTime);

        m_window->SwapBuffers();
    }
}
