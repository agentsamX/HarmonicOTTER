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
		void UpdateCurPos(glm::vec3 pos);
		void SetCamera(Camera::sptr cam);
		void ListRender(Shader::sptr,syre::Mesh mesh);
		void ListRender(Shader::sptr, syre::Mesh mesh,float deltaTime);
		void ListRender(Shader::sptr,syre::MorphRenderer morph);
		void AddPos(glm::vec3 pos);
		void AddTrans(glm::vec3 pos, glm::vec3 rot);
		void Particalize(float timeE, float timeD);

	private:
		void ParticleUpdate(float deltaTime);
		Camera::sptr camera = nullptr;
		bool useDefaultRot = false;
		glm::vec3 defaultRot = glm::vec3(0.0f, 0.0f, 0.0f);
		bool useDefaultSca = false;
		glm::vec3 defaultScale = glm::vec3(1.0f);
		bool useRelative = false;
		glm::vec3 relativePos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 lastRelative = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 curPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 lastCurPos = glm::vec3(0.0f, 0.0f, 0.0f);
		std::vector<syre::Transform> listTransform;
		std::vector<float>lifeTimes;
		bool particalized = false;
		float emitTimer;
		float timeEmit;
		float timeDegrade; 
	};
}