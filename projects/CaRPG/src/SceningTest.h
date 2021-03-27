#pragma once
#include"SceneParent.h"
#include "AudioEngine.h"
#include "Graphics/Post/CubeCoCoEffect.h"
#include "Graphics/Post/CombinedBloom.h"
#include "Graphics/Post/Blur.h"
#include "Graphics/Post/Pixelate.h"
#include "Graphics/Post/FilmGrain.h"
#include "Graphics/Post/NightVision.h"
#include "Graphics/LUT.h"
#include "Graphics/GBuffer.h"
#include "Graphics/IlluminationBuffer.h"
#include "DirectionalLight.h"
#include <cstdlib>
#include <ctime>
class SceningTest:
	public syre::SceneParent
{
public:
	SceningTest(GLFWwindow* inWind);
	void Start();
	int Update();
	int PausedUpdate();
	void ImGUIUpdate();
	Camera::sptr& GetCam();
private:
	int KeyEvents(float delta);
	Camera::sptr camera;
	entt::entity m_PCar;
	entt::entity m_enemy;
	entt::entity m_Obstacle;
	entt::entity m_Card;
	entt::entity m_Hazard;
	entt::entity m_Gearbox;
	entt::entity m_Gearbox2;
	entt::entity m_Particles1;
	entt::entity m_Particles2;
	entt::entity m_TransparentBlack;
	entt::entity m_PauseMenu;
	entt::entity m_PGears;
	entt::entity m_EGears;
	entt::entity m_HBox;
	entt::entity m_Htex;
	entt::entity m_Hnumber;
	entt::entity m_Pscore;
	entt::entity m_Escore;

	std::vector<syre::Texture> cardTextures;
	std::vector<syre::Texture> hazardTextures;
	std::vector<syre::Texture> gearboxTextures;
	std::vector<syre::Texture> progressBar1;
	std::vector<syre::Texture> progressBar2;
	std::vector<syre::Texture> pGearTextures;
	std::vector<syre::Texture> eGearTextures;
	std::vector<syre::Texture> pneedleTextures;
	std::vector<syre::Texture> eneedleTextures;
	std::vector<syre::Texture> htexTextures;
	std::vector<syre::Texture> hnumberTextures;

	entt::entity sceneBuff;
	entt::entity cocoBuff;
	bool correcting = true;
	entt::entity bloomBuff;
	bool blooming = true;
	entt::entity blurBuff;
	bool blurring = false;
	entt::entity gBuff;
	bool dispG = false;
	bool indivgBuff = false;
	int colTarg = 0;
	entt::entity illumBuff;
	bool dispIllum = false;
	entt::entity shadowBuff;
	entt::entity pixelBuff;
	bool pixelling = true;
	entt::entity grainBuff;
	bool graining = false;
	entt::entity nightVisBuff;
	bool nightVising = false;

	std::vector<LUT3D> cubes;

	Shader::sptr basicShader;
	Shader::sptr flatShader;
	Shader::sptr morphShader;
	//Shader::sptr flatMorphShader;
	Shader::sptr simpleDepthShader;
	bool manualCamera = false;
	float Elapsedtime = 0;
	bool lbutton_down = false;
	bool helptog = true;
	bool speedDemon = true;
	bool showGear = false;
	bool isPaused = false;
	bool escRelease = false;
	bool ambientOn = true;
	bool specularOn = true;
	bool diffuseOn = true;
	bool carLighting = true;
	bool rampOnSpec = false;
	bool rampOnDiff = false;

	Texture2D::sptr rampTex;

	DirectionalLight Sun;

	int activeCube = 0;

	int shadowWidth = 4096;
	int shadowHeight = 4096;


	float ud = 200.0f;
	float lr = 200.0f;
	float unear = 80.0f;
	float ufar = 80.0f;
};