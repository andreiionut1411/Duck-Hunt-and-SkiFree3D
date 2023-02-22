#include "lab_m1/Tema3/ObjectOnSlope.h"
#include <random>

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;

#define ANGLE_OF_SLOPE (0.1 * M_PI)

ObjectOnSlope::ObjectOnSlope(glm::vec3 position, int type) {
	this->position = position;
	this->type = type;
	this->typeOfPresent = -1;

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::rotate(modelMatrix, (float)ANGLE_OF_SLOPE, glm::vec3(1, 0, 0));
	if (type == TREE_TYPE) {
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.4, 0));
		light_position = glm::vec3(modelMatrix * glm::vec4(0, 0, 0, 1));
		second_light_position = glm::vec3(0, 0, 0);

		boundingBox = glm::vec3(0.35, 1, 0.18);
	}
	else if (type == PRESENT_TYPE) {
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.2, 0));
		light_position = glm::vec3(modelMatrix * glm::vec4(0, 0, 0, 1));
		second_light_position = glm::vec3(0, 0, 0);

		boundingBox = glm::vec3(0.1, 0, 0.1);

		// There are more types of presents
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> type(1, 5);
		this->typeOfPresent = type(gen);
	}
	else if (type == LIGHT_TYPE) {
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.4, 1.2, 0));
		light_position = glm::vec3(modelMatrix * glm::vec4(0, 0, 0, 1));

		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.8, 0, 0));
		second_light_position = glm::vec3(modelMatrix * glm::vec4(0, 0, 0, 1));

		boundingBox = glm::vec3(0.05, 0, 0.025);
	}
	else if (type == ROCK_TYPE){
		light_position = glm::vec3(0, 0, 0);
		second_light_position = glm::vec3(0, 0, 0);

		boundingBox = glm::vec3(0.3, 0, 0.18);
	}
	else if (type == BULLET_TYPE) {
		light_position = glm::vec3(0, 0, 0);
		second_light_position = glm::vec3(0, 0, 0);
		boundingBox = glm::vec3(0.1, 0, 0.06);
	}
	
	// We generate random colors for the light that comes out of different objects.
	if (type == TREE_TYPE || type == PRESENT_TYPE) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, 255);

		light_color.x = distr(gen) / 255.0;
		light_color.y = distr(gen) / 255.0;
		light_color.z = distr(gen) / 255.0;
	}
	else {
		light_color = glm::vec3(-1, -1, -1);
	}
}

glm::vec3 ObjectOnSlope::getPosition() {
	return position;
}

int ObjectOnSlope::getType() {
	return type;
}

glm::vec3 ObjectOnSlope::getLightPosition() {
	return light_position;
}

glm::vec3 ObjectOnSlope::getSecondLightPosition() {
	return second_light_position;
}

glm::vec3 ObjectOnSlope::getLightColor() {
	return light_color;
}

glm::vec3 ObjectOnSlope::getBoundingBox() {
	return boundingBox;
}

int ObjectOnSlope::getTypeOfPresent() {
	return typeOfPresent;
}

void ObjectOnSlope::setPosition(glm::vec3 position) {
	this->position = position;
}