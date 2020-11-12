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
	void KeyEvents(float delta);
	entt::entity m_Camera;
	entt::entity m_Shader;
	entt::entity m_PCar;
	entt::entity NO2Card;
	entt::entity SlipstreamCard;
	Shader::sptr flatShader;
};