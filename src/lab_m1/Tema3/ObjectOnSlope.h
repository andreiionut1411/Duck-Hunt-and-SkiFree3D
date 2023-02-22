#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"
#define PRESENT_TYPE 0
#define ROCK_TYPE 1
#define LIGHT_TYPE 2
#define TREE_TYPE 3
#define BULLET_TYPE 4
#define NORMAL 1
#define POINTS 2
#define CRATE 3
#define SHIELD 4
#define SPEED 5


namespace m1
{
    class ObjectOnSlope {
    public:
        ObjectOnSlope(glm::vec3 position, int type);
        glm::vec3 getPosition();
        int getType();
        glm::vec3 getLightPosition();
        glm::vec3 getSecondLightPosition();
        glm::vec3 getLightColor();
        glm::vec3 getBoundingBox();
        int getTypeOfPresent();
        void setPosition(glm::vec3 position);
    
    private:
        glm::vec3 position;
        int type;
        int typeOfPresent;
        glm::vec3 light_position;
        glm::vec3 second_light_position; // This is only for the spot lights on the slope
        glm::vec3 light_color;
        glm::vec3 boundingBox;
    };
}