#pragma once
#include"SceneParent.h"
#include <cstdlib>
#include <ctime>
class MenuScreen :
	public syre::SceneParent
{
public:
	MenuScreen(GLFWwindow* inWind);
	void Start();
	int Update();
	void ImGUIUpdate();
	Camera::sptr& GetCam();
private:
	Shader::sptr flatShader;
	entt::entity m_MenuImage;
};