#pragma once
#include"SceneParent.h"
#include <cstdlib>
#include <ctime>
class MidGameMenu :
	public syre::SceneParent
{
public:
	MidGameMenu(GLFWwindow* inWind);
	void Start();
	int Update();
	void ImGUIUpdate();
	Camera::sptr& GetCam();
private:
	Shader::sptr flatShader;
	entt::entity m_MenuImage;
}; 
