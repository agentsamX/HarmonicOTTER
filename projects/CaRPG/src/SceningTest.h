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
	entt::entity Card1;
	entt::entity Card2;
	entt::entity Card3;
	entt::entity Card4;
	entt::entity Card5;
	syre::Texture cardTextures[4] =
	{
		"NO2.png", "Slipstream.png", "Drift.png", "Muffler.png"
	};
	Shader::sptr flatShader;
	Shader::sptr morphShader;
	bool manualCamera = false;
};