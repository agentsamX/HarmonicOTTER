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
	entt::entity m_Card;

	std::vector<syre::Texture> cardTextures;
	
	Shader::sptr flatShader;
	Shader::sptr morphShader;
	bool manualCamera = false;
};