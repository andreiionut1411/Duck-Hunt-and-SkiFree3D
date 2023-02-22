#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace geometry
{
    Mesh* CreateTriangle(const std::string& name, glm::vec3 centerTri, int size, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, int centerCircleX, int circleY, int radius, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color, bool fill = false);
}