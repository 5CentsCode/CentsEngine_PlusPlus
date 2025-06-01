#include "Component/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Component;

Component::Camera::Camera(const Window* window)
{
    m_window = window;
}

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

glm::vec3 Component::Camera::ScreenToWorldPoint(const Component::Transform& cameraTransform, const glm::vec3& screenPosition) const
{
    glm::mat4 projection = GetProjectionMatrix();
    glm::mat4 view = cameraTransform.GetViewMatrix();
    glm::mat4 model = cameraTransform.GetWorldMatrix();
    glm::mat4 viewModel = view * model;
    glm::vec4 viewport = glm::vec4(0, 0, m_window->GetWidth(), m_window->GetHeight());

    glm::vec3 position = glm::vec3(screenPosition.x, m_window->GetHeight() - screenPosition.y, screenPosition.z);
    glm::vec3 worldPosition = glm::unProject(position, view, projection, viewport) + cameraTransform.Position;;
    return worldPosition;
}

Ray Component::Camera::ScreenPointToRay(const Component::Transform& cameraTransform, const glm::vec2& screenPosition) const
{
    glm::mat4 projection = GetProjectionMatrix();
    glm::mat4 view = cameraTransform.GetViewMatrix();
    glm::mat4 model = cameraTransform.GetWorldMatrix();
    glm::mat4 viewModel = view * model;
    glm::vec4 viewport = glm::vec4(0, 0, m_window->GetWidth(), m_window->GetHeight());

    glm::vec3 position = glm::vec3(screenPosition.x, m_window->GetHeight() - screenPosition.y, 0.0f);
    glm::vec3 origin = glm::unProject(position, view, projection, viewport);

    position.z = 1.0f;
    glm::vec3 end = glm::unProject(position, view, projection, viewport);

    Ray ray;
    ray.Origin = origin;
    ray.Direction = glm::normalize(end - origin);
    return ray;
}
