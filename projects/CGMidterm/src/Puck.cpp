#include "Puck.h"

Puck::Puck(float x, float y)
{
	velocity = glm::vec2(x, y);
}

glm::vec2 Puck::GetVelo()
{
	return glm::vec2(velocity);
}

void Puck::SetVelo(glm::vec2 vecIn)
{
	velocity = vecIn;
}
