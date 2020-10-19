#pragma once

#include "entt.hpp"

namespace syre {

	class Scene
	{
	public:
		Scene();
		~Scene();
	private:
		entt::registry m_Registry;
	};
}