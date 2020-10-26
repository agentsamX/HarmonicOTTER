#pragma once
#include <GLM/glm.hpp>
namespace syre
{
	class Transform
	{
		Transform();
		~Transform();
		glm::vec3 globalPosition;
		glm::vec3 localPosition;
		
		Transform* parent = nullptr;

	};
}