#pragma once
#include "GLM/glm.hpp"
class Puck {
public:
	Puck(float x, float y);
	glm::vec2 GetVelo();
	void SetVelo(glm::vec2 vecIn);

private:
	glm::vec2 velocity;

};