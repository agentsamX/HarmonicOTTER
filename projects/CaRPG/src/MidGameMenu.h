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
	entt::entity m_DoneGame;
	glm::vec2 menuPos;
	glm::vec2 destPos;
	bool map[8][6] = {
		{false,false,false,false,false,false},
		{true,true,true,true,true,true},
		{false,true,false,true,false,false},
		{true,true,true,true,false,false},
		{false,true,false,true,true,true},
		{false,true,false,true,true,false},
		{true,true,true,true,true,false},
		{false,false,false,false,true,false}
	};
	float menuScale;
	bool m_won1;
	bool m_won2;
	bool m_wonTut;
	bool moving = false;
	int curLevel = 1;
	float timer;
	int xPos=0;
	int yPos=0;
	glm::vec2 carPos = glm::vec2(0.137, 0.667);

}; 
