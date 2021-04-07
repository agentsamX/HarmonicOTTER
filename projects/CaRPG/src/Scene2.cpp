#include "Scene2.h"
#include "Cars.h"
#include "Obstacles.h"


Scene2::Scene2(GLFWwindow* inWind)
{
	window = inWind;
}

void Scene2::Start()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	rampTex = Texture2D::LoadFromFile("images/tinyRamp.png");

	sceneBuff = m_Registry.create();
	cocoBuff = m_Registry.create();
	bloomBuff = m_Registry.create();
	blurBuff = m_Registry.create();
	gBuff = m_Registry.create();
	illumBuff = m_Registry.create();
	shadowBuff = m_Registry.create();
	pixelBuff = m_Registry.create();
	nightVisBuff = m_Registry.create();
	grainBuff = m_Registry.create();

	m_Registry.emplace<PostEffect>(sceneBuff);
	m_Registry.emplace<CubeCoCoEffect>(cocoBuff);
	m_Registry.emplace<CombinedBloom>(bloomBuff);
	m_Registry.emplace<Blur>(blurBuff);
	m_Registry.emplace<GBuffer>(gBuff);
	m_Registry.emplace<IlluminationBuffer>(illumBuff);
	m_Registry.emplace<Framebuffer>(shadowBuff);
	m_Registry.emplace<Pixelate>(pixelBuff);
	m_Registry.emplace<NightVision>(nightVisBuff);
	m_Registry.emplace<FilmGrain>(grainBuff);

	m_Registry.get<PostEffect>(sceneBuff).Init(width, height);
	m_Registry.get<CubeCoCoEffect>(cocoBuff).Init(width, height);
	m_Registry.get<CombinedBloom>(bloomBuff).Init(width, height);
	m_Registry.get<Blur>(blurBuff).Init(width, height);
	m_Registry.get<GBuffer>(gBuff).Init(width, height);
	m_Registry.get<IlluminationBuffer>(illumBuff).Init(width, height);
	m_Registry.get<Framebuffer>(shadowBuff).AddDepthTarget();
	m_Registry.get<Framebuffer>(shadowBuff).Init(shadowWidth, shadowHeight);
	m_Registry.get<Pixelate>(pixelBuff).Init(width, height);
	m_Registry.get<NightVision>(nightVisBuff).Init(width, height);
	m_Registry.get<FilmGrain>(grainBuff).Init(width, height);

	Sun._ambientPow = 0.2;
	Sun._ambientCol = glm::vec4(1.0, 1.0, 1.0, 1.0);
	Sun._lightAmbientPow = 0.2;
	Sun._lightCol = glm::vec4(1.0, 1.0, 1.0, 1.0);
	Sun._lightDirection = glm::vec4(1.370, 2.760, -3.090, 0.0);
	Sun._lightSpecularPow = 0.7;
	Sun._shadowBias = 0.05;

	m_Registry.get<IlluminationBuffer>(illumBuff).SetSun(Sun);

	m_Registry.get<CombinedBloom>(bloomBuff).SetThreshold(0.7);
	m_Registry.get<CombinedBloom>(bloomBuff).SetPasses(10);


	cubes.push_back(LUT3D("cubes/Neutral-512.cube"));
	cubes.push_back(LUT3D("cubes/Cool.cube"));
	cubes.push_back(LUT3D("cubes/Warm.cube"));
	cubes.push_back(LUT3D("cubes/Darken-512.cube"));

	AudioEngine& engine = AudioEngine::Instance();


	//play event
	AudioEvent& oldMusic = engine.GetEvent("Menu Music");
	oldMusic.Stop();

	AudioEvent& newMusic = engine.GetEvent("Ambient");
	newMusic.Play();

	AudioEvent& slipstream = engine.GetEvent("Slipstream");
	AudioEvent& drift = engine.GetEvent("Drift");
	AudioEvent& multiNitro = engine.GetEvent("MultiNitro");

	slipstream.StopImmediately();
	drift.StopImmediately();
	multiNitro.StopImmediately();






	camera = Camera::Create();
	std::string fileName = "monkey.obj";
	entt::entity testModel = m_Registry.create();
	entt::entity shader = m_Registry.create();
	m_PCar = m_Registry.create();
	m_enemy = m_Registry.create();
	m_Obstacle = m_Registry.create();
	entt::entity Track = m_Registry.create();
	m_Hazard = m_Registry.create();
	m_Gearbox = m_Registry.create();
	m_Gearbox2 = m_Registry.create();
	m_PGears = m_Registry.create();
	m_EGears = m_Registry.create();
	m_HBox = m_Registry.create();
	m_Htex = m_Registry.create();
	m_Hnumber = m_Registry.create();
	m_Pscore = m_Registry.create();
	m_Escore = m_Registry.create();
	m_Endbutton = m_Registry.create();
	m_A1 = m_Registry.create();
	m_A2 = m_Registry.create();
	//cards
	m_Card = m_Registry.create();
	m_TransparentBlack = m_Registry.create();
	m_PauseMenu = m_Registry.create();


	/*entt::entity morphTest = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(morphTest);
	m_Registry.emplace<syre::Texture>(morphTest, "Car2.png");
	m_Registry.emplace<syre::Transform>(morphTest, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.get<syre::MorphRenderer>(morphTest).AddFrame("morph01.obj");
	m_Registry.get<syre::MorphRenderer>(morphTest).AddFrame("morph02.obj");
	*/

	//track and scenery
	m_Registry.emplace<syre::Mesh>(Track, "objects/Track2.obj");
	m_Registry.emplace<syre::Transform>(Track, glm::vec3(8.0f, 7.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(Track, "images/PossibleRoad.png");

	m_Registry.emplace<syre::Mesh>(m_Hazard, "objects/RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_Hazard, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Hazard, "images/Apex.png");

	m_Registry.emplace<syre::Mesh>(m_Gearbox, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Gearbox, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Gearbox, "images/GearBoxNeutral.png");

	m_Registry.emplace<syre::Mesh>(m_Gearbox2, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Gearbox2, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Gearbox2, "images/New_Gearbox.png");

	m_Registry.emplace<syre::Mesh>(m_TransparentBlack, "objects/RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_TransparentBlack, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_TransparentBlack, "images/TransparentBlack.png");

	m_Registry.emplace<syre::Mesh>(m_PauseMenu, "objects/RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_PauseMenu, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_PauseMenu, "images/PauseMenu.png");

	m_Registry.emplace<syre::Mesh>(m_PGears, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_PGears, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_PGears, "images/PauseMenu.png");

	m_Registry.emplace<syre::Mesh>(m_EGears, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_EGears, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_EGears, "images/PauseMenu.png");

	m_Registry.emplace<syre::Mesh>(m_HBox, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_HBox, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_HBox, "images/HUD_Info_box.png");

	m_Registry.emplace<syre::Mesh>(m_Htex, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Htex, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Htex, "images/Hairpin_HUD.png");

	m_Registry.emplace<syre::Mesh>(m_Hnumber, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Hnumber, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Hnumber, "images/O1.png");

	m_Registry.emplace<syre::Mesh>(m_Pscore, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Pscore, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Pscore, "images/Progress Bar.png");

	m_Registry.emplace<syre::Mesh>(m_Escore, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Escore, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Escore, "images/Progress Bar.png");

	m_Registry.emplace<syre::Mesh>(m_Endbutton, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Endbutton, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Endbutton, "images/EndTurn.png");

	m_Registry.emplace<syre::Mesh>(m_A1, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_A1, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_A1, "images/EndTurn.png");

	m_Registry.emplace<syre::Mesh>(m_A2, "objects/Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_A2, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_A2, "images/EndTurn.png");

	entt::entity start = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(start);
	m_Registry.emplace<syre::Transform>(start, glm::vec3(15.0f, -50.0f, 0.0f), glm::vec3(90.0f, 0.0f, 190.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(start, "images/START.png");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START1.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START1.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START2.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START3.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START4.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START5.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START6.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START7.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("objects/START8.obj");


	entt::entity finish = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(finish);
	m_Registry.emplace<syre::Transform>(finish, glm::vec3(-270.0f, -135.0f, 0.0f), glm::vec3(90.0f, 0.0f, 150.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(finish, "images/Finish.png");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH1.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH1.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH2.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH3.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH4.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH5.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH6.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH7.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH8.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH9.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH10.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH11.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("objects/FINISH12.obj");




	//trees
	entt::entity trackTrees = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackTrees, "objects/Trees2.obj");
	m_Registry.emplace<syre::Transform>(trackTrees, glm::vec3(8.0f, 7.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackTrees, "images/Tree.png");

	//terrain
	entt::entity trackTerrain = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackTerrain, "objects/Terrain2.obj");
	m_Registry.emplace<syre::Transform>(trackTerrain, glm::vec3(8.0f, 7.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackTerrain, "images/Terrain.png");

	//signs
	entt::entity trackSigns = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackSigns, "objects/Signs2.obj");
	m_Registry.emplace<syre::Transform>(trackSigns, glm::vec3(8.0f, 7.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackSigns, "images/Signs.png");

	//sharp rocks
	entt::entity trackSharpRocks = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackSharpRocks, "objects/Sharp2.obj");
	m_Registry.emplace<syre::Transform>(trackSharpRocks, glm::vec3(8.0f, 7.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackSharpRocks, "images/SharpRock.png");

	//round rocks
	entt::entity trackRoundRocks = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackRoundRocks, "objects/Round2.obj");
	m_Registry.emplace<syre::Transform>(trackRoundRocks, glm::vec3(8.0f, 7.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackRoundRocks, "images/RoundRock.png");

	//flowers
	entt::entity trackFlowers = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackFlowers, "objects/Flowers2.obj");
	m_Registry.emplace<syre::Transform>(trackFlowers, glm::vec3(8.0f, 7.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackFlowers, "images/Flower.png");

	//bush
	entt::entity trackBush = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackBush, "objects/Bush2.obj");
	m_Registry.emplace<syre::Transform>(trackBush, glm::vec3(8.0f, 7.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackBush, "images/Bush.png");

	entt::entity butterflies = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(butterflies);
	m_Registry.get<syre::MorphRenderer>(butterflies).AddFrame("objects/ButterflyNeutral.obj");
	m_Registry.get<syre::MorphRenderer>(butterflies).AddFrame("objects/ButterflyDown.obj");
	m_Registry.get<syre::MorphRenderer>(butterflies).AddFrame("objects/ButterflyNeutral.obj");
	m_Registry.get<syre::MorphRenderer>(butterflies).AddFrame("objects/ButterflyUp.obj");

	m_Registry.emplace<syre::Texture>(butterflies, "images/butterfly.png");
	m_Registry.emplace<syre::TransformList>(butterflies);
	m_Registry.get<syre::TransformList>(butterflies).SetDefaultRot(glm::vec3(90.0f, -70.0f, 180.0f));
	m_Registry.get<syre::TransformList>(butterflies).SetDefaultSca(glm::vec3(0.2f));
	m_Registry.get<syre::TransformList>(butterflies).AddPos(glm::vec3(0.0f, 0.0f, 0.0f));
	m_Registry.get<syre::TransformList>(butterflies).AddPos(glm::vec3(3.0f, -70.0f, 1.0f));
	m_Registry.get<syre::TransformList>(butterflies).AddPos(glm::vec3(35.0f, -97.f, 0.0f));
	m_Registry.get<syre::TransformList>(butterflies).AddPos(glm::vec3(110.0f, -104.f, 0.0f));
	m_Registry.get<syre::TransformList>(butterflies).AddPos(glm::vec3(153.0f, -205.f, 0.0f));

	entt::entity swayingTree = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(swayingTree);
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying1.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying2.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying3.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying4.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying5.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying6.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying7.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying8.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("objects/TreeSwaying9.obj");

	m_Registry.emplace<syre::Texture>(swayingTree, "images/Tree.png");
	m_Registry.emplace<syre::TransformList>(swayingTree);
	m_Registry.get<syre::TransformList>(swayingTree).SetDefaultRot(glm::vec3(90.0f, 0.0f, 0.0f));
	m_Registry.get<syre::TransformList>(swayingTree).SetDefaultSca(glm::vec3(1.0f));
	m_Registry.get<syre::TransformList>(swayingTree).AddPos(glm::vec3(-1.0f, -80.0f, 0.0f));







	m_Registry.emplace<Obstacles>(m_Obstacle);



	m_Registry.emplace<Cars>(m_PCar);
	m_Registry.emplace<syre::Mesh>(m_PCar, "objects/Car2.obj");
	m_Registry.emplace<syre::Transform>(m_PCar, glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(90.f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_PCar, "images/Car2.png");
	m_Registry.emplace<syre::PathAnimator>(m_PCar, syre::PathType::BEZIER);
	auto& carPath = m_Registry.get<syre::PathAnimator>(m_PCar);

	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //start point
	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of first straight
	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(3.0f, -99.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-27.0f, -99.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //end of first turn
	carPath.AddPoint(glm::vec3(-27.0f, -99.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-27.0f, -99.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-97.0f, -99.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str   
	carPath.AddPoint(glm::vec3(-97.0f, -99.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-139.0f, -99.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-139.0f, -129.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //half u   
	carPath.AddPoint(glm::vec3(-139.0f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-137.0f, -194.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 

	carPath.AddPoint(glm::vec3(-97.0f, -184.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //half u   
	carPath.AddPoint(glm::vec3(-97.0f, -184.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-97.0f, -184.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 

	carPath.AddPoint(glm::vec3(-18.0f, -184.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //str   
	carPath.AddPoint(glm::vec3(-18.0f, -184.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(17.0f, -176.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(8.0f, -246.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //turn   
	carPath.AddPoint(glm::vec3(8.0f, -246.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(8.0f, -246.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
							   
	carPath.AddPoint(glm::vec3(8.0f, -350.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //rocks
	carPath.AddPoint(glm::vec3(8.0f, -350.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(15.0f, -390.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-13.0f, -390.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //turn ///
	carPath.AddPoint(glm::vec3(-13.0f, -390.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-13.0f, -390.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-89.0f, -390.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str 
	carPath.AddPoint(glm::vec3(-89.0f, -390.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-143.0f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-133.0f, -350.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //s 
	carPath.AddPoint(glm::vec3(-133.0f, -350.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-125.0f, -303.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-175.0f, -313.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //s
	carPath.AddPoint(glm::vec3(-175.0f, -313.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-175.0f, -313.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 

	carPath.AddPoint(glm::vec3(-250.0f, -313.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //rocks
	carPath.AddPoint(glm::vec3(-250.0f, -313.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-250.0f, -313.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-310.0f, -313.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str
	carPath.AddPoint(glm::vec3(-310.0f, -313.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-350.0f, -313.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-346.0f, -273.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //u
	carPath.AddPoint(glm::vec3(-346.0f, -273.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-350.0f, -232.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-310.0f, -237.f, 0.0f), glm::vec3(90.0f, 0.0f, -270.0f)); //u
	carPath.AddPoint(glm::vec3(-310.0f, -237.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-310.0f, -237.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 

	carPath.AddPoint(glm::vec3(-235.0f, -237.f, 0.0f), glm::vec3(90.0f, 0.0f, -270.0f)); //str
	carPath.AddPoint(glm::vec3(-235.0f, -237.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-197.0f, -233.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-202.0f, -193.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //turn
	carPath.AddPoint(glm::vec3(-202.0f, -193.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-202.0f, -193.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
								  
	carPath.AddPoint(glm::vec3(-202.0f, -60.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //str
	carPath.AddPoint(glm::vec3(-202.0f, -60.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-205.0f, -20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-165.0f, -25.f, 0.0f), glm::vec3(90.0f, 0.0f, -270.0f)); //s
	carPath.AddPoint(glm::vec3(-165.0f, -25.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-118.0f, -30.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-125.0f, 20.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //s
	carPath.AddPoint(glm::vec3(-125.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-125.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-125.0f, 95.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //str
	carPath.AddPoint(glm::vec3(-125.0f, 95.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-120.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-155.0f, 125.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //turn
	carPath.AddPoint(glm::vec3(-155.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-155.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
										 
	carPath.AddPoint(glm::vec3(-230.0f, 125.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str 
	carPath.AddPoint(glm::vec3(-230.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-230.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-300.0f, 125.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //rocks 
	carPath.AddPoint(glm::vec3(-300.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-300.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-365.0f, 125.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str 
	carPath.AddPoint(glm::vec3(-365.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-408.5f, 130.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-408.5f, 95.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //turn 
	carPath.AddPoint(glm::vec3(-408.5f, 95.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-408.5f, 95.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 

	carPath.AddPoint(glm::vec3(-408.5f, 15.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str
	carPath.AddPoint(glm::vec3(-408.5f, 15.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-405.0f, -29.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-375.0f, -24.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //half u
	carPath.AddPoint(glm::vec3(-375.0f, -24.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-320.0f, -32.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-325.0f, 12.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); //end u
	carPath.AddPoint(glm::vec3(-325.0f, 12.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-330.0f, 60.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-285.0f, 56.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //start u
	carPath.AddPoint(glm::vec3(-285.0f, 56.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-245.0f, 55.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-250.0f, 20.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end u
	carPath.AddPoint(glm::vec3(-250.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-250.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
								
	carPath.AddPoint(glm::vec3(-250.0f, -120.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str x2
	carPath.AddPoint(glm::vec3(-250.0f, -120.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-250.0f, -156.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-295.0f, -151.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //turn
	carPath.AddPoint(glm::vec3(-295.0f, -151.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-295.0f, -151.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
										 
	carPath.AddPoint(glm::vec3(-425.0f, -151.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str x2
	carPath.AddPoint(glm::vec3(-425.0f, -151.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-458.0f, -155.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-458.0f, -120.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //turn
	carPath.AddPoint(glm::vec3(-458.0f, -120.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-458.0f, -120.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 

	carPath.AddPoint(glm::vec3(-457.0f, 20.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //str x2
	carPath.AddPoint(glm::vec3(-457.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-450.0f, 57.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-495.0f, 57.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //s
	carPath.AddPoint(glm::vec3(-495.0f, 57.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-536.0f, 50.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-536.0f, 93.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //s
	carPath.AddPoint(glm::vec3(-536.0f, 93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-540.0f, 139.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 

	carPath.AddPoint(glm::vec3(-574.0f, 134.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //start u
	carPath.AddPoint(glm::vec3(-574.0f, 134.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-627.0f, 140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-622.0f, 93.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end u
	carPath.AddPoint(glm::vec3(-622.0f, 93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-622.0f, 93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
								 
	carPath.AddPoint(glm::vec3(-622.0f, 20.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str
	carPath.AddPoint(glm::vec3(-622.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-622.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
								 
	carPath.AddPoint(glm::vec3(-622.0f, -55.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //rocks
	carPath.AddPoint(glm::vec3(-622.0f, -55.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-622.0f, -55.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
									
	carPath.AddPoint(glm::vec3(-622.0f, -105.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str
	carPath.AddPoint(glm::vec3(-622.0f, -105.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-620.0f, -160.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-574.0f, -149.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //s
	carPath.AddPoint(glm::vec3(-574.0f, -149.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-540.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-542.0f, -180.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //s
	carPath.AddPoint(glm::vec3(-542.0f, -180.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-542.0f, -180.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
								  
	carPath.AddPoint(glm::vec3(-542.0f, -300.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str x2
	carPath.AddPoint(glm::vec3(-542.0f, -300.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-542.0f, -300.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.SpeedControl();
	

	m_Registry.emplace<Cars>(m_enemy);
	m_Registry.emplace<syre::Mesh>(m_enemy, "objects/Car2.obj");
	m_Registry.emplace<syre::Transform>(m_enemy, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(90.f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_enemy, "images/Car2-Blue.png");
	m_Registry.emplace<syre::PathAnimator>(m_enemy, syre::PathType::BEZIER);
	auto& enemyCarPath = m_Registry.get<syre::PathAnimator>(m_enemy);

	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //start point
	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(10.0f, -70.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of first straight
	enemyCarPath.AddPoint(glm::vec3(10.0f, -70.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(7.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-27.0f, -103.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //end of first turn
	enemyCarPath.AddPoint(glm::vec3(-27.0f, -103.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-27.0f, -103.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-97.0f, -103.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str   
	enemyCarPath.AddPoint(glm::vec3(-97.0f, -103.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-139.0f, -103.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-135.0f, -129.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //half u   
	enemyCarPath.AddPoint(glm::vec3(-135.0f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-137.0f, -190.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-97.0f, -180.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //half u   
	enemyCarPath.AddPoint(glm::vec3(-97.0f, -180.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-97.0f, -180.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-18.0f, -180.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //str   
	enemyCarPath.AddPoint(glm::vec3(-18.0f, -180.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(20.0f, -172.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(12.0f, -256.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //turn   
	enemyCarPath.AddPoint(glm::vec3(12.0f, -256.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(12.0f, -256.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(12.0f, -350.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //rocks
	enemyCarPath.AddPoint(glm::vec3(12.0f, -350.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(19.0f, -390.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-13.0f, -394.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //turn
	enemyCarPath.AddPoint(glm::vec3(-13.0f, -394.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-13.0f, -394.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); ////////////////
	
	enemyCarPath.AddPoint(glm::vec3(-89.0f, -394.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-89.0f, -394.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-143.0f, -404.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-137.0f, -350.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //s 
	enemyCarPath.AddPoint(glm::vec3(-137.0f, -350.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-125.0f, -303.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-175.0f, -317.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //s
	enemyCarPath.AddPoint(glm::vec3(-175.0f, -317.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-179.0f, -317.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-250.0f, -317.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //rocks
	enemyCarPath.AddPoint(glm::vec3(-250.0f, -317.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-250.0f, -317.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
								   
	enemyCarPath.AddPoint(glm::vec3(-310.0f, -317.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-310.0f, -317.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-350.0f, -317.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-350.0f, -273.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //u
	enemyCarPath.AddPoint(glm::vec3(-350.0f, -273.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-350.0f, -228.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-310.0f, -233.f, 0.0f), glm::vec3(90.0f, 0.0f, -270.0f)); //u
	enemyCarPath.AddPoint(glm::vec3(-310.0f, -233.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-310.0f, -233.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-235.0f, -233.f, 0.0f), glm::vec3(90.0f, 0.0f, -270.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-235.0f, -233.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-197.0f, -229.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-206.0f, -193.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //turn
	enemyCarPath.AddPoint(glm::vec3(-206.0f, -193.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-206.0f, -193.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-206.0f, -60.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //str x2
	enemyCarPath.AddPoint(glm::vec3(-206.0f, -60.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-209.0f, -20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); //////
	
	enemyCarPath.AddPoint(glm::vec3(-165.0f, -21.f, 0.0f), glm::vec3(90.0f, 0.0f, -270.0f)); //s
	enemyCarPath.AddPoint(glm::vec3(-165.0f, -21.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-118.0f, -26.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-129.0f, 20.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //s
	enemyCarPath.AddPoint(glm::vec3(-129.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-129.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-129.0f, 95.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-129.0f, 95.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-124.0f, 125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-155.0f, 121.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //turn
	enemyCarPath.AddPoint(glm::vec3(-155.0f, 121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-155.0f, 121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
								  
	enemyCarPath.AddPoint(glm::vec3(-230.0f, 121.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str 
	enemyCarPath.AddPoint(glm::vec3(-230.0f, 121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-230.0f, 121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
								  
	enemyCarPath.AddPoint(glm::vec3(-300.0f, 121.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //rocks 
	enemyCarPath.AddPoint(glm::vec3(-300.0f, 121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-300.0f, 121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
								  
	enemyCarPath.AddPoint(glm::vec3(-365.0f, 121.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str 
	enemyCarPath.AddPoint(glm::vec3(-365.0f, 121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-408.0f, 126.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-404.5f, 95.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //turn 
	enemyCarPath.AddPoint(glm::vec3(-404.5f, 95.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-404.5f, 95.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						  
	enemyCarPath.AddPoint(glm::vec3(-404.5f, 15.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-404.5f, 15.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-401.f, -29.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-375.0f, -20.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //half u
	enemyCarPath.AddPoint(glm::vec3(-375.0f, -20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-324.0f, -32.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-329.0f, 12.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); //end u
	enemyCarPath.AddPoint(glm::vec3(-329.0f, 12.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-334.0f, 60.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-285.0f, 60.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //start u
	enemyCarPath.AddPoint(glm::vec3(-285.0f, 60.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-241.0f, 55.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-246.0f, 20.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end u
	enemyCarPath.AddPoint(glm::vec3(-246.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-246.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						 
	enemyCarPath.AddPoint(glm::vec3(-246.0f, -120.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str x2
	enemyCarPath.AddPoint(glm::vec3(-246.0f, -120.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-246.0f, -156.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-295.0f, -155.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //turn
	enemyCarPath.AddPoint(glm::vec3(-295.0f, -155.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-295.0f, -155.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-425.0f, -155.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //str x2
	enemyCarPath.AddPoint(glm::vec3(-425.0f, -155.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-458.0f, -159.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-463.0f, -120.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //turn
	enemyCarPath.AddPoint(glm::vec3(-463.0f, -120.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-463.0f, -120.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						 
	enemyCarPath.AddPoint(glm::vec3(-463.0f, 20.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //str x2
	enemyCarPath.AddPoint(glm::vec3(-463.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-454.0f, 57.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-495.0f, 53.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //s
	enemyCarPath.AddPoint(glm::vec3(-495.0f, 53.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-540.0f, 50.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-540.0f, 93.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //s
	enemyCarPath.AddPoint(glm::vec3(-540.0f, 93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-540.0f, 135.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-574.0f, 130.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //start u
	enemyCarPath.AddPoint(glm::vec3(-574.0f, 130.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-623.0f, 140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-618.0f, 93.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end u
	enemyCarPath.AddPoint(glm::vec3(-618.0f, 93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-618.0f, 93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						 
	enemyCarPath.AddPoint(glm::vec3(-618.0f, 20.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-618.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-618.0f, 20.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						 
	enemyCarPath.AddPoint(glm::vec3(-618.0f, -55.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //rocks
	enemyCarPath.AddPoint(glm::vec3(-618.0f, -55.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-618.0f, -55.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						 
	enemyCarPath.AddPoint(glm::vec3(-618.0f, -105.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-618.0f, -105.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-616.0f, -160.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-574.0f, -145.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //s
	enemyCarPath.AddPoint(glm::vec3(-574.0f, -145.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-536.0f, -14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.AddPoint(glm::vec3(-538.0f, -180.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //s
	enemyCarPath.AddPoint(glm::vec3(-538.0f, -180.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-538.0f, -180.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
						 
	enemyCarPath.AddPoint(glm::vec3(-538.0f, -300.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //str x2
	enemyCarPath.AddPoint(glm::vec3(-538.0f, -300.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-538.0f, -300.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.SpeedControl();
	
	//cards

	m_Registry.emplace<syre::Mesh>(m_Card, "objects/Card.obj");
	m_Registry.emplace<syre::Transform>(m_Card, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2f));
	m_Registry.emplace<syre::Texture>(m_Card, "images/NO2.png");



	cardTextures.push_back(syre::Texture("images/NO2.png"));
	cardTextures.push_back(syre::Texture("images/Drift.png"));
	cardTextures.push_back(syre::Texture("images/Slipstream.png"));
	cardTextures.push_back(syre::Texture("images/EBrake.png"));
	cardTextures.push_back(syre::Texture("images/QuickShiftN.png"));
	cardTextures.push_back(syre::Texture("images/Sabotage.png"));

	hazardTextures.push_back(syre::Texture("images/Apex.png"));
	hazardTextures.push_back(syre::Texture("images/Hairpin.png"));
	hazardTextures.push_back(syre::Texture("images/Chicane.png"));
	hazardTextures.push_back(syre::Texture("images/Rocks.png"));

	gearboxTextures.push_back(syre::Texture("images/Pedals_Neutral.png"));
	gearboxTextures.push_back(syre::Texture("images/Pedals_Gas.png"));
	gearboxTextures.push_back(syre::Texture("images/Pedals_Brake.png"));

	//accelerometerTexture.push_back(syre::Texture("Accelerometer.png"));

	pGearTextures.push_back(syre::Texture("images/P1.png"));
	pGearTextures.push_back(syre::Texture("images/P1.png"));
	pGearTextures.push_back(syre::Texture("images/P2.png"));
	pGearTextures.push_back(syre::Texture("images/P3.png"));
	pGearTextures.push_back(syre::Texture("images/P4.png"));
	pGearTextures.push_back(syre::Texture("images/P5.png"));
	pGearTextures.push_back(syre::Texture("images/P6.png"));

	eGearTextures.push_back(syre::Texture("images/E1.png"));
	eGearTextures.push_back(syre::Texture("images/E1.png"));
	eGearTextures.push_back(syre::Texture("images/E2.png"));
	eGearTextures.push_back(syre::Texture("images/E3.png"));
	eGearTextures.push_back(syre::Texture("images/E4.png"));
	eGearTextures.push_back(syre::Texture("images/E5.png"));
	eGearTextures.push_back(syre::Texture("images/E6.png"));

	eneedleTextures.push_back(syre::Texture("images/Eneedle1.png"));
	eneedleTextures.push_back(syre::Texture("images/Eneedle1.png"));
	eneedleTextures.push_back(syre::Texture("images/Eneedle2.png"));
	eneedleTextures.push_back(syre::Texture("images/Eneedle3.png"));
	eneedleTextures.push_back(syre::Texture("images/Eneedle4.png"));
	eneedleTextures.push_back(syre::Texture("images/Eneedle5.png"));
	eneedleTextures.push_back(syre::Texture("images/Eneedle6.png"));

	pneedleTextures.push_back(syre::Texture("images/Pneedle1.png"));
	pneedleTextures.push_back(syre::Texture("images/Pneedle1.png"));
	pneedleTextures.push_back(syre::Texture("images/Pneedle2.png"));
	pneedleTextures.push_back(syre::Texture("images/Pneedle3.png"));
	pneedleTextures.push_back(syre::Texture("images/Pneedle4.png"));
	pneedleTextures.push_back(syre::Texture("images/Pneedle5.png"));
	pneedleTextures.push_back(syre::Texture("images/Pneedle6.png"));

	hnumberTextures.push_back(syre::Texture("images/O1.png"));
	hnumberTextures.push_back(syre::Texture("images/O1.png"));
	hnumberTextures.push_back(syre::Texture("images/O2.png"));
	hnumberTextures.push_back(syre::Texture("images/O3.png"));
	hnumberTextures.push_back(syre::Texture("images/O4.png"));
	hnumberTextures.push_back(syre::Texture("images/O5.png"));
	hnumberTextures.push_back(syre::Texture("images/O6.png"));

	htexTextures.push_back(syre::Texture("images/Apex_HUD.png"));
	htexTextures.push_back(syre::Texture("images/Hairpin_HUD.png"));
	htexTextures.push_back(syre::Texture("images/Chicane_HUD.png"));
	htexTextures.push_back(syre::Texture("images/Rocks_HUD.png"));

	progressBar1.push_back(syre::Texture("images/Progress Bar Top.png"));
	progressBar1.push_back(syre::Texture("images/Red1.png"));
	progressBar1.push_back(syre::Texture("images/Red2.png"));
	progressBar1.push_back(syre::Texture("images/Red3.png"));
	progressBar1.push_back(syre::Texture("images/Red4.png"));
	progressBar1.push_back(syre::Texture("images/Red5.png"));
	progressBar1.push_back(syre::Texture("images/Red6.png"));
	progressBar1.push_back(syre::Texture("images/Red7.png"));
	progressBar1.push_back(syre::Texture("images/Red8.png"));

	progressBar2.push_back(syre::Texture("images/Progress Bar Bottom.png"));
	progressBar2.push_back(syre::Texture("images/Blue1.png"));
	progressBar2.push_back(syre::Texture("images/Blue1.png"));
	progressBar2.push_back(syre::Texture("images/Blue1.png"));
	progressBar2.push_back(syre::Texture("images/Blue1.png"));
	progressBar2.push_back(syre::Texture("images/Blue1.png"));
	progressBar2.push_back(syre::Texture("images/Blue1.png"));
	progressBar2.push_back(syre::Texture("images/Blue1.png"));
	progressBar2.push_back(syre::Texture("images/Blue1.png"));

	ActionTextures.push_back(syre::Texture("images/A1.png"));
	ActionTextures.push_back(syre::Texture("images/A2.png"));
	ActionTextures.push_back(syre::Texture("images/A3.png"));
	ActionTextures.push_back(syre::Texture("images/A4.png"));

	flatShader = Shader::Create();
	flatShader->LoadShaderPartFromFile("flatVert.glsl", GL_VERTEX_SHADER);
	flatShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatShader->Link();






	basicShader = Shader::Create();
	basicShader->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	basicShader->LoadShaderPartFromFile("shaders/gBuffer_pass_frag.glsl", GL_FRAGMENT_SHADER);
	basicShader->Link();

	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	float     lightAmbientPow = 0.1f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.5f;
	float     shininess = 4.0f;
	// These are our application / scene level uniforms that don't necessarily update
	// every frame
	basicShader->SetUniform("u_LightPos", lightPos);
	basicShader->SetUniform("u_LightCol", lightCol);
	basicShader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	basicShader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	basicShader->SetUniform("u_AmbientCol", ambientCol);
	basicShader->SetUniform("u_AmbientStrength", ambientPow);
	basicShader->SetUniform("u_Shininess", shininess);


	morphShader = Shader::Create();
	morphShader->LoadShaderPartFromFile("morph_vertex_shader.glsl", GL_VERTEX_SHADER);
	morphShader->LoadShaderPartFromFile("gfrag_shader.glsl", GL_FRAGMENT_SHADER);
	morphShader->Link();

	lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
	lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	lightAmbientPow = 0.1f;
	lightSpecularPow = 1.0f;
	ambientCol = glm::vec3(1.0f);
	ambientPow = 0.5f;
	shininess = 4.0f;
	// These are our application / scene level uniforms that don't necessarily update
	// every frame
	morphShader->SetUniform("u_LightPos", lightPos);
	morphShader->SetUniform("u_LightCol", lightCol);
	morphShader->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	morphShader->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	morphShader->SetUniform("u_AmbientCol", ambientCol);
	morphShader->SetUniform("u_AmbientStrength", ambientPow);
	morphShader->SetUniform("u_Shininess", shininess);


	/*flatMorphShader = Shader::Create();
	flatMorphShader->LoadShaderPartFromFile("flatMorphVert.glsl", GL_VERTEX_SHADER);
	flatMorphShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatMorphShader->Link();*/

	simpleDepthShader = Shader::Create();
	simpleDepthShader->LoadShaderPartFromFile("shaders/simple_depth_vert.glsl", GL_VERTEX_SHADER);
	simpleDepthShader->LoadShaderPartFromFile("shaders/simple_depth_frag.glsl", GL_FRAGMENT_SHADER);
	simpleDepthShader->Link();


	auto& camComponent = camera;
	camComponent->SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camComponent->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camComponent->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camComponent->SetFovDegrees(100.0f); // Set an initial FOV

	auto& obstacleComponent = m_Registry.get<Obstacles>(m_Obstacle);
	/*
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(3);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(3);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(2);
	*/
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(3);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(3);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(3);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(2);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(3);
	obstacleComponent.Adddeck(0);
	obstacleComponent.Adddeck(1);
	obstacleComponent.Adddeck(0);

	auto listView = m_Registry.view<syre::TransformList>();
	for (auto entity : listView)
	{
		m_Registry.get<syre::TransformList>(entity).SetCamera(camera);
	}
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
	PlayerComponent.Shuffle();

	lastFrame = glfwGetTime();
}

int Scene2::Update()
{
	PostEffect* framebuffer = &m_Registry.get<PostEffect>(sceneBuff);
	CubeCoCoEffect* colorCorrect = &m_Registry.get<CubeCoCoEffect>(cocoBuff);
	CombinedBloom* bloom = &m_Registry.get<CombinedBloom>(bloomBuff);
	Blur* blur = &m_Registry.get<Blur>(blurBuff);
	GBuffer* g = &m_Registry.get<GBuffer>(gBuff);
	IlluminationBuffer* illum = &m_Registry.get<IlluminationBuffer>(illumBuff);
	Framebuffer* shadow = &m_Registry.get<Framebuffer>(shadowBuff);
	Pixelate* pixel = &m_Registry.get<Pixelate>(pixelBuff);
	NightVision* vision = &m_Registry.get<NightVision>(nightVisBuff);
	FilmGrain* grain = &m_Registry.get<FilmGrain>(grainBuff);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	framebuffer->Clear();
	colorCorrect->Clear();
	bloom->Clear();
	blur->Clear();
	g->Clear();
	shadow->Clear();
	illum->Clear();
	pixel->Clear();
	vision->Clear();
	grain->Clear();

	AudioEngine& engine = AudioEngine::Instance();

	AudioEvent& ambient = engine.GetEvent("Ambient");
	AudioBus& musicBus = engine.GetBus("Music");


	//get ref listener
	AudioListener& listener = engine.GetListener();
	listener.SetPosition(glm::vec3(5, 0, 0));

	engine.Update();

	if (isPaused)
	{
		return PausedUpdate();
	}
	thisFrame = glfwGetTime();
	float deltaTime = thisFrame - lastFrame;
	auto& camComponent = camera;
	auto& obstacleComponent = m_Registry.get<Obstacles>(m_Obstacle);
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
	auto& EnemyComponent = m_Registry.get<Cars>(m_enemy);
	int temp = 0;
	bool done = false;
	bool Pemp = false;
	bool Eemp = false;
	if (start == 0)
	{
		start += 1;
		obstacleComponent.Draw();
	}
	glm::vec3 camX = glm::cross(camComponent->GetForward(), camComponent->GetUp());
	KeyEvents(deltaTime);
	flatShader->Bind();
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.115f)));
	flatShader->SetUniform("aspect", camera->GetAspect());
	for (int i = 0; i <= 4; i++)
	{
		int cardVal = PlayerComponent.GetCard(i, true);
		if (cardVal != -1 && PlayerComponent.GetPosition1() == i || PlayerComponent.GetPosition2() == i && cardVal != -1)
		{
			flatShader->SetUniform("offset", glm::vec2(-0.1f + i / 4.2f, -.42f));

			cardTextures[cardVal].Bind();
			m_Registry.get<syre::Mesh>(m_Card).Render();
		}
		else if (cardVal != -1)
		{
			flatShader->SetUniform("offset", glm::vec2(-0.1f + i / 4.2f, -.66f));

			cardTextures[cardVal].Bind();
			m_Registry.get<syre::Mesh>(m_Card).Render();
		}
	}

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.12f, 0.06f, 0.004f)));
	flatShader->SetUniform("offset", glm::vec2(-0.5, -0.8f));
	m_Registry.get<syre::Texture>(m_Endbutton).Bind();
	m_Registry.get<syre::Mesh>(m_Endbutton).Render();

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.09f)));
	flatShader->SetUniform("offset", glm::vec2(0.90, 0.8f));
	int ObsVal = obstacleComponent.GetObs();
	hazardTextures[ObsVal].Bind();
	m_Registry.get<syre::Mesh>(m_Hazard).Render();

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
	flatShader->SetUniform("offset", glm::vec2(-0.87, -0.62f));
	int GerValP = PlayerComponent.GetGear();
	pGearTextures[GerValP].Bind();
	m_Registry.get<syre::Mesh>(m_PGears).Render();

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
	flatShader->SetUniform("offset", glm::vec2(-0.87, -0.62f));
	int GerValE = EnemyComponent.GetGear();
	eGearTextures[GerValE].Bind();
	m_Registry.get<syre::Mesh>(m_EGears).Render();

	int pos1 = PlayerComponent.GetPosition1();
	int pos2 = PlayerComponent.GetPosition2();

	if (pos1 != -1)
	{
		//flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.55, -0.60));
		ActionTextures[1].Bind();
		m_Registry.get<syre::Mesh>(m_A1).Render();
	}
	else if (pos1 == -1)
	{
		//flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.55, -0.60));
		ActionTextures[0].Bind();
		m_Registry.get<syre::Mesh>(m_A1).Render();
	}

	if (pos2 != -1)
	{
		//flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.45, -0.60));
		ActionTextures[3].Bind();
		m_Registry.get<syre::Mesh>(m_A2).Render();
	}
	else if (pos2 == -1)
	{
		//flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.45, -0.60));
		ActionTextures[2].Bind();
		m_Registry.get<syre::Mesh>(m_A2).Render();
	}

	if (helptog == true)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.28f, 0.1f, 1.0f)));
		flatShader->SetUniform("offset", glm::vec2(0.57, 0.7f));
		int obs = obstacleComponent.GetObs();
		htexTextures[obs].Bind();
		m_Registry.get<syre::Mesh>(m_Htex).Render();

		if (obstacleComponent.GetObs() != 3)
		{
			flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.28f, 0.1f, 1.0f)));
			flatShader->SetUniform("offset", glm::vec2(0.54, 0.7f));
			int value = obstacleComponent.GetValue();
			hnumberTextures[value].Bind();
			m_Registry.get<syre::Mesh>(m_Hnumber).Render();
		}

		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.1f, 1.0f)));
		flatShader->SetUniform("offset", glm::vec2(0.55, 0.7f));
		m_Registry.get<syre::Texture>(m_HBox).Bind();
		m_Registry.get<syre::Mesh>(m_HBox).Render();
	}

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
	flatShader->SetUniform("offset", glm::vec2(-0.87, -0.62f));
	m_Registry.get<syre::Texture>(m_Gearbox2).Bind();
	m_Registry.get<syre::Mesh>(m_Gearbox2).Render();


	if (PlayerComponent.GetBrk() == false && PlayerComponent.GetAcc() == false)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.87, -0.75f));
		gearboxTextures[0].Bind();
		m_Registry.get<syre::Mesh>(m_Gearbox).Render();
	}
	else if (PlayerComponent.GetBrk() == true)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.87, -0.75f));
		gearboxTextures[2].Bind();
		m_Registry.get<syre::Mesh>(m_Gearbox).Render();
	}
	else if (PlayerComponent.GetAcc() == true)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.87, -0.75f));
		gearboxTextures[1].Bind();
		m_Registry.get<syre::Mesh>(m_Gearbox).Render();
	}

	for (int i = 0; i < 8; i++)
	{
		if (PlayerComponent.GetScore() > floor((obstacleComponent.GetSize() / 8) * i) && PlayerComponent.GetScore() <= floor((obstacleComponent.GetSize() / 8) * (i + 1)))
		{
			flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.1f, 0.004f)));
			flatShader->SetUniform("offset", glm::vec2(-0.6, 0.85f));
			progressBar1[i].Bind();
			m_Registry.get<syre::Mesh>(m_Pscore).Render();
		}
		else if (PlayerComponent.GetScore() < floor((obstacleComponent.GetSize() / 8) * i))
		{
			flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.1f, 0.004f)));
			flatShader->SetUniform("offset", glm::vec2(-0.6, 0.85f));
			progressBar1[0].Bind();
			m_Registry.get<syre::Mesh>(m_Pscore).Render();
		}

		if (EnemyComponent.GetScore() > floor((obstacleComponent.GetSize() / 8) * i) && EnemyComponent.GetScore() <= floor((obstacleComponent.GetSize() / 8) * (i + 1)))
		{
			flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.1f, 0.004f)));
			flatShader->SetUniform("offset", glm::vec2(-0.6, 0.85f));
			progressBar2[i].Bind();
			m_Registry.get<syre::Mesh>(m_Escore).Render();
		}
		else if (EnemyComponent.GetScore() < floor((obstacleComponent.GetSize() / 8) * i))
		{
			flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.1f, 0.004f)));
			flatShader->SetUniform("offset", glm::vec2(-0.6, 0.85f));
			progressBar2[0].Bind();
			m_Registry.get<syre::Mesh>(m_Pscore).Render();
		}
	}

	if (m_Registry.get<syre::PathAnimator>(m_PCar).HitMax() || m_Registry.get<syre::PathAnimator>(m_enemy).HitMax())
	{
		m_Registry.get<syre::PathAnimator>(m_PCar).Stop();
		m_Registry.get<syre::PathAnimator>(m_enemy).Stop();
		deltaTime = deltaTime / 8.0f;
	}
	else if (!(m_Registry.get<syre::PathAnimator>(m_PCar).HitMax() && m_Registry.get<syre::PathAnimator>(m_enemy).HitMax()))
	{
		m_Registry.get<syre::PathAnimator>(m_PCar).Resume();
		m_Registry.get<syre::PathAnimator>(m_enemy).Resume();
	}
	if (obstacleComponent.GetEnd() != true)
	{
		if (EnemyComponent.GetSabo() == false && EnemyComponent.GetEnded() == false)
		{
			EnemyComponent.SetOppGear(PlayerComponent.GetGear());
			if (obstacleComponent.GetObs() == 0)
			{
				if (abs(PlayerComponent.GetGear() - obstacleComponent.GetValue()) <= 2)
				{
					for (int i; i <= 5; i++)
					{
						if (EnemyComponent.GetCard(i, true) == 2)
						{
							EnemyComponent.PlayCard(i, 0);
							break;
						}
					}
				}
				if (EnemyComponent.GetGear() + 3 <= 8)
				{
					for (int i; i <= 5; i++)
					{
						if (EnemyComponent.GetCard(i, true) == 0)
						{
							EnemyComponent.PlayCard(i, 0);
							break;
						}
					}
				}
				else if (EnemyComponent.GetPosition1() == -1 || EnemyComponent.GetPosition2() == -1)
				{
					EnemyComponent.SetAcc();
				}
			}

			if (obstacleComponent.GetObs() == 1 || obstacleComponent.GetObs() == 2)
			{
				if (abs(PlayerComponent.GetGear() - obstacleComponent.GetValue()) <= 2)
				{
					for (int i; i <= 5; i++)
					{
						if (EnemyComponent.GetCard(i, true) == 2)
						{
							EnemyComponent.PlayCard(i, 0);
							break;
						}
					}
				}
				else if (abs(obstacleComponent.GetValue() - EnemyComponent.GetGear()) <= 3 && EnemyComponent.GetGear() < obstacleComponent.GetValue())
				{
					for (int i; i <= 5; i++)
					{
						if (EnemyComponent.GetCard(i, true) == 1)
						{
							EnemyComponent.PlayCard(i, 0);
							break;
						}
					}
				}
				else if (EnemyComponent.GetPosition1() == -1 && EnemyComponent.GetGear() < obstacleComponent.GetValue() && EnemyComponent.GetPosition2() == -1 && EnemyComponent.GetGear() < obstacleComponent.GetValue())
				{
					EnemyComponent.SetAcc();
				}
				else if (EnemyComponent.GetPosition1() == -1 && EnemyComponent.GetGear() > obstacleComponent.GetValue() && EnemyComponent.GetPosition2() == -1 && EnemyComponent.GetGear() > obstacleComponent.GetValue())
				{
					EnemyComponent.SetBrk();
				}
			}

			if (obstacleComponent.GetObs() == 3)
			{
				if (abs(PlayerComponent.GetGear() - obstacleComponent.GetValue()) <= 2)
				{
					for (int i; i <= 5; i++)
					{
						if (EnemyComponent.GetCard(i, true) == 2)
						{
							EnemyComponent.PlayCard(i, 0);
							break;
						}
					}
				}

				if (abs(1 - obstacleComponent.GetValue()) == 0 || abs(1 - obstacleComponent.GetValue()) <= 2)
				{
					for (int i; i <= 5; i++)
					{
						if (EnemyComponent.GetCard(i, true) == 3)
						{
							EnemyComponent.PlayCard(i, 0);
							break;
						}
					}
				}

				if (EnemyComponent.GetPosition1() == -1 && EnemyComponent.GetGear() < PlayerComponent.GetGear() || EnemyComponent.GetPosition2() == -1 && EnemyComponent.GetGear() < PlayerComponent.GetGear())
				{
					EnemyComponent.SetBrk();
				}
			}

			if (EnemyComponent.GetPosition1() != -1 && EnemyComponent.GetPosition1() != -2 && EnemyComponent.GetPosition1() != -3)
			{
				if (EnemyComponent.GetCard(EnemyComponent.GetPosition1(), true) == 2)
				{
					PlayerComponent.ChangeGears(EnemyComponent.GetGear());
				}
				else if (EnemyComponent.GetCard(EnemyComponent.GetPosition1(), true) == 5)
				{
					PlayerComponent.SetSabo();
				}
			}

			if (EnemyComponent.GetPosition2() != -1 && EnemyComponent.GetPosition2() != -2 && EnemyComponent.GetPosition2() != -3)
			{
				if (EnemyComponent.GetCard(EnemyComponent.GetPosition2(), true) == 2)
				{
					PlayerComponent.ChangeGears(EnemyComponent.GetGear());
				}
				else if (EnemyComponent.GetCard(EnemyComponent.GetPosition2(), true) == 5)
				{
					PlayerComponent.SetSabo();
				}
			}
			EnemyComponent.ResolveCards();
			PlayerComponent.SetOppGear(EnemyComponent.GetGear());
		}
		/*
		if (EnemyComponent.GetSabo() == false && EnemyComponent.GetEnded() == false)
		{
			if (speedDemon == true)
			{
				for (int i = 0; i <= 5; i++)
				{
					if (EnemyComponent.GetCard(i, true) == 0)
					{
						EnemyComponent.PlayCard(i, 0);
						break;
					}
				}
				if (EnemyComponent.GetPosition1() == -1 || EnemyComponent.GetPosition2() == -1)
				{
					EnemyComponent.SetAcc();
				}
				if (EnemyComponent.GetGear() == 6)
				{
					speedDemon = false;
				}
			}
			else if (speedDemon == false)
			{
				if (EnemyComponent.GetGear() - 1 <= 1)
				{
					speedDemon = true;
				}
				EnemyComponent.SetBrk();

			}
			EnemyComponent.ResolveCards();
			PlayerComponent.SetOppGear(EnemyComponent.GetGear());
		}
		*/
		/*
	if (showGear == false)
	{
		showGear = true;
		printf("The enemy's gear level is : ");
		printf("%i", EnemyComponent.GetGear());
		printf("\n");
		printf("\n");
	}
	*/
		if (PlayerComponent.GetEnded() == true)
		{
			/// harry i changed the bit below, what did it do lol
			for (int i = 0; i <= 5; i++)
			{
				if (PlayerComponent.GetCard(i, true) == -1)
				{
					temp += 1;
				}
				if (temp == 6)//changed from = to ==
				{
					Pemp = true;
					temp = 0;
				}
			}
			for (int i = 0; i <= 5; i++)
			{
				if (EnemyComponent.GetCard(i, true) == -1)
				{
					temp += 1;
				}
				if (temp == 6)//changed from = to ==
				{
					Eemp = true;
					temp = 0;
				}
			}
			if (obstacleComponent.GetObs() != 2)
			{
				if (obstacleComponent.Resolve(PlayerComponent.GetGear(), EnemyComponent.GetGear()) == 1)
				{
					PlayerComponent.IncreaseScore();
					m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(0.25, true);
					m_Registry.get<syre::PathAnimator>(m_enemy).SetSpeed(0.25, false);
					if (obstacleComponent.GetObs() == 3)
					{
						if (Eemp != true)
						{
							while (done != true)
							{
								srand((unsigned)time(0));
								temp = (rand() % 5);
								if (EnemyComponent.GetCard(temp, true) != -1)
								{
									EnemyComponent.RemoveCard(temp, true);
									break;
								}
							}
						}
					}
				}
				else
				{
					EnemyComponent.IncreaseScore();
					m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(0.25, false);
					m_Registry.get<syre::PathAnimator>(m_enemy).SetSpeed(0.25, true);
					if (obstacleComponent.GetObs() == 3)
					{
						if (Pemp != true)
						{
							while (done != true)
							{
								srand((unsigned)time(0));
								temp = (rand() % 5);

								if (PlayerComponent.GetCard(temp, true) != -1)
								{
									PlayerComponent.RemoveCard(temp, true);
									break;
								}
							}
						}
					}
				}
			}
			if (EnemyComponent.GetCard(EnemyComponent.GetPosition1(), true) == 1 || EnemyComponent.GetCard(EnemyComponent.GetPosition2(), true) == 1)
			{
				temp = EnemyComponent.GetGear();
				EnemyComponent.ChangeGears(PlayerComponent.GetGear());
				PlayerComponent.ChangeGears(temp);
			}
			if (PlayerComponent.GetCard(PlayerComponent.GetPosition1(), true) == 1 || PlayerComponent.GetCard(PlayerComponent.GetPosition1(), true) == 1)
			{
				temp = PlayerComponent.GetGear();
				PlayerComponent.ChangeGears(EnemyComponent.GetGear());
				EnemyComponent.ChangeGears(temp);
			}
			if (obstacleComponent.GetObs() == 2)
			{
				if (obstacleComponent.GetP1wins() + obstacleComponent.GetP2wins() > 0)
				{
					if (obstacleComponent.Resolve(PlayerComponent.GetGear(), EnemyComponent.GetGear()) == true)
					{
						PlayerComponent.IncreaseScore();
						m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(0.25, true);
						m_Registry.get<syre::PathAnimator>(m_enemy).SetSpeed(0.25, false);
					}
					else
					{
						EnemyComponent.IncreaseScore();
						m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(0.25, false);
						m_Registry.get<syre::PathAnimator>(m_enemy).SetSpeed(0.25, true);
					}
				}
				else
				{
					obstacleComponent.Resolve(PlayerComponent.GetGear(), EnemyComponent.GetGear());
				}
			}
			if (obstacleComponent.GetObs() != 2 && obstacleComponent.GetObs() != 3)
			{
				m_Registry.get<syre::PathAnimator>(m_PCar).IncrementSegment(2);
				m_Registry.get<syre::PathAnimator>(m_enemy).IncrementSegment(2);
			}
			else
			{
				m_Registry.get<syre::PathAnimator>(m_PCar).IncrementSegment(1);
				m_Registry.get<syre::PathAnimator>(m_enemy).IncrementSegment(1);
			}
			PlayerComponent.ResetTurn();
			EnemyComponent.ResetTurn();
			obstacleComponent.Draw();
			showGear = false;
			if (obstacleComponent.GetObs() == 2)
			{
				PlayerComponent.SetPosition(-6);
				EnemyComponent.SetPosition(-6);
			}
			if (EnemyComponent.GetSabo() == true)
			{
				EnemyComponent.ChangeGears(1);
			}
		}
	}
	else
	{
		m_Registry.get<syre::PathAnimator>(m_PCar).IncrementSegment(2);//needs changed
		m_Registry.get<syre::PathAnimator>(m_enemy).IncrementSegment(2);//needs changed
		if (PlayerComponent.GetScore() >= EnemyComponent.GetScore())
		{
			flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.4f)));
			flatShader->SetUniform("offset", glm::vec2(0.0f, 0.4f));
			flatShader->SetUniform("aspect", 0.4f);
			Winner.Bind();
			m_Registry.get<syre::Mesh>(m_Hazard).Render();

			m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(1.0, true);
			m_Registry.get<syre::PathAnimator>(m_enemy).SetSpeed(1.0, false);
			if (m_Registry.get<syre::PathAnimator>(m_PCar).GetHardStop())
			{
				//game is finished finished
				m_Registry.get<syre::PathAnimator>(m_enemy).Stop();
				//this is where we could go to next level
				won = true;
				bootToMenu += deltaTime;
				if (bootToMenu > 7.0f)
				{
					return -1;
				}
			}
		}
		else if (PlayerComponent.GetScore() < EnemyComponent.GetScore())
		{
			flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.4f)));
			flatShader->SetUniform("offset", glm::vec2(0.0f, 0.4f));
			flatShader->SetUniform("aspect", 0.4f);
			Loser.Bind();
			m_Registry.get<syre::Mesh>(m_Hazard).Render();
			m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(1.0, false);
			m_Registry.get<syre::PathAnimator>(m_enemy).SetSpeed(1.0, true);
			bootToMenu += deltaTime;
			if (bootToMenu > 7.0f)
			{
				return -1;
			}
		}
	}
	auto pathView = m_Registry.view<syre::PathAnimator, syre::Transform>();
	for (auto entity : pathView)
	{
		auto& transform = m_Registry.get<syre::Transform>(entity);
		m_Registry.get<syre::PathAnimator>(entity).Update(transform, deltaTime);
	}
	flatShader->UnBind();
	auto renderView = m_Registry.view<syre::Mesh, syre::Transform, syre::Texture>();

	glm::mat4 lightProjectionMatrix = glm::ortho(-lr, lr, -ud, ud, -unear, ufar);
	glm::mat4 lightViewMatrix = glm::lookAt(glm::vec3(-illum->GetSunRef()._lightDirection), glm::vec3(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 lightSpaceViewProj = lightProjectionMatrix * lightViewMatrix;
	illum->SetLightSpaceViewProj(lightSpaceViewProj);
	illum->SetCamPos(camera->GetPosition());

	glViewport(0, 0, shadowWidth, shadowHeight);
	simpleDepthShader->Bind();
	shadow->Bind();
	for (auto entity : renderView)
	{
		glm::mat4 transform = renderView.get<syre::Transform>(entity).GetModelMat();
		simpleDepthShader->SetUniformMatrix("u_LightSpaceMatrix", lightSpaceViewProj);
		simpleDepthShader->SetUniformMatrix("u_Model", transform);
		renderView.get<syre::Texture>(entity).Bind();
		renderView.get<syre::Mesh>(entity).Render();
	}
	simpleDepthShader->UnBind();
	shadow->Unbind();

	//framebuffer bound
	//framebuffer->BindBuffer(0);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glDisable(GL_BLEND);

	g->Bind();
	rampTex->Bind(20);


	basicShader->Bind();
	basicShader->SetUniform("u_CamPos", camComponent->GetPosition());
	basicShader->SetUniform("playerPos", m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	basicShader->SetUniform("enemyPos", m_Registry.get<syre::Transform>(m_enemy).GetPosition());
	basicShader->SetUniform("u_SpecularStrength", specularOn ? 0.7f : 0.0f);
	basicShader->SetUniform("u_AmbientStrength", ambientOn ? 0.3f : 0.0f);
	basicShader->SetUniform("u_DiffuseStrength", diffuseOn ? 1.0f : 0.0f);
	basicShader->SetUniform("u_CarEmissive", carLighting ? 1 : 0);
	basicShader->SetUniform("u_RampingSpec", rampOnSpec ? 1 : 0);
	basicShader->SetUniform("u_RampingDiff", rampOnDiff ? 1 : 0);



	for (auto entity : renderView)
	{
		glm::mat4 transform = renderView.get<syre::Transform>(entity).GetModelMat();
		basicShader->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		basicShader->SetUniformMatrix("u_Model", transform);
		basicShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		renderView.get<syre::Texture>(entity).Bind();
		renderView.get<syre::Mesh>(entity).Render();
	}

	auto listRenderView = m_Registry.view<syre::Mesh, syre::TransformList, syre::Texture>();
	for (auto entity : listRenderView)
	{
		listRenderView.get<syre::Texture>(entity).Bind();
		listRenderView.get<syre::TransformList>(entity).ListRender(basicShader, listRenderView.get<syre::Mesh>(entity), deltaTime);
	}

	auto morphRenderView = m_Registry.view<syre::MorphRenderer, syre::Transform, syre::Texture>();
	morphShader->Bind();

	morphShader->SetUniform("u_CamPos", camComponent->GetPosition());
	morphShader->SetUniform("playerPos", m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	morphShader->SetUniform("enemyPos", m_Registry.get<syre::Transform>(m_enemy).GetPosition());
	morphShader->SetUniform("u_SpecularStrength", specularOn ? 0.7f : 0.0f);
	morphShader->SetUniform("u_AmbientStrength", ambientOn ? 0.3f : 0.0f);
	morphShader->SetUniform("u_DiffuseStrength", diffuseOn ? 1.0f : 0.0f);
	morphShader->SetUniform("u_CarEmissive", carLighting ? 1 : 0);
	morphShader->SetUniform("u_RampingSpec", rampOnSpec ? 1 : 0);
	morphShader->SetUniform("u_RampingDiff", rampOnDiff ? 1 : 0);



	for (auto entity : morphRenderView)
	{
		float t = morphRenderView.get<syre::MorphRenderer>(entity).Update(deltaTime);
		glm::mat4 transform = morphRenderView.get<syre::Transform>(entity).GetModelMat();
		morphShader->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		morphShader->SetUniformMatrix("u_Model", transform);
		morphShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		morphShader->SetUniform("t", t);
		morphRenderView.get<syre::Texture>(entity).Bind();
		morphRenderView.get<syre::MorphRenderer>(entity).Render();
	}
	auto morphListRenderView = m_Registry.view<syre::MorphRenderer, syre::TransformList, syre::Texture>();
	for (auto entity : morphListRenderView)
	{
		float t = morphListRenderView.get<syre::MorphRenderer>(entity).Update(deltaTime);
		morphShader->SetUniform("t", t);
		morphListRenderView.get<syre::Texture>(entity).Bind();
		morphListRenderView.get<syre::TransformList>(entity).ListRender(morphShader, morphListRenderView.get<syre::MorphRenderer>(entity));
	}

	g->Unbind();

	shadow->BindDepthAsTexture(30);


	DirectionalLight& tempSun = illum->GetSunRef();
	tempSun._ambientPow = ambientOn ? 0.2f : 0.0f;
	tempSun._lightAmbientPow = ambientOn ? 0.2f : 0.0f;
	tempSun._lightSpecularPow = specularOn ? 0.7f : 0.0f;
	tempSun._lightCol = diffuseOn ? glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) : glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	illum->SetPlayerPos(m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	illum->SetEnemyPos(m_Registry.get<syre::Transform>(m_enemy).GetPosition());
	illum->SetEmissive(carLighting);
	illum->ApplyEffect(g);

	shadow->UnbindTexture(30);

	if (dispG)
	{
		if (indivgBuff)
			g->DrawBuffersToScreen(colTarg);
		else
			g->DrawBuffersToScreen();
	}
	else if (dispIllum)
	{
		illum->DrawIllumBuffer();
	}
	else
	{
		PostEffect* lastBuffer = illum;
		if (nightVising)
		{
			vision->ApplyEffect(lastBuffer);

			lastBuffer = vision;
		}
		if (blooming)
		{
			bloom->ApplyEffect(lastBuffer);

			lastBuffer = bloom;
		}
		if (blurring)
		{
			blur->ApplyEffect(lastBuffer);

			lastBuffer = blur;
		}
		if (correcting)
		{
			cubes[activeCube].bind(30);

			colorCorrect->ApplyEffect(lastBuffer);

			lastBuffer = colorCorrect;
		}
		if (pixelling)
		{
			pixel->ApplyEffect(lastBuffer);

			lastBuffer = pixel;
		}
		if (graining)
		{
			grain->ApplyEffect(lastBuffer);

			lastBuffer = grain;
		}


		lastBuffer->DrawToScreen();
	}
	//PostEffect* lastBuffer = framebuffer;
	//framebuffer->UnBindBuffer();




	if (!manualCamera)
	{
		camComponent->SetPosition(m_Registry.get<syre::Transform>(m_PCar).GetPosition() + glm::vec3(1.0f, 5.0f, 5.0f));
	}
	camComponent->SetForward(glm::normalize(m_Registry.get<syre::Transform>(m_PCar).GetPosition() - camComponent->GetPosition()));
	/*m_Registry.get<syre::TransformList>(m_Particles1).UpdateCurPos(m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	m_Registry.get<syre::TransformList>(m_Particles2).UpdateCurPos(m_Registry.get<syre::Transform>(m_enemy).GetPosition());*/

	lastFrame = thisFrame;
	return 0;
}

int Scene2::PausedUpdate()
{
	PostEffect* framebuffer = &m_Registry.get<PostEffect>(sceneBuff);
	CubeCoCoEffect* colorCorrect = &m_Registry.get<CubeCoCoEffect>(cocoBuff);
	CombinedBloom* bloom = &m_Registry.get<CombinedBloom>(bloomBuff);
	Blur* blur = &m_Registry.get<Blur>(blurBuff);
	GBuffer* g = &m_Registry.get<GBuffer>(gBuff);
	IlluminationBuffer* illum = &m_Registry.get<IlluminationBuffer>(illumBuff);
	Framebuffer* shadow = &m_Registry.get<Framebuffer>(shadowBuff);
	Pixelate* pixel = &m_Registry.get<Pixelate>(pixelBuff);
	NightVision* vision = &m_Registry.get<NightVision>(nightVisBuff);
	FilmGrain* grain = &m_Registry.get<FilmGrain>(grainBuff);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	framebuffer->Clear();
	colorCorrect->Clear();
	bloom->Clear();
	blur->Clear();
	g->Clear();
	shadow->Clear();
	illum->Clear();
	pixel->Clear();
	vision->Clear();
	grain->Clear();

	thisFrame = glfwGetTime();
	float deltaTime = thisFrame - lastFrame;
	auto& camComponent = camera;
	auto& obstacleComponent = m_Registry.get<Obstacles>(m_Obstacle);
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
	auto& EnemyComponent = m_Registry.get<Cars>(m_enemy);
	int returning = KeyEvents(deltaTime);
	if (returning == -1)
	{
		return -1;
	}

	flatShader->Bind();
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
	flatShader->SetUniform("offset", glm::vec2(0.0, 0.0f));
	flatShader->SetUniform("aspect", camera->GetAspect());
	m_Registry.get<syre::Texture>(m_PauseMenu).Bind();
	m_Registry.get<syre::Mesh>(m_PauseMenu).Render();



	auto renderView = m_Registry.view<syre::Mesh, syre::Transform, syre::Texture>();

	glm::mat4 lightProjectionMatrix = glm::ortho(-lr, lr, -ud, ud, -unear, ufar);
	glm::mat4 lightViewMatrix = glm::lookAt(glm::vec3(-illum->GetSunRef()._lightDirection), glm::vec3(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 lightSpaceViewProj = lightProjectionMatrix * lightViewMatrix;
	illum->SetLightSpaceViewProj(lightSpaceViewProj);
	illum->SetCamPos(camera->GetPosition());

	glViewport(0, 0, shadowWidth, shadowHeight);
	simpleDepthShader->Bind();
	shadow->Bind();
	for (auto entity : renderView)
	{
		glm::mat4 transform = renderView.get<syre::Transform>(entity).GetModelMat();
		simpleDepthShader->SetUniformMatrix("u_LightSpaceMatrix", lightSpaceViewProj);
		simpleDepthShader->SetUniformMatrix("u_Model", transform);
		renderView.get<syre::Texture>(entity).Bind();
		renderView.get<syre::Mesh>(entity).Render();
	}
	simpleDepthShader->UnBind();
	shadow->Unbind();

	//framebuffer bound
	//framebuffer->BindBuffer(0);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glDisable(GL_BLEND);

	g->Bind();
	rampTex->Bind(20);


	basicShader->Bind();
	basicShader->SetUniform("u_CamPos", camComponent->GetPosition());
	basicShader->SetUniform("playerPos", m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	basicShader->SetUniform("enemyPos", m_Registry.get<syre::Transform>(m_enemy).GetPosition());
	basicShader->SetUniform("u_SpecularStrength", specularOn ? 0.7f : 0.0f);
	basicShader->SetUniform("u_AmbientStrength", ambientOn ? 0.3f : 0.0f);
	basicShader->SetUniform("u_DiffuseStrength", diffuseOn ? 1.0f : 0.0f);
	basicShader->SetUniform("u_CarEmissive", carLighting ? 1 : 0);
	basicShader->SetUniform("u_RampingSpec", rampOnSpec ? 1 : 0);
	basicShader->SetUniform("u_RampingDiff", rampOnDiff ? 1 : 0);



	for (auto entity : renderView)
	{
		glm::mat4 transform = renderView.get<syre::Transform>(entity).GetModelMat();
		basicShader->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		basicShader->SetUniformMatrix("u_Model", transform);
		basicShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		renderView.get<syre::Texture>(entity).Bind();
		renderView.get<syre::Mesh>(entity).Render();
	}

	auto listRenderView = m_Registry.view<syre::Mesh, syre::TransformList, syre::Texture>();
	for (auto entity : listRenderView)
	{
		listRenderView.get<syre::Texture>(entity).Bind();
		listRenderView.get<syre::TransformList>(entity).ListRender(basicShader, listRenderView.get<syre::Mesh>(entity), deltaTime);
	}

	auto morphRenderView = m_Registry.view<syre::MorphRenderer, syre::Transform, syre::Texture>();
	morphShader->Bind();

	morphShader->SetUniform("u_CamPos", camComponent->GetPosition());
	morphShader->SetUniform("playerPos", m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	morphShader->SetUniform("enemyPos", m_Registry.get<syre::Transform>(m_enemy).GetPosition());
	morphShader->SetUniform("u_SpecularStrength", specularOn ? 0.7f : 0.0f);
	morphShader->SetUniform("u_AmbientStrength", ambientOn ? 0.3f : 0.0f);
	morphShader->SetUniform("u_DiffuseStrength", diffuseOn ? 1.0f : 0.0f);
	morphShader->SetUniform("u_CarEmissive", carLighting ? 1 : 0);
	morphShader->SetUniform("u_RampingSpec", rampOnSpec ? 1 : 0);
	morphShader->SetUniform("u_RampingDiff", rampOnDiff ? 1 : 0);



	for (auto entity : morphRenderView)
	{
		float t = morphRenderView.get<syre::MorphRenderer>(entity).GetT();
		glm::mat4 transform = morphRenderView.get<syre::Transform>(entity).GetModelMat();
		morphShader->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		morphShader->SetUniformMatrix("u_Model", transform);
		morphShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		morphShader->SetUniform("t", t);
		morphRenderView.get<syre::Texture>(entity).Bind();
		morphRenderView.get<syre::MorphRenderer>(entity).Render();
	}
	auto morphListRenderView = m_Registry.view<syre::MorphRenderer, syre::TransformList, syre::Texture>();
	for (auto entity : morphListRenderView)
	{
		float t = morphListRenderView.get<syre::MorphRenderer>(entity).GetT();
		morphShader->SetUniform("t", t);
		morphListRenderView.get<syre::Texture>(entity).Bind();
		morphListRenderView.get<syre::TransformList>(entity).ListRender(morphShader, morphListRenderView.get<syre::MorphRenderer>(entity));
	}

	g->Unbind();

	shadow->BindDepthAsTexture(30);

	illum->SetPlayerPos(m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	illum->SetEnemyPos(m_Registry.get<syre::Transform>(m_enemy).GetPosition());
	illum->ApplyEffect(g);

	shadow->UnbindTexture(30);

	if (dispG)
	{
		if (indivgBuff)
			g->DrawBuffersToScreen(colTarg);
		else
			g->DrawBuffersToScreen();
	}
	else if (dispIllum)
	{
		illum->DrawIllumBuffer();
	}
	else
	{
		PostEffect* lastBuffer = illum;
		if (nightVising)
		{
			vision->ApplyEffect(lastBuffer);

			lastBuffer = vision;
		}
		if (blooming)
		{
			bloom->ApplyEffect(lastBuffer);

			lastBuffer = bloom;
		}
		if (blurring)
		{
			blur->ApplyEffect(lastBuffer);

			lastBuffer = blur;
		}
		if (correcting)
		{
			cubes[activeCube].bind(30);

			colorCorrect->ApplyEffect(lastBuffer);

			lastBuffer = colorCorrect;
		}
		if (pixelling)
		{
			pixel->ApplyEffect(lastBuffer);

			lastBuffer = pixel;
		}
		if (graining)
		{
			grain->ApplyEffect(lastBuffer);

			lastBuffer = grain;
		}


		lastBuffer->DrawToScreen();
	}
	//PostEffect* lastBuffer = framebuffer;
	//framebuffer->UnBindBuffer();




	if (!manualCamera)
	{
		camComponent->SetPosition(m_Registry.get<syre::Transform>(m_PCar).GetPosition() + glm::vec3(1.0f, 5.0f, 5.0f));
	}
	camComponent->SetForward(glm::normalize(m_Registry.get<syre::Transform>(m_PCar).GetPosition() - camComponent->GetPosition()));
	/*m_Registry.get<syre::TransformList>(m_Particles1).UpdateCurPos(m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	m_Registry.get<syre::TransformList>(m_Particles2).UpdateCurPos(m_Registry.get<syre::Transform>(m_enemy).GetPosition());*/




	lastFrame = thisFrame;
	return returning;
}

void Scene2::ImGUIUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	CombinedBloom* bloom = &m_Registry.get<CombinedBloom>(bloomBuff);
	Blur* blur = &m_Registry.get<Blur>(blurBuff);
	IlluminationBuffer* illum = &m_Registry.get<IlluminationBuffer>(illumBuff);
	Pixelate* pixel = &m_Registry.get<Pixelate>(pixelBuff);
	int blurPasses = blur->GetPasses();
	float bloomThreshold = bloom->GetThreshold();
	int bloomPasses = bloom->GetPasses();
	int pixellationFactor = pixel->GetFactor();

	// ImGui context new frame
	ImGui::NewFrame();
	AudioEngine& audio = AudioEngine::Instance();
	int pauseStatus = audio.GetGlobalParameterValue("IsPaused");
	float sfxVol = audio.GetGlobalParameterValue("SFXVolume");
	float musVol = audio.GetGlobalParameterValue("MusicVolume");

	if (ImGui::Begin("Debug")) {
		// Render our GUI stuff
		if (ImGui::CollapsingHeader("Deferred"))
		{
			ImGui::DragFloat3("Light Direction/Position", glm::value_ptr(illum->GetSunRef()._lightDirection), 0.01f, -10.0f, 10.0f);
			ImGui::Checkbox("Display GBuffer", &dispG);
			if (dispG)
			{
				ImGui::Checkbox("Display Targets Individually", &indivgBuff);
				if (indivgBuff)
				{
					ImGui::SliderInt("Color Target", &colTarg, 0, 3);
				}
			}
			ImGui::Checkbox("Display Illumination Accumulation", &dispIllum);
			ImGui::SliderFloat("Left and Right ortho", &lr, 0.0f, 2000.0f);
			ImGui::SliderFloat("Up and Down ortho", &ud, 0.0f, 2000.0f);
			ImGui::SliderFloat("Near ortho", &unear, 0.0f, 2000.0f);
			ImGui::SliderFloat("Far ortho", &ufar, 0.0f, 2000.0f);

		}
		if (ImGui::CollapsingHeader("Post Processing"))
		{
			ImGui::Checkbox("Night Vision", &nightVising);
			ImGui::Checkbox("Bloom", &blooming);
			if (blooming)
			{
				ImGui::SliderFloat("Bloom Threshold", &bloomThreshold, 0, 1);
				ImGui::SliderInt("Bloom blur Passes", &bloomPasses, 0, 20);
				bloom->SetPasses(bloomPasses);
				bloom->SetThreshold(bloomThreshold);
			}
			ImGui::Checkbox("Blur", &blurring);
			if (blurring)
			{
				ImGui::SliderInt("Blur blur Passes", &blurPasses, 0, 20);
				blur->SetPasses(blurPasses);
			}
			ImGui::Checkbox("Color Correction", &correcting);
			if (correcting)
			{
				ImGui::SliderInt("Active CoCo Effect", &activeCube, 0, cubes.size() - 1);
				ImGui::Text("0 is Neutral, 1 is Cool, 2 is Warm, 3 is Custom");
			}
			ImGui::Checkbox("Pixelation", &pixelling);
			if (pixelling)
			{
				ImGui::SliderInt("Pixellation Amount", &pixellationFactor, 2, 32);
				pixel->SetFactor(pixellationFactor);
			}
			//ImGui::Checkbox("Film Grain", &graining);
		}
		if (ImGui::CollapsingHeader("Lighting"))
		{
			ImGui::Checkbox("Ambient Lighting", &ambientOn);
			ImGui::Checkbox("Diffuse Lighting", &diffuseOn);
			ImGui::Checkbox("Specular Lighting", &specularOn);
			ImGui::Checkbox("Emissive Car Lighting", &carLighting);
			//ImGui::Checkbox("Specular Ramping", &rampOnSpec);
			//ImGui::Checkbox("Diffuse Ramping", &rampOnDiff);
		}
		if (ImGui::CollapsingHeader("FMOD"))
		{
			ImGui::SliderFloat("Effects Volume", &sfxVol, 0.f, 1.f);
			ImGui::SliderFloat("Music Volume", &musVol, 0.f, 1.f);
		}

		glm::vec3 camPos = camera->GetPosition();
		if (ImGui::Button(manualCamera ? "Auto Camera" : "Manual Camera"))
		{
			manualCamera = !manualCamera;
		}
		if (manualCamera)
		{
			ImGui::SliderFloat3("Camera Position", &camPos.x, -200.f, 200.f);
			camera->SetPosition(camPos);

		}
		if (ImGui::Button("1"))
		{
			dispG = false;
			dispIllum = false;
		}
		if (ImGui::Button("2"))
		{
			dispG = true;
			indivgBuff = true;
			colTarg = 3;
		}
		if (ImGui::Button("3"))
		{
			dispG = true;
			indivgBuff = true;
			colTarg = 1;
		}
		if (ImGui::Button("4"))
		{
			dispG = true;
			indivgBuff = true;
			colTarg = 0;
		}
		if (ImGui::Button("5"))
		{
			dispG = false;
			dispIllum = true;
		}
	}
	ImGui::End();
	audio.SetGlobalParameter("IsPaused", pauseStatus);
	audio.SetGlobalParameter("SFXVolume", sfxVol);
	audio.SetGlobalParameter("MusicVolume", musVol);


	// Make sure ImGui knows how big our window is
	ImGuiIO& io = ImGui::GetIO();
	int width{ 0 }, height{ 0 };
	glfwGetWindowSize(window, &width, &height);
	io.DisplaySize = ImVec2((float)width, (float)height);

	// Render all of our ImGui elements
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		// Update the windows that ImGui is using
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		// Restore our gl context
		glfwMakeContextCurrent(window);
	}

}

int Scene2::GetID()
{
	return 2;
}

Camera::sptr& Scene2::GetCam()
{
	// TODO: insert return statement here
	return camera;
}

int Scene2::KeyEvents(float delta)
{
	if (isPaused)
	{
		double* x = new double;
		double* y = new double;

		glfwGetCursorPos(window, x, y);
		//printf("Mouse at X %f Y %f\n", *x, *y);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		{
			escRelease = true;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && escRelease)
		{
			isPaused = false;
			escRelease = false;

		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			if (552.0f < *x && *x < 729.0f)
			{
				if (323.0f < *y && *y < 367.0f)
				{
					isPaused = false;
				}
				else if (374.0f < *y && *y < 417.0f)
				{
					m_Registry.clear();
					return -1;
				}
				else if (425.0f < *y && *y < 474.0f)
				{
					return -2;
				}
			}
		}

		return 0;
	}
	else
	{
		Elapsedtime += delta;
		auto& camComponent = camera;
		auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
		auto& EnemyComponent = m_Registry.get<Cars>(m_enemy);
		int temp;
		glm::vec3 curCamPos = camComponent->GetPosition();
		glm::vec3 curCamFor = camComponent->GetForward();

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			curCamPos.x += 10.f * delta;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			curCamPos.x -= 10.f * delta;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			curCamPos.y -= 10.f * delta;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			curCamPos.y += 10.f * delta;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			curCamFor.x += 0.1f * delta;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			curCamFor.x -= 0.1f * delta;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			curCamFor.y -= 0.1f * delta;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			curCamFor.y += 0.1f * delta;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			PlayerComponent.Draw();
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		{
			escRelease = true;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && escRelease)
		{
			isPaused = true;
			escRelease = false;

		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && Elapsedtime >= 0.5)
		{
			double* x = new double;
			double* y = new double;

			glfwGetCursorPos(window, x, y);
			if (*x >= 70 && *x <= 95 && *y <= 615 && *y >= 597)
			{
				lbutton_down = true;
			}
			/*
			printf("Mouse at X ");
			printf("%f", *x);
			printf("\n");
			printf("Mouse at Y ");
			printf("%f", *y);
			*/
			if (m_Registry.get<syre::PathAnimator>(m_PCar).HitMax() || m_Registry.get<syre::PathAnimator>(m_enemy).HitMax())
			{
				for (float i = 0; i <= 5; i++)
				{
					if ((i * 165) + 478 <= *x && (i + 1) * 165 + 478 >= *x && *y >= 457 && *y <= 706 && PlayerComponent.GetCard(i, true) != -1)
					{
						PlayerComponent.PlayCard(i, 0);
						Elapsedtime = 0;
					}
				}
				if (*x >= 34 && *x <= 72 && *y <= 699 && *y >= 674)
				{
					PlayerComponent.SetBrk();
					Elapsedtime = 0;
				}
				else if (*x >= 98 && *x <= 129 && *y <= 709 && *y >= 666)
				{
					PlayerComponent.SetAcc();
					Elapsedtime = 0;
				}
			}
			if (*x >= 1157 && *x <= 1278 && *y <= 132 && *y >= 10)
			{
				if (helptog == true)
				{
					helptog = false;
					Elapsedtime = 0;
				}
				else if (helptog == false)
				{
					helptog = true;
					Elapsedtime = 0;
				}
			}

			if (*x >= 242 && *x <= 397 && *y <= 687 && *y >= 611)
			{
				if (m_Registry.get<syre::PathAnimator>(m_PCar).HitMax() || m_Registry.get<syre::PathAnimator>(m_enemy).HitMax())
				{
					if (PlayerComponent.GetPosition1() != -1 && PlayerComponent.GetPosition1() != -2 && PlayerComponent.GetPosition1() != -3)
					{
						if (PlayerComponent.GetCard(PlayerComponent.GetPosition1(), true) == 2)
						{
							EnemyComponent.ChangeGears(PlayerComponent.GetGear());
						}
						else if (PlayerComponent.GetCard(PlayerComponent.GetPosition1(), true) == 5)
						{
							EnemyComponent.SetSabo();
						}
					}

					if (PlayerComponent.GetPosition2() != -1 && PlayerComponent.GetPosition2() != -2 && PlayerComponent.GetPosition2() != -3)
					{
						if (PlayerComponent.GetCard(PlayerComponent.GetPosition2(), true) == 2)
						{
							EnemyComponent.ChangeGears(PlayerComponent.GetGear());
						}
						else if (PlayerComponent.GetCard(PlayerComponent.GetPosition2(), true) == 5)
						{
							EnemyComponent.SetSabo();
						}
					}
					PlayerComponent.ResolveCards();
				}
			}
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			lbutton_down = false;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			m_Registry.get<syre::PathAnimator>(m_PCar).Reset();
		}
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			if (m_Registry.get<syre::PathAnimator>(m_PCar).HitMax() || m_Registry.get<syre::PathAnimator>(m_enemy).HitMax())
			{
				if (PlayerComponent.GetPosition1() != -1 && PlayerComponent.GetPosition1() != -2 && PlayerComponent.GetPosition1() != -3)
				{
					if (PlayerComponent.GetCard(PlayerComponent.GetPosition1(), true) == 2)
					{
						EnemyComponent.ChangeGears(PlayerComponent.GetGear());
					}
					else if (PlayerComponent.GetCard(PlayerComponent.GetPosition1(), true) == 5)
					{
						EnemyComponent.SetSabo();
					}
				}

				if (PlayerComponent.GetPosition2() != -1 && PlayerComponent.GetPosition2() != -2 && PlayerComponent.GetPosition2() != -3)
				{
					if (PlayerComponent.GetCard(PlayerComponent.GetPosition2(), true) == 2)
					{
						EnemyComponent.ChangeGears(PlayerComponent.GetGear());
					}
					else if (PlayerComponent.GetCard(PlayerComponent.GetPosition2(), true) == 5)
					{
						EnemyComponent.SetSabo();
					}
				}
				PlayerComponent.ResolveCards();
			}
		}
		camComponent->SetPosition(curCamPos);
		return 0;
	}
}

