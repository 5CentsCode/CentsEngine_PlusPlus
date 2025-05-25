#include "Pong.h"
#include <Cents/Common.h>
#include <Cents/Input.h>

float height = 600.0f;
float orthoSize = 600.0f;
float scale = orthoSize / height;
float halfWidth = 400.0f;
float halfHeight = 300.0f;
float size = 15.0f;
float paddleHeight = 80.0f;

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
    m_camera.OrthographicSize = orthoSize;
    m_camera.AspectRatio = 800.0f / 600.0f;
    m_cameraTransform.Position = glm::vec3(0.0f, 0.0f, 10.0f);

    halfWidth *= scale;
    halfHeight *= scale;
    size *= scale;
    paddleHeight *= scale;

    m_shader->Bind();
    m_shader->SetUniform("View", m_cameraTransform.GetViewMatrix());
    m_shader->SetUniform("Projection", m_camera.GetProjectionMatrix());

    m_ball.Transform.Scale = glm::vec3(size, size, 1.0f);
    m_leftPaddle.Transform.Scale = glm::vec3(size, paddleHeight, 1.0f);
    m_rightPaddle.Transform.Scale = glm::vec3(size, paddleHeight, 1.0f);

    Reset();
    Start();
}

void Pong::Unload()
{
    Application::Unload();
    delete m_shader;
    delete m_model;
}

void Pong::UpdateFrame(float deltaTime)
{
    Application::UpdateFrame(deltaTime);

    glm::vec3 position = m_ball.Transform.Position;
    glm::vec3 newPosition = position + (m_ball.Velocity * m_ball.Speed * (float)deltaTime);
    glm::vec4 ballBounds = m_ball.GetBounds();
    const float ballSpeedIncrease = 1.05f;

    glm::vec3 paddleMoveDirection = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 leftPaddleMovement = glm::vec3(0.0f);
    if (Input::IsKeyDown(KeyCode::Q))
    {
        leftPaddleMovement += paddleMoveDirection;
    }
    if (Input::IsKeyDown(KeyCode::A))
    {
        leftPaddleMovement -= paddleMoveDirection;
    }
    m_leftPaddle.Transform.Position += leftPaddleMovement * m_leftPaddle.Speed * deltaTime;

    glm::vec3 rightPaddleMovement = glm::vec3(0.0f);
    if (Input::IsKeyDown(KeyCode::O))
    {
        rightPaddleMovement += paddleMoveDirection;
    }
    if (Input::IsKeyDown(KeyCode::L))
    {
        rightPaddleMovement -= paddleMoveDirection;
    }
    m_rightPaddle.Transform.Position += rightPaddleMovement * m_leftPaddle.Speed * deltaTime;;

    glm::vec4 paddleBounds[]
    {
        m_leftPaddle.GetBounds(),
        m_rightPaddle.GetBounds()
    };

    for (const glm::vec4& paddleBound : paddleBounds)
    {
        bool intersection = ballBounds.x < paddleBound.z &&
            ballBounds.z > paddleBound.x &&
            ballBounds.y < paddleBound.w &&
            ballBounds.w > paddleBound.y;

        if (intersection)
        {
            glm::vec2 ballPosition = glm::vec2((ballBounds.x + ballBounds.z) * 0.5f, (ballBounds.y + ballBounds.w) * 0.5f);
            glm::vec2 paddlePosition = glm::vec2((paddleBound.x + paddleBound.z) * 0.5f, (paddleBound.y + paddleBound.w) * 0.5f);
            glm::vec2 posDelta = glm::abs(ballPosition - paddlePosition);
            float distance = glm::length(posDelta);

            if (glm::sign(paddlePosition.x) == glm::sign(m_ball.Velocity.x) &&
                distance < (ballBounds.w - ballBounds.y) + (paddleBound.w - paddleBound.y))
            {
                glm::vec3 invertVelocity = glm::vec3(glm::normalize(posDelta), 0.0f) * glm::vec3(-1.0f, 1.0f, 1.0f);
                m_ball.Velocity *= invertVelocity;
                m_ball.Velocity.x = glm::sign(m_ball.Velocity.x) * glm::clamp(glm::abs(m_ball.Velocity.x), 0.35f, 1.0f);
                m_ball.Speed *= ballSpeedIncrease;
            }
        }
    }

    glm::vec2 ballSize = m_ball.GetSize() * 0.5f;
    if (ballBounds.x < -halfWidth ||
        ballBounds.z > halfWidth)
    {
        m_ball.Velocity *= glm::vec3(-1.0f, 1.0f, 0.0f);
        newPosition.x = glm::clamp(newPosition.x, -halfWidth + ballSize.x, halfWidth - ballSize.x);
        m_ball.Speed *= ballSpeedIncrease;
    }

    if (ballBounds.y < -halfHeight ||
        ballBounds.w > halfHeight)
    {
        m_ball.Velocity *= glm::vec3(1.0f, -1.0f, 0.0f);
        newPosition.y = glm::clamp(newPosition.y, -halfHeight + ballSize.y, halfHeight - ballSize.y);
        m_ball.Speed *= ballSpeedIncrease;
    }

    m_ball.Velocity = glm::normalize(m_ball.Velocity);
    m_ball.Transform.Position = newPosition;
}

void Pong::RenderFrame(float deltaTime)
{
    Application::RenderFrame(deltaTime);

    m_shader->Bind();

    m_shader->SetUniform("Model", m_ball.Transform.GetWorldMatrix());
    m_model->Draw();

    m_shader->SetUniform("Model", m_leftPaddle.Transform.GetWorldMatrix());
    m_model->Draw();

    m_shader->SetUniform("Model", m_rightPaddle.Transform.GetWorldMatrix());
    m_model->Draw();
}

void Pong::Start()
{
    int randX = rand() % 100;
    int randY = rand() % 100;
    m_ball.Velocity = glm::normalize(glm::vec3(randX, randY, 0.0f));
    m_ball.Speed = 150.0f * scale;
}

void Pong::Reset()
{
    m_ball.Transform.Position = glm::vec3(0.0f);
    m_ball.Velocity = glm::vec3(0.0f);
    m_leftPaddle.Transform.Position = glm::vec3(-halfWidth + (size * 2.0f), 0.0f, 0.0f);
    m_rightPaddle.Transform.Position = glm::vec3(halfWidth - (size * 2.0f), 0.0f, 0.0f);
}
