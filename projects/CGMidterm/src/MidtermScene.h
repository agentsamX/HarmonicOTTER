#pragma once
#include"SceneParent.h"
#include "Puck.h"
class MidtermScene :
	public syre::SceneParent
{
public:
	MidtermScene(GLFWwindow* inWind);
	void Start();
	void Update();
	void ImGUIUpdate();
private:
	void KeyEvents(float delta);
	entt::entity m_Camera;
	entt::entity m_Shader;
	entt::entity puck;
	entt::entity paddleR;
	entt::entity paddleL;
	entt::entity counterL;
	entt::entity counterR;
	entt::entity win;
	float upperBound = -6.f;
	float lowerBound = 2.f;
	float rightBound = -8.f;
	float leftBound = 8.f;
	float puckBaseSpeed = 6.f;
	bool lHit = false;
	bool rHit = false;
	float lHitTime = 0.0f;
	float rHitTime = 0.0f;
	float targRotL = 90.f;
	float targRotR = 90.f;
};