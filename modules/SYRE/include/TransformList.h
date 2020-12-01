#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "MorphRenderer.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>

namespace syre {
	class TransformList
	{
	public:
		TransformList();
		void SetDefaultRot(glm::vec3 rot);
		void SetDefaultSca(glm::vec3 sca);
		void SetRelativePos(glm::vec3 pos);
		void SetCamera(Camera::sptr cam);
		void ListRender(Shader::sptr,syre::Mesh mesh);
		void ListRender(Shader::sptr,syre::MorphRenderer morph);
		void AddPos(glm::vec3 pos);
		void AddTrans(glm::vec3 pos, glm::vec3 rot);
	private:
		Camera::sptr camera = nullptr;
		bool useDefaultRot = false;
		glm::vec3 defaultRot = glm::vec3(0.0f, 0.0f, 0.0f);
		bool useDefaultSca = false;
		glm::vec3 defaultScale = glm::vec3(1.0f);
		bool useRelative = false;
		glm::vec3 relativePos = glm::vec3(0.0f, 0.0f, 0.0f);
		std::vector<syre::Transform> listTransform;
	};
}