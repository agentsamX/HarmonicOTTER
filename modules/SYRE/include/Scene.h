#pragma once

#include "entt.hpp"

namespace syre {

	class Scene
	{
	public:
		Scene();
		~Scene();
		virtual void Start();
		virtual void Update();
		entt::registry m_Registry;

	private:
	};
}