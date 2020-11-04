#pragma once
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtc/type_ptr.hpp>
namespace syre
{
	class Transform
	{
	public:
		Transform();
		Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca);
		Transform(glm::vec3 pos);
		glm::mat4 GetModelMat();
		glm::vec3 GetPosition();
		void SetPosition(glm::vec3 vecIn);
		glm::vec3 GetRotation();
		void SetRotation(glm::vec3 rotIn);

		glm::vec3 globalPosition;
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotationEuler;
		glm::quat rotation;
		

		Transform* parent = nullptr;

	};
}