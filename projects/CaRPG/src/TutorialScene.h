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
class TutorialScene :
	public syre::SceneParent
{
public:
	TutorialScene(GLFWwindow* inWind);
	void Start();
	int Update();
	int PausedUpdate();
	void ImGUIUpdate();
	int GetID();
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
	entt::entity m_Endbutton;
	entt::entity m_A1;
	entt::entity m_A2;

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
	std::vector<syre::Texture> ActionTextures;

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
	int start = 0;
	float bootToMenu = 0.0f;

	Texture2D::sptr rampTex;

	DirectionalLight Sun;

	int activeCube = 0;

	int shadowWidth = 4096;
	int shadowHeight = 4096;


	float ud = 200.0f;
	float lr = 200.0f;
	float unear = 160.0f;
	float ufar = 160.0f;

	bool inEv = false;
	float evTimer = 0.0f;
	int curEv = 0;
	bool evDone[5] = { false,false,false,false,false };

	syre::Texture Start1 = syre::Texture("images/StartOfRace1.png");
	syre::Texture Start2 = syre::Texture("images/StartOfRace2.png");
	syre::Texture Start3 = syre::Texture("images/StartOfRace3.png");
	syre::Texture Start4 = syre::Texture("images/StartOfRace4.png");
	syre::Texture After1 = syre::Texture("images/AfterFirstTurn1.png");
	syre::Texture After2 = syre::Texture("images/AfterFirstTurn2.png");
	syre::Texture After3 = syre::Texture("images/AfterFirstTurn3.png");
	syre::Texture AfterU1 = syre::Texture("images/AfterUTurn1.png");
	syre::Texture AfterU2 = syre::Texture("images/AfterUTurn2.png");
	syre::Texture Before1 = syre::Texture("images/BeforeChicane.png");
	syre::Texture End1 = syre::Texture("images/EndOfRace.png");

	syre::Texture Racer = syre::Texture("images/SquaredOff.png");
	syre::Texture Winner = syre::Texture("images/Win Screen.png");
	syre::Texture Loser = syre::Texture("images/Lose Screen.png");

};
