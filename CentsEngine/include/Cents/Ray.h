#pragma once
#include "Common.h"

struct Ray
{
    glm::vec3 Origin;
    glm::vec3 Direction;

    glm::vec3 GetPoint(float distance) const
    {
        glm::vec3 point = Origin + Direction * distance;
        return point;
    }
};