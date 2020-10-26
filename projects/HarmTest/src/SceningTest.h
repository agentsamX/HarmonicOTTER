#pragma once
#include"SceneParent.h"
class SceningTest:
	public syre::SceneParent
{
	void Start();
	void Update();

private:
	entt::entity m_Camera;
	entt::entity m_Shader;
};