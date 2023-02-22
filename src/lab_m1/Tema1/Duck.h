#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab_m1/Tema1/Geometry.h"


namespace Duck
{
    float generateRandomDuckAngle();
    int generateRandomDuckStartingPosition(int start, int end);
    
    class Duck {
    public:

        const glm::vec3 brown = glm::vec3(0.435, 0.306, 0.216);
        const glm::vec3 darkGreen = glm::vec3(0, 0.392, 0);
        const glm::vec3 yellow = glm::vec3(1, 1, 0);
        int centerOfDuckX, centerOfDuckY;
        const int upperWingX = 40, upperWingY = 20; // Depending on the overall center
        const int lowerWingX = 40, lowerWingY = -20;
        const int headX = 110, headY = 0;
        const int beakX = 150, beakY = -10;
        const int headRadius = 34;
        const int bodySize = 150;
        const int wingSize = 75;
        const int beakSize = 38;
        bool forwardFlap = true;
        float currentAngleWings = 0;
        float duckAngle;
        float duckDirectionX = 0, duckDirectionY = 0;
        bool dead = false;
        bool escape = false;
    };
}