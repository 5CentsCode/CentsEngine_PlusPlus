#pragma once
#include "../Common.h"
#include <glm/gtx/quaternion.hpp>

namespace Component
{
    struct Transform
    {
        glm::vec3 Position = glm::vec3(0.0f);
        glm::quat Rotation = glm::identity<glm::quat>();
        glm::vec3 Scale = glm::vec3(1.0f);

        glm::vec3 GetForward() const;
        glm::vec3 GetUp() const;
        glm::vec3 GetRight() const;

        glm::mat4 GetWorldMatrix() const;
        glm::mat4 GetViewMatrix() const;
    };
}