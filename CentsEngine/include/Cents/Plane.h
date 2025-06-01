#pragma once
#include "Common.h"
#include <glm/gtx/intersect.hpp>
#include "Ray.h"

struct Plane
{
    glm::vec3 Point;
    glm::vec3 Normal;

    bool Raycast(const Ray& ray, OUT float& enter)
    {
        return glm::intersectRayPlane(ray.Origin, ray.Direction, Point, Normal, enter);
    }
};