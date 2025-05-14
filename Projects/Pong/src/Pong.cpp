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

    m_camera.ProjectionMode = Component::Camera::ProjectionMode::Orthographic;
    m_camera.AspectRatio = 800.0f / 600.0f;
    m_cameraTransform.Position = glm::vec3(0.0f, 0.0f, 10.0f);

    m_modelTransform.Position = glm::vec3(0.0f, 0.0f, 0.0f);
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
    m_shader->SetUniform("Model", m_modelTransform.GetWorldMatrix());
    m_shader->SetUniform("View", m_cameraTransform.GetViewMatrix());
    m_shader->SetUniform("Projection", m_camera.GetProjectionMatrix());
    m_model->Draw();
}
