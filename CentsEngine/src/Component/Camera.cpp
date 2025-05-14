#include "Component/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Component;

glm::mat4 Component::Camera::GetProjectionMatrix() const
{
    glm::mat4 projectionMatrix = glm::identity<glm::mat4>();

    switch (ProjectionMode)
    {
        case ProjectionMode::Orthographic:
        {
            float halfWidth = AspectRatio * OrthographicSize * 0.5f;
            float halfHeight = OrthographicSize * 0.5f;
            projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, NearClippingPlane, FarClippingPlane);
            break;
        }

        case ProjectionMode::Perspective:
        {
            projectionMatrix = glm::perspective(glm::radians(FieldOfView), AspectRatio, NearClippingPlane, FarClippingPlane);
            break;
        }
    }

    return projectionMatrix;
}
