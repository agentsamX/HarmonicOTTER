#include "Transform.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/gtx/quaternion.hpp>

syre::Transform::Transform()
{
	globalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

syre::Transform::Transform(glm::vec3 pos, glm::quat rot, glm::vec3 sca)
{
	globalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	position = pos;
	scale = sca;
	rotation = rot;
}

syre::Transform::Transform(glm::vec3 pos)
{
	globalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	position = pos;
	scale = glm::vec3(1.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
}

glm::mat4 syre::Transform::GetModelMat()
{
	return glm::mat4(glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale));
}
