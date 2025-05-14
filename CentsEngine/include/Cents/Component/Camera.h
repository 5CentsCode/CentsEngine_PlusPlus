#pragma once
#include "../Common.h"

namespace Component
{
    struct Camera
    {
        enum class ProjectionMode : uint8
        {
            Orthographic = 0,
            Perspective = 1
        };

        float NearClippingPlane = 0.1f;
        float FarClippingPlane = 1000.0f;

        float FieldOfView = 60.0f;
        float AspectRatio = 16.0f / 9.0f;
        float OrthographicSize = 5.0f;

        ProjectionMode ProjectionMode = ProjectionMode::Perspective;

        glm::mat4 GetProjectionMatrix() const;
    };
}