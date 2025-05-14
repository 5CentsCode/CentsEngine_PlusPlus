#include <Cents/Application.h>
#include <Cents/Shader.h>
#include <Cents/Model.h>
#include <Cents/Component/Camera.h>
#include <Cents/Component/Transform.h>

class Pong : public Application
{
protected:
    void Init() override;
    void Load() override;
    void Unload() override;

    void UpdateFrame() override;
    void RenderFrame() override;

private:
    Shader* m_shader;
    Model* m_model;
    Component::Camera m_camera;
    Component::Transform m_cameraTransform;
    Component::Transform m_modelTransform;
};

CREATE_APPLICATION(Pong);