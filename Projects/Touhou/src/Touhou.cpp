#include "Touhou.h"
#include <Cents/Input.h>

float height = 600.0f;
float orthoSize = 600.0f;
float scale = orthoSize / height;
float halfWidth = 400.0f;
float halfHeight = 300.0f;
float size = 15.0f;
float paddleHeight = 80.0f;

void Touhou::Init()
{
    Application::Init();
}

void Touhou::Load()
{
    Application::Load();

    m_model = new Model("content/models/quad.obj");
    m_shader = new Shader("content/shaders/texture.vert", "content/shaders/texture.frag");
    m_texture = new Texture("content/textures/basecharacter.png");

    m_camera.ProjectionMode = Component::Camera::ProjectionMode::Orthographic;
    m_camera.OrthographicSize = orthoSize;
    m_camera.AspectRatio = 800.0f / 600.0f;
    m_cameraTransform.Position = glm::vec3(0.0f, 0.0f, 10.0f);

    m_shader->Bind();
    m_shader->SetUniform("uView", m_cameraTransform.GetViewMatrix());
    m_shader->SetUniform("uProjection", m_camera.GetProjectionMatrix());
    m_shader->SetUniform("uTexture", 0);

    m_characterTransform.Scale = glm::vec3(128.0f, 128.0f, 1.0f);
}

void Touhou::Unload()
{
    Application::Unload();
    delete m_shader;
    delete m_model;
    delete m_texture;
}

void Touhou::UpdateFrame(float deltaTime)
{
    Application::UpdateFrame(deltaTime);
}

void Touhou::RenderFrame(float deltaTime)
{
    Application::RenderFrame(deltaTime);

    m_shader->Bind();
    m_shader->SetUniform("uModel", m_characterTransform.GetWorldMatrix());
    m_model->Draw();
}