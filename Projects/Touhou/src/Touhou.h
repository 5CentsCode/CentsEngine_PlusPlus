#pragma once
#define STB_IMAGE_IMPLEMTNATION
#include <Cents/Common.h>
#include <Cents/Application.h>
#include <Cents/Model.h>
#include <Cents/Shader.h>
#include <Cents/Texture.h>
#include <Cents/Component/Camera.h>
#include <Cents/Component/Transform.h>

class Touhou : public Application
{
protected:
    void Init() override;
    void Load() override;
    void Unload() override;

    void UpdateFrame(float deltaTime) override;
    void RenderFrame(float deltaTime) override;

private:
    Shader* m_shader = nullptr;
    Model* m_model = nullptr;
    Texture* m_texture = nullptr;
    Component::Camera m_camera;
    Component::Transform m_cameraTransform;

    Component::Transform m_characterTransform;
};

CREATE_APPLICATION(Touhou);