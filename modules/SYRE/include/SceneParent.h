#pragma once

#include "entt.hpp"

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