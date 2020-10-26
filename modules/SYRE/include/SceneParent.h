#pragma once

#include "entt.hpp"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"

namespace syre {

	class SceneParent
	{
	public:
		SceneParent();
		~SceneParent();
		virtual void Start();
		virtual void Update();
		entt::registry m_Registry;

	private:
	};
}