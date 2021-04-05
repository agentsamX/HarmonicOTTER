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
	void SetWins(bool tut, bool b1, bool b2);
	Camera::sptr& GetCam();
private:
	Shader::sptr flatShader;
	entt::entity m_MenuImage;
	entt::entity m_winBadge;
	entt::entity m_MapScreen;
	entt::entity m_CarIcon;
	glm::vec2 menuPos;
	bool map[8][6];
	float menuScale;
	bool m_won1;
	bool m_won2;
	bool m_wonTut;
}; 
