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
    Shader* m_textureShader = nullptr;
    Shader* m_whiteShader = nullptr;

    Model* m_quadModel = nullptr;
    Model* m_planeModel = nullptr;

    Texture* m_texture = nullptr;

    bool m_debugMode = false;
    Component::Camera m_camera;
    Component::Transform m_debugCamTransform;
    Component::Transform m_gameCamTransform;

    Component::Transform m_playerTransform;
    Component::Transform m_planeTransform;
};

CREATE_APPLICATION(Touhou);