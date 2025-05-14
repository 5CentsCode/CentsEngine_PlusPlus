#include "Component/Transform.h"

using namespace Component;

glm::vec3 Transform::GetForward() const
{
    glm::vec3 forward = glm::normalize(Rotation * VEC3_FORWARD);
    return forward;
}

glm::vec3 Transform::GetUp() const
{
    glm::vec3 up = glm::normalize(Rotation * VEC3_UP);
    return up;
}

glm::vec3 Transform::GetRight() const
{
    glm::vec3 right = glm::normalize(Rotation * VEC3_RIGHT);
    return right;
}

glm::mat4 Transform::GetWorldMatrix() const
{
    glm::mat4 worldMatrix = glm::identity<glm::mat4>();
    worldMatrix = glm::translate(worldMatrix, Position);
    worldMatrix *= glm::mat4_cast(Rotation);
    worldMatrix = glm::scale(worldMatrix, Scale);
    return worldMatrix;
}

glm::mat4 Transform::GetViewMatrix() const
{
    glm::vec3 forward = GetForward();
    glm::vec3 up = GetUp();
    glm::mat4 view = glm::lookAt(Position, Position + forward, up);
    return view;
}
