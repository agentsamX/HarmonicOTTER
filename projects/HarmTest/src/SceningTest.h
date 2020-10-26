#pragma once
#include"SceneParent.h"
class SceningTest:
	public syre::SceneParent
{
public:
	SceningTest(GLFWwindow* inWind);
	void Start();
	void Update();
	void ImGUIUpdate();
private:
	entt::entity m_Camera;
	entt::entity m_Shader;
};