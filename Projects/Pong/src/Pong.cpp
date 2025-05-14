#include "Pong.h"
#include <Cents/Common.h>

void Pong::Init()
{
    Application::Init();
}

void Pong::Load()
{
    Application::Load();

    m_shader = new Shader("content/shaders/white.vert", "content/shaders/white.frag");
    m_model = new Model("content/models/quad.obj");
}

void Pong::Unload()
{
    Application::Unload();
    delete m_shader;
    delete m_model;
}

void Pong::UpdateFrame()
{
    Application::UpdateFrame();
}

void Pong::RenderFrame()
{
    Application::RenderFrame();

    m_shader->Bind();
    m_model->Draw();
}
