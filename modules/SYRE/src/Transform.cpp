#include "Transform.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/gtx/quaternion.hpp>

syre::Transform::Transform()
{
	globalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f);
	rotationEuler = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = (glm::quat(glm::radians(rotationEuler)));
}

syre::Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
	globalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	position = pos;
	scale = sca;
	rotationEuler = glm::vec3(rot.x, rot.y, rot.z);
	rotation = (glm::quat(glm::radians(rotationEuler)));
}

syre::Transform::Transform(glm::vec3 pos)
{
	globalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	position = pos;
	scale = glm::vec3(1.0f);
	rotationEuler = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = (glm::quat(glm::radians(rotationEuler)));
}

glm::mat4 syre::Transform::GetModelMat()
{
	return glm::mat4(glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale));
}

glm::vec3 syre::Transform::GetPosition()
{
	return glm::vec3(position);
}

void syre::Transform::SetPosition(glm::vec3 vecIn)
{
	position = vecIn;
}

glm::vec3 syre::Transform::GetRotation()
{
	return glm::vec3(rotationEuler);
}

glm::vec3 syre::Transform::GetScale()
{
	return scale;
}

void syre::Transform::SetRotation(glm::vec3 rotIn)
{
	rotationEuler = rotIn;
	rotation = (glm::quat(glm::radians(rotationEuler)));
}

void syre::Transform::SetRotQuat(glm::quat quatIn)
{
	rotation = quatIn;
}
