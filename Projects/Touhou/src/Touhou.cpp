#include <Cents/Input.h>
#include "Touhou.h"
#include <Cents/Debug.h>
#include <Cents/Plane.h>

float height = 600.0f;
float orthoSize = 600.0f;
float scale = orthoSize / height;
float halfWidth = 400.0f;
float halfHeight = 300.0f;
float size = 15.0f;
float paddleHeight = 80.0f;

const float cameraDistance = 10.0f;
const float minCameraAngle = -60.0f;
const float maxCameraAngle = -30.0f;
float cameraAngle = -45.0f;
float cameraDirection = 0.0f;

void Touhou::Init()
{
    Application::Init();
}

void Touhou::Load()
{
    Application::Load();

    m_quadModel = new Model("content/models/OffsetQuad.obj");
    m_planeModel = new Model("content/models/plane.obj");
    m_cubeModel = new Model("content/models/cube.obj");

    m_textureShader = new Shader("content/shaders/texture.vert", "content/shaders/texture.frag");
    m_colorShader = new Shader("content/shaders/color.vert", "content/shaders/color.frag");

    m_texture = new Texture("content/textures/BaseCharacter.png");

    m_camera = new Component::Camera(m_window);
    m_camera->ProjectionMode = Component::Camera::ProjectionMode::Perspective;
    m_camera->OrthographicSize = orthoSize;
    m_camera->AspectRatio = (float)m_window->GetWidth() / (float)m_window->GetHeight();
    // m_camera.FieldOfView = 60.0f;
    m_debugCamTransform.Position = glm::vec3(0.0f, 0.0f, 10.0f);

    m_playerTransform.Scale = glm::vec3(1.0f);
    m_playerTransform.Position += glm::vec3(0.0f, 0.0f, 0.0f);

    m_planeTransform.Position = glm::vec3(0.0f);
    m_planeTransform.Scale = glm::vec3(10.0f);

    m_cubeTransform.Scale = glm::vec3(1.0f);
    m_cubeTransform.Position += glm::vec3(5.0f, 0.5f, 0.0f);

    m_gameCamTransform.Rotation = glm::quat(glm::vec3(glm::radians(cameraAngle), 0.0f, 0.0f));
    m_gameCamTransform.Position = m_playerTransform.Position - m_gameCamTransform.GetForward() * cameraDistance;
}

void Touhou::Unload()
{
    Application::Unload();

    delete m_quadModel;
    delete m_planeModel;
    delete m_cubeModel;

    delete m_textureShader;
    delete m_colorShader;

    delete m_texture;

    delete m_camera;
}

void Touhou::UpdateFrame(float deltaTime)
{
    Application::UpdateFrame(deltaTime);

    if (Input::IsKeyPressed(KeyCode::F1))
    {
        m_debugMode = !m_debugMode;
        if (m_debugMode)
        {
            m_debugCamTransform = m_gameCamTransform;
        }
    }

    m_camera->AspectRatio = (float)m_window->GetWidth() / (float)m_window->GetHeight();

    if (m_debugMode == false)
    {
        glm::vec3 playerMovement = glm::vec3(0.0f);
        if (Input::IsKeyDown(KeyCode::W))
        {
            playerMovement += m_gameCamTransform.GetForward();
        }
        if (Input::IsKeyDown(KeyCode::A))
        {
            playerMovement -= m_gameCamTransform.GetRight();
        }
        if (Input::IsKeyDown(KeyCode::S))
        {
            playerMovement -= m_gameCamTransform.GetForward();
        }
        if (Input::IsKeyDown(KeyCode::D))
        {
            playerMovement += m_gameCamTransform.GetRight();
        }

        playerMovement.y = 0.0f;
        m_playerTransform.Position += playerMovement * 2.5f * deltaTime;

        float camDelta = 0.0f;
        if (Input::IsKeyDown(KeyCode::E))
        {
            camDelta += deltaTime;
        }
        if (Input::IsKeyDown(KeyCode::Q))
        {
            camDelta -= deltaTime;
        }

        cameraDirection = glm::mod(cameraDirection + camDelta * 75.0f, 360.0f);

        if (Input::IsKeyPressed(KeyCode::X))
        {
            cameraDirection = 0.0f;
        }

        glm::vec2 scrollWheel = Input::GetScrollWheelMove();
        if (scrollWheel.y != 0.0f)
        {
            cameraAngle = glm::clamp(cameraAngle + (scrollWheel.y * 1000.0f * deltaTime), minCameraAngle, maxCameraAngle);
        }

        m_gameCamTransform.Rotation = glm::quat(glm::vec3(glm::radians(cameraAngle), glm::radians(cameraDirection), 0.0f));
        m_gameCamTransform.Position = m_playerTransform.Position - m_gameCamTransform.GetForward() * cameraDistance;

        m_playerTransform.Rotation = glm::quat(glm::vec3(0.0f, glm::radians(cameraDirection), 0.0f));
    }
    if (m_debugMode == true)
    {
        glm::vec3 cameraMovement = glm::vec3(0.0f);
        if (Input::IsKeyDown(KeyCode::W))
        {
            cameraMovement += m_debugCamTransform.GetForward();
        }
        if (Input::IsKeyDown(KeyCode::A))
        {
            cameraMovement -= m_debugCamTransform.GetRight();
        }
        if (Input::IsKeyDown(KeyCode::S))
        {
            cameraMovement -= m_debugCamTransform.GetForward();
        }
        if (Input::IsKeyDown(KeyCode::D))
        {
            cameraMovement += m_debugCamTransform.GetRight();
        }

        if (Input::IsKeyDown(KeyCode::Z))
        {
            cameraMovement -= m_debugCamTransform.GetUp();
        }
        if (Input::IsKeyDown(KeyCode::X))
        {
            cameraMovement += m_debugCamTransform.GetUp();
        }

        m_debugCamTransform.Position += cameraMovement * 10.0f * deltaTime;

        static glm::vec2 previousMousePosition = Input::GetMousePosition();
        glm::vec2 mousePosition = Input::GetMousePosition();
        glm::vec2 mouseDelta = previousMousePosition - mousePosition;
        previousMousePosition = mousePosition;

        if (Input::IsMouseButtonDown(MouseCode::Right))
        {
            glm::quat yaw = glm::angleAxis((float)glm::radians(mouseDelta.x * 0.15f), VEC3_UP);
            glm::quat pitch = glm::angleAxis((float)glm::radians(mouseDelta.y * 0.15f), m_debugCamTransform.GetRight());
            glm::quat orientation = glm::normalize(yaw * pitch);

            m_debugCamTransform.Rotation = glm::normalize(orientation * m_debugCamTransform.Rotation);
        }
    }
}

void Touhou::RenderFrame(float deltaTime)
{
    Application::RenderFrame(deltaTime);

    Component::Transform camTransform;
    if (m_debugMode)
    {
        camTransform = m_debugCamTransform;
    }
    else
    {
        camTransform = m_gameCamTransform;
    }

    Component::Transform trans;
    trans.Position = m_playerTransform.Position;
    trans.Rotation = m_gameCamTransform.Rotation;
    trans.Scale = m_playerTransform.Scale;

    m_colorShader->Bind();
    m_colorShader->SetUniform("uView", camTransform.GetViewMatrix());
    m_colorShader->SetUniform("uProjection", m_camera->GetProjectionMatrix());

    m_textureShader->Bind();
    m_textureShader->SetUniform("uView", camTransform.GetViewMatrix());
    m_textureShader->SetUniform("uProjection", m_camera->GetProjectionMatrix());

    m_colorShader->Bind();
    m_colorShader->SetUniform("uColor", glm::vec4(0.5f));
    m_colorShader->SetUniform("uModel", m_planeTransform.GetWorldMatrix());
    m_planeModel->Draw();

    m_colorShader->Bind();
    m_colorShader->SetUniform("uColor", glm::vec4(0.65f, 0.55f, 0.6f, 1.0f));
    m_colorShader->SetUniform("uModel", m_cubeTransform.GetWorldMatrix());
    m_cubeModel->Draw();

    m_colorShader->Bind();
    m_colorShader->SetUniform("uColor", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    m_colorShader->SetUniform("uModel", glm::identity<glm::mat4>());

    glm::vec2 mousePosition = Input::GetMousePosition();
    Plane plane;
    plane.Point = glm::vec3(0.0f, 0.1f, 0.0f);
    plane.Normal = VEC3_UP;
    Ray ray = m_camera->ScreenPointToRay(camTransform, mousePosition);
    float enter = 0.0f;
    plane.Raycast(ray, OUT enter);
    glm::vec3 endPoint = ray.GetPoint(enter);

    Debug::DrawLine(m_playerTransform.Position + glm::vec3(0.0f, 0.1f, 0.0f), endPoint, glm::vec4(1.0f));

    m_textureShader->Bind();
    m_textureShader->SetUniform("uTexture", 0);
    m_textureShader->SetUniform("uModel", m_playerTransform.GetWorldMatrix());
    m_quadModel->Draw();
}