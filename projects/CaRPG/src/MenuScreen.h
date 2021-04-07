#pragma once
#include"SceneParent.h"
#include "AudioEngine.h"
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
	int GetID();
private:
	Shader::sptr flatShader;
	entt::entity m_MenuImage;
	int clickTimes = 0;
};