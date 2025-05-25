#pragma once
#include <Cents/Common.h>
#include <Cents/Component/Transform.h>

struct Paddle
{
    Component::Transform Transform;
    float Speed;

    Paddle()
    {
        Transform.Scale = glm::vec3(15.0f, 80.0f, 1.0f);
        Speed = 150.0f;
    }

    glm::vec4 GetBounds()
    {
        glm::vec3 position = Transform.Position;
        glm::vec3 size = Transform.Scale;

        float width = size.x;
        float height = size.y;
        float x = position.x - (width * 0.5f);
        float y = position.y - (height * 0.5f);

        glm::vec4 bounds = glm::vec4(x, y, x + width, y + height);
        return bounds;
    }
};