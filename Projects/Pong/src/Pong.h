#include <Cents/Application.h>
#include <Cents/Shader.h>
#include <Cents/Model.h>
#include <Cents/Component/Camera.h>
#include <Cents/Component/Transform.h>
#include "Ball.h"
#include "Paddle.h"

class Pong : public Application
{
protected:
    void Init() override;
    void Load() override;
    void Unload() override;

    void UpdateFrame(float deltaTime) override;
    void RenderFrame(float deltaTime) override;

private:

    void Start();
    void Reset();

private:
    Shader* m_shader;
    Model* m_model;
    Component::Camera m_camera;
    Component::Transform m_cameraTransform;

    Ball m_ball;
    Paddle m_leftPaddle;
    Paddle m_rightPaddle;
};

CREATE_APPLICATION(Pong);