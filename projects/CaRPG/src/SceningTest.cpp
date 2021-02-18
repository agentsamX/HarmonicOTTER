#include "SceningTest.h"
#include "Cars.h"
#include "Obstacles.h"

int start = 0;

SceningTest::SceningTest(GLFWwindow* inWind)
{
	window = inWind;
}

void SceningTest::Start()
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	rampTex = Texture2D::LoadFromFile("tinyRamp.png");

	sceneBuff = m_Registry.create();
	cocoBuff = m_Registry.create();
	m_Registry.emplace<PostEffect>(sceneBuff);
	m_Registry.emplace<CubeCoCoEffect>(cocoBuff);
	m_Registry.get<PostEffect>(sceneBuff).Init(width, height);
	m_Registry.get<CubeCoCoEffect>(cocoBuff).Init(width, height);

	cubes.push_back(LUT3D("cubes/Neutral-512.cube"));
	cubes.push_back(LUT3D("cubes/Cool.cube"));
	cubes.push_back(LUT3D("cubes/Warm.cube"));
	cubes.push_back(LUT3D("cubes/Darken-512.cube"));

	AudioEngine& engine = AudioEngine::Instance();
	

	//play event
	AudioEvent& oldMusic = engine.GetEvent("Menu Music");
	oldMusic.Stop();

	AudioEvent& newMusic = engine.CreateEventW("Ambient", "{18c986e1-88b0-45ce-82c7-567d3447f2e8}");
	newMusic.Play();

	AudioEvent& slipstream = engine.CreateEventW("Slipstream", "{50d08bc6-b9f1-4411-906f-69506bd36f13}");
	AudioEvent& drift = engine.CreateEventW("Drift", "{3eb39553-5d08-456c-998b-822942c1f860}");
	AudioEvent& multiNitro = engine.CreateEventW("MultiNitro", "{6d8f789b-95db-4007-bd66-f26c1f377b3c}");

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
	m_GearboxLever = m_Registry.create();
	m_Accelerometer = m_Registry.create();
	m_Needle = m_Registry.create();
	m_PGears = m_Registry.create();
	m_EGears = m_Registry.create();
	m_AccRect = m_Registry.create();
	m_Pneedle = m_Registry.create();
	m_Eneedle = m_Registry.create();
	/*m_Particles1 = m_Registry.create();
	m_Particles2 = m_Registry.create();*/
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
	m_Registry.emplace<syre::Mesh>(Track, "Track1New.obj");
	m_Registry.emplace<syre::Transform>(Track, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(Track, "PossibleRoad.png");

	m_Registry.emplace<syre::Mesh>(m_Hazard, "RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_Hazard, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Hazard, "Apex.png");

	m_Registry.emplace<syre::Mesh>(m_Gearbox, "Gearbox.obj");
	m_Registry.emplace<syre::Transform>(m_Gearbox, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Gearbox, "GearBoxNeutral.png");

	m_Registry.emplace<syre::Mesh>(m_GearboxLever, "Lever.obj");
	m_Registry.emplace<syre::Transform>(m_GearboxLever, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_GearboxLever, "GearboxLever.png");
	
	m_Registry.emplace<syre::Mesh>(m_Accelerometer, "Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Accelerometer, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Accelerometer, "Accelerometer.png");
	
	m_Registry.emplace<syre::MorphRenderer>(m_Needle);
	m_Registry.emplace<syre::Transform>(m_Needle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Needle, "Finish.png");
	m_Registry.get<syre::MorphRenderer>(m_Needle).AddFrame("NeedleLeft.obj");
	m_Registry.get<syre::MorphRenderer>(m_Needle).AddFrame("Needle.obj");
	m_Registry.get<syre::MorphRenderer>(m_Needle).AddFrame("NeedleRight.obj");

	m_Registry.emplace<syre::Mesh>(m_TransparentBlack, "RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_TransparentBlack, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_TransparentBlack, "TransparentBlack.png");

	m_Registry.emplace<syre::Mesh>(m_PauseMenu, "RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_PauseMenu, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_PauseMenu, "PauseMenu.png");

	m_Registry.emplace<syre::Mesh>(m_PGears, "Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_PGears, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_PGears, "PauseMenu.png");

	m_Registry.emplace<syre::Mesh>(m_AccRect, "Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_AccRect, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_AccRect, "Accelerometer_rec.png");

	m_Registry.emplace<syre::Mesh>(m_Pneedle, "Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Pneedle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Pneedle, "Pneedle1.png");

	m_Registry.emplace<syre::Mesh>(m_Eneedle, "Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_Eneedle, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_Eneedle, "Eneedle1.png");

	m_Registry.emplace<syre::Mesh>(m_EGears, "Accelerometer.obj");
	m_Registry.emplace<syre::Transform>(m_EGears, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(0.25f));
	m_Registry.emplace<syre::Texture>(m_EGears, "PauseMenu.png");
	


	entt::entity start = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(start);
	m_Registry.emplace<syre::Transform>(start, glm::vec3(15.0f, -50.0f, 0.0f), glm::vec3(90.0f, 0.0f, 190.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(start, "START.png");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START1.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START1.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START2.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START3.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START4.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START5.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START6.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START7.obj");
	m_Registry.get<syre::MorphRenderer>(start).AddFrame("START8.obj");
	

	entt::entity finish = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(finish);
	m_Registry.emplace<syre::Transform>(finish, glm::vec3(-270.0f, -135.0f, 0.0f), glm::vec3(90.0f, 0.0f, 150.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(finish, "Finish.png");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH1.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH1.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH2.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH3.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH4.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH5.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH6.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH7.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH8.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH9.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH10.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH11.obj");
	m_Registry.get<syre::MorphRenderer>(finish).AddFrame("FINISH12.obj");



	
	//trees
	entt::entity trackTrees = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackTrees, "TreesMap.obj");
	m_Registry.emplace<syre::Transform>(trackTrees, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackTrees, "Tree.png");

	//terrain
	entt::entity trackTerrain = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackTerrain, "TerrainMap.obj");
	m_Registry.emplace<syre::Transform>(trackTerrain, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackTerrain, "Terrain.png");

	//signs
	entt::entity trackSigns = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackSigns, "SignsMap.obj");
	m_Registry.emplace<syre::Transform>(trackSigns, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackSigns, "Signs.png");

	//sharp rocks
	entt::entity trackSharpRocks = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackSharpRocks, "SharpRockMap.obj");
	m_Registry.emplace<syre::Transform>(trackSharpRocks, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackSharpRocks, "SharpRock.png");

	//round rocks
	entt::entity trackRoundRocks = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackRoundRocks, "RoundRockMap.obj");
	m_Registry.emplace<syre::Transform>(trackRoundRocks, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackRoundRocks, "RoundRock.png");

	//flowers
	entt::entity trackFlowers = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackFlowers, "FlowersMap.obj");
	m_Registry.emplace<syre::Transform>(trackFlowers, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackFlowers, "Flower.png");

	//bush
	entt::entity trackBush = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(trackBush, "BushMap.obj");
	m_Registry.emplace<syre::Transform>(trackBush, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(trackBush, "Bush.png");
	
	entt::entity butterflies = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(butterflies);
	m_Registry.get<syre::MorphRenderer>(butterflies).AddFrame("ButterflyNeutral.obj");
	m_Registry.get<syre::MorphRenderer>(butterflies).AddFrame("ButterflyDown.obj");
	m_Registry.get<syre::MorphRenderer>(butterflies).AddFrame("ButterflyNeutral.obj");
	m_Registry.get<syre::MorphRenderer>(butterflies).AddFrame("ButterflyUp.obj");

	m_Registry.emplace<syre::Texture>(butterflies, "butterfly.png");
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
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying1.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying2.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying3.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying4.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying5.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying6.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying7.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying8.obj");
	m_Registry.get<syre::MorphRenderer>(swayingTree).AddFrame("TreeSwaying9.obj");

	m_Registry.emplace<syre::Texture>(swayingTree, "Tree.png");
	m_Registry.emplace<syre::TransformList>(swayingTree);
	m_Registry.get<syre::TransformList>(swayingTree).SetDefaultRot(glm::vec3(90.0f, 0.0f, 0.0f));
	m_Registry.get<syre::TransformList>(swayingTree).SetDefaultSca(glm::vec3(1.0f));
	m_Registry.get<syre::TransformList>(swayingTree).AddPos(glm::vec3(-1.0f, -80.0f, 0.0f));







	m_Registry.emplace<Obstacles>(m_Obstacle);
	

	//remove this if frequent crashes
	/*m_Registry.emplace<syre::Mesh>(m_Particles1, "particleLol.obj");
	m_Registry.emplace<syre::Texture>(m_Particles1, "black.png");
	m_Registry.emplace<syre::TransformList>(m_Particles1);
	m_Registry.get<syre::TransformList>(m_Particles1).Particalize(0.05f, 0.6f);
	m_Registry.get<syre::TransformList>(m_Particles1).SetDefaultSca(glm::vec3(0.1f));

	m_Registry.emplace<syre::Mesh>(m_Particles2, "particleLol.obj");
	m_Registry.emplace<syre::Texture>(m_Particles2, "black.png");
	m_Registry.emplace<syre::TransformList>(m_Particles2);
	m_Registry.get<syre::TransformList>(m_Particles2).Particalize(0.05f, 0.6f);
	m_Registry.get<syre::TransformList>(m_Particles2).SetDefaultSca(glm::vec3(0.1f));*/

	
	m_Registry.emplace<Cars>(m_PCar);
	m_Registry.emplace<syre::Mesh>(m_PCar, "Car2.obj");
	m_Registry.emplace<syre::Transform>(m_PCar, glm::vec3(6.0f, 0.0f, 0.0f),glm::vec3(90.f,0.0f,0.0f),glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_PCar, "Car2.png");
	m_Registry.emplace<syre::PathAnimator>(m_PCar,syre::PathType::BEZIER);
	auto& carPath = m_Registry.get<syre::PathAnimator>(m_PCar);

	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //start point
	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of first straight
	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(10.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(35.0f, -100.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of first turn
	carPath.AddPoint(glm::vec3(35.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(35.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(110.0f, -101.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of 2nd straight 
	carPath.AddPoint(glm::vec3(110.0f, -101.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(155.0f, -85.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 2nd turn 
	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(155.0f, -205.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 3rd str 
	carPath.AddPoint(glm::vec3(155.0f, -205.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(145.0f, -247.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(205.0f, -247.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //mid s  
	carPath.AddPoint(glm::vec3(205.0f, -247.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(235.0f, -230.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of S 
	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(236.f, -420.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of str
	carPath.AddPoint(glm::vec3(236.f, -420.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(240.f, -458.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(198.f, -458.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //mid u turn
	carPath.AddPoint(glm::vec3(198.f, -458.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(151.f, -466.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(161.f, -416.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //end u turn
	carPath.AddPoint(glm::vec3(161.f, -416.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(164.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //end turn 
	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(63.f, -373.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //str
	carPath.AddPoint(glm::vec3(63.f, -373.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(24.f, -370.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //turn
	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(16.f, -470.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //str
	carPath.AddPoint(glm::vec3(16.f, -470.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(20.f, -502.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-26.f, -502.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid s 
	carPath.AddPoint(glm::vec3(-26.f, -502.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-73.f, -490.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-73.f, -537.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end s 
	carPath.AddPoint(glm::vec3(-73.f, -537.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-64.f, -570.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-114.f, -570.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid u 
	carPath.AddPoint(glm::vec3(-114.f, -570.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-148.f, -580.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //end u turn 
	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-130.f, -393.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //str
	carPath.AddPoint(glm::vec3(-130.f, -393.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-138.f, -350.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-88.f, -365.f, 0.0f), glm::vec3(90.0f, 0.0f, -280.0f)); //mid u 
	carPath.AddPoint(glm::vec3(-88.f, -365.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-70.f, -360.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-74.f, -405.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end u 
	carPath.AddPoint(glm::vec3(-74.f, -405.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-76.f, -448.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-56.f, -448.f, 0.0f), glm::vec3(90.0f, 0.0f, 80.0f)); //mid u 
	carPath.AddPoint(glm::vec3(-56.f, -448.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-9.f, -460.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //end u 
	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(1.5f, -346.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //str
	carPath.AddPoint(glm::vec3(1.5f, -346.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(30.f, -310.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(90.0f, 0.0f, 260.0f)); //turn 
	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-117.f, -286.f, 0.0f), glm::vec3(90.0f, 0.0f, 265.0f)); //str
	carPath.AddPoint(glm::vec3(-117.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-133.f, -285.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-133.f, -252.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); // mid u 
	carPath.AddPoint(glm::vec3(-133.f, -252.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-147.f, -219.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //end u 
	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-34.f, -210.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //str
	carPath.AddPoint(glm::vec3(-34.f, -210.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(15.f, -220.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(8.f, -160.f, 0.0f), glm::vec3(90.0f, 0.0f, 190.0f)); //mid u
	carPath.AddPoint(glm::vec3(8.f, -160.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(16.f, -120.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //end u
	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-108.f, -129.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //str
	carPath.AddPoint(glm::vec3(-108.f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-150.f, -133.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); //turn ///////
	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-145.f, -25.f, 0.0f), glm::vec3(90.0f, 0.0f, 175.0f)); //str
	carPath.AddPoint(glm::vec3(-145.f, -25.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-125.f, 14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-195.f, 14.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //mid u////////////
	carPath.AddPoint(glm::vec3(-195.f, 14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-220.f, 13.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(90.0f, 0.0f, 340.0f)); //end u ///////
	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(90.0f, 0.0f, 337.0f)); //str
	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.SpeedControl();


	m_Registry.emplace<Cars>(m_enemy);
	m_Registry.emplace<syre::Mesh>(m_enemy, "Car2.obj");
	m_Registry.emplace<syre::Transform>(m_enemy, glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(90.f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_enemy, "Car2-Blue.png");
	m_Registry.emplace<syre::PathAnimator>(m_enemy, syre::PathType::BEZIER);
	auto& enemyCarPath = m_Registry.get<syre::PathAnimator>(m_enemy);

	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //start point
	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(10.0f, -70.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of first straight
	enemyCarPath.AddPoint(glm::vec3(10.0f, -70.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(14.0f, -100.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(35.0f, -96.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of first turn
	enemyCarPath.AddPoint(glm::vec3(35.0f, -96.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(35.0f, -96.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(110.0f, -97.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of 2nd straight 
	enemyCarPath.AddPoint(glm::vec3(110.0f, -97.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(159.0f, -81.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(159.0f, -140.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 2nd turn 
	enemyCarPath.AddPoint(glm::vec3(159.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(159.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(159.0f, -205.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 3rd str 
	enemyCarPath.AddPoint(glm::vec3(159.0f, -205.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(149.0f, -243.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(205.0f, -243.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //mid s  
	enemyCarPath.AddPoint(glm::vec3(205.0f, -243.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(235.0f, -230.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(240.f, -286.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of S 
	enemyCarPath.AddPoint(glm::vec3(240.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(240.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(240.f, -420.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of str
	enemyCarPath.AddPoint(glm::vec3(240.f, -420.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(244.f, -458.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));            ///////

	enemyCarPath.AddPoint(glm::vec3(198.f, -462.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //mid u turn
	enemyCarPath.AddPoint(glm::vec3(198.f, -462.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(151.f, -470.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(157.f, -416.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //end u turn
	enemyCarPath.AddPoint(glm::vec3(157.f, -416.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(160.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(134.f, -385.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //end turn 
	enemyCarPath.AddPoint(glm::vec3(134.f, -385.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(134.f, -385.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(63.f, -377.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(63.f, -377.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(28.f, -374.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));      ////////

	enemyCarPath.AddPoint(glm::vec3(28.f, -400.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //turn
	enemyCarPath.AddPoint(glm::vec3(28.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(28.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(20.f, -470.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(20.f, -470.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(24.f, -503.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-26.f, -506.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid s
	enemyCarPath.AddPoint(glm::vec3(-26.f, -506.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-77.f, -495.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-68.f, -537.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end s
	enemyCarPath.AddPoint(glm::vec3(-68.f, -537.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-60.f, -570.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));   ///

	enemyCarPath.AddPoint(glm::vec3(-114.f, -574.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid u 
	enemyCarPath.AddPoint(glm::vec3(-114.f, -574.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-152.f, -582.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-152.f, -529.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //end u turn 
	enemyCarPath.AddPoint(glm::vec3(-152.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-152.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));    /////

	enemyCarPath.AddPoint(glm::vec3(-134.f, -393.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-134.f, -393.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-142.f, -350.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-88.f, -361.f, 0.0f), glm::vec3(90.0f, 0.0f, -280.0f)); //mid u 
	enemyCarPath.AddPoint(glm::vec3(-88.f, -361.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-64.f, -356.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-70.f, -405.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end u 
	enemyCarPath.AddPoint(glm::vec3(-70.f, -405.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-72.f, -450.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-56.f, -444.f, 0.0f), glm::vec3(90.0f, 0.0f, 80.0f)); //mid u 
	enemyCarPath.AddPoint(glm::vec3(-56.f, -444.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-11.f, -456.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-13.f, -415.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //end u 
	enemyCarPath.AddPoint(glm::vec3(-13.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-13.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-3.5f, -346.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-3.5f, -346.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(26.f, -310.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));   /////////

	enemyCarPath.AddPoint(glm::vec3(-64.f, -293.f, 0.0f), glm::vec3(90.0f, 0.0f, 260.0f)); //turn 
	enemyCarPath.AddPoint(glm::vec3(-64.f, -293.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-64.f, -293.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));  /////

	enemyCarPath.AddPoint(glm::vec3(-117.f, -290.f, 0.0f), glm::vec3(90.0f, 0.0f, 265.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-117.f, -290.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-131.f, -287.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));  ///

	enemyCarPath.AddPoint(glm::vec3(-137.f, -252.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); // mid u 
	enemyCarPath.AddPoint(glm::vec3(-137.f, -252.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-149.f, -219.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-107.f, -210.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //end u 
	enemyCarPath.AddPoint(glm::vec3(-107.f, -210.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-107.f, -210.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-34.f, -206.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-34.f, -206.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(15.f, -216.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(4.f, -160.f, 0.0f), glm::vec3(90.0f, 0.0f, 190.0f)); //mid u
	enemyCarPath.AddPoint(glm::vec3(4.f, -160.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(12.f, -122.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-36.f, -129.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //end u
	enemyCarPath.AddPoint(glm::vec3(-36.f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-36.f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-108.f, -133.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-108.f, -133.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-150.f, -137.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));  //////////

	enemyCarPath.AddPoint(glm::vec3(-149.f, -93.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); //turn 
	enemyCarPath.AddPoint(glm::vec3(-149.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-149.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-149.f, -25.f, 0.0f), glm::vec3(90.0f, 0.0f, 175.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-149.f, -25.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-129.f, 14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-195.f, 10.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //mid u
	enemyCarPath.AddPoint(glm::vec3(-195.f, 10.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-216.f, 9.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-222.f, -3.f, 0.0f), glm::vec3(90.0f, 0.0f, 340.0f)); //end u
	enemyCarPath.AddPoint(glm::vec3(-222.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-222.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	enemyCarPath.AddPoint(glm::vec3(-272.f, -121.f, 0.0f), glm::vec3(90.0f, 0.0f, 337.0f)); //str
	enemyCarPath.AddPoint(glm::vec3(-272.f, -121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	enemyCarPath.AddPoint(glm::vec3(-272.f, -121.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	enemyCarPath.SpeedControl();

	//cards

	m_Registry.emplace<syre::Mesh>(m_Card, "Card.obj");
	m_Registry.emplace<syre::Transform>(m_Card, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2f));
	m_Registry.emplace<syre::Texture>(m_Card, "NO2.png");



	cardTextures.push_back(syre::Texture("NO2.png"));
	cardTextures.push_back(syre::Texture("Drift.png"));
	cardTextures.push_back(syre::Texture("Slipstream.png"));
	cardTextures.push_back(syre::Texture("Muffler.png"));

	hazardTextures.push_back(syre::Texture("Apex.png"));
	hazardTextures.push_back(syre::Texture("Hairpin.png"));
	hazardTextures.push_back(syre::Texture("Chicane.png"));
	hazardTextures.push_back(syre::Texture("Rocks.png"));

	gearboxTextures.push_back(syre::Texture("GearBoxNeutral.png"));
	gearboxTextures.push_back(syre::Texture("GearBoxGasPressed.png"));
	gearboxTextures.push_back(syre::Texture("GearBoxBrakePressed.png"));
	
	//accelerometerTexture.push_back(syre::Texture("Accelerometer.png"));

	pGearTextures.push_back(syre::Texture("P1.png"));
	pGearTextures.push_back(syre::Texture("P1.png"));
	pGearTextures.push_back(syre::Texture("P2.png"));
	pGearTextures.push_back(syre::Texture("P3.png"));
	pGearTextures.push_back(syre::Texture("P4.png"));
	pGearTextures.push_back(syre::Texture("P5.png"));
	pGearTextures.push_back(syre::Texture("P6.png"));

	eGearTextures.push_back(syre::Texture("E1.png"));
	eGearTextures.push_back(syre::Texture("E1.png"));
	eGearTextures.push_back(syre::Texture("E2.png"));
	eGearTextures.push_back(syre::Texture("E3.png"));
	eGearTextures.push_back(syre::Texture("E4.png"));
	eGearTextures.push_back(syre::Texture("E5.png"));
	eGearTextures.push_back(syre::Texture("E6.png"));

	eneedleTextures.push_back(syre::Texture("Eneedle1.png"));
	eneedleTextures.push_back(syre::Texture("Eneedle1.png"));
	eneedleTextures.push_back(syre::Texture("Eneedle2.png"));
	eneedleTextures.push_back(syre::Texture("Eneedle3.png"));
	eneedleTextures.push_back(syre::Texture("Eneedle4.png"));
	eneedleTextures.push_back(syre::Texture("Eneedle5.png"));
	eneedleTextures.push_back(syre::Texture("Eneedle6.png"));

	pneedleTextures.push_back(syre::Texture("Pneedle1.png"));
	pneedleTextures.push_back(syre::Texture("Pneedle1.png"));
	pneedleTextures.push_back(syre::Texture("Pneedle2.png"));
	pneedleTextures.push_back(syre::Texture("Pneedle3.png"));
	pneedleTextures.push_back(syre::Texture("Pneedle4.png"));
	pneedleTextures.push_back(syre::Texture("Pneedle5.png"));
	pneedleTextures.push_back(syre::Texture("Pneedle6.png"));

	flatShader = Shader::Create();
	flatShader->LoadShaderPartFromFile("flatVert.glsl", GL_VERTEX_SHADER);
	flatShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatShader->Link();




	
	
	basicShader = Shader::Create();
	basicShader->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	basicShader->LoadShaderPartFromFile("frag_shader.glsl", GL_FRAGMENT_SHADER);
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
	morphShader->LoadShaderPartFromFile("frag_shader.glsl", GL_FRAGMENT_SHADER);
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


	flatMorphShader = Shader::Create();
	flatMorphShader->LoadShaderPartFromFile("flatMorphVert.glsl", GL_VERTEX_SHADER);
	flatMorphShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatMorphShader->Link();


	auto& camComponent = camera;
	camComponent->SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camComponent->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camComponent->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camComponent->SetFovDegrees(100.0f); // Set an initial FOV

	auto& obstacleComponent = m_Registry.get<Obstacles>(m_Obstacle);

	auto listView = m_Registry.view<syre::TransformList>();
	for (auto entity : listView)
	{
		m_Registry.get<syre::TransformList>(entity).SetCamera(camera);
	}


	lastFrame = glfwGetTime();
}


int SceningTest::Update()
{
	PostEffect* framebuffer = &m_Registry.get<PostEffect>(sceneBuff);
	CubeCoCoEffect* colorCorrect = &m_Registry.get<CubeCoCoEffect>(cocoBuff);

	

	framebuffer->Clear();
	colorCorrect->Clear();

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
	bool Eemp=false;
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
		if (cardVal != -1)
		{
			flatShader->SetUniform("offset", glm::vec2(-0.1f+i/4.2f, -.66f));

			cardTextures[cardVal].Bind();
			m_Registry.get<syre::Mesh>(m_Card).Render();
		}	
	}

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.09f)));
	flatShader->SetUniform("offset", glm::vec2(0.90, 0.8f));
	int ObsVal = obstacleComponent.GetObs();
	hazardTextures[ObsVal].Bind();
	m_Registry.get<syre::Mesh>(m_Hazard).Render();

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.0325f)));
	flatShader->SetUniform("offset", glm::vec2(-0.52f, -0.95f));
	int GerValP = PlayerComponent.GetGear();
	pGearTextures[GerValP].Bind();
	m_Registry.get<syre::Mesh>(m_PGears).Render();

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.0325f)));
	flatShader->SetUniform("offset", glm::vec2(-0.48f, -0.95f));
	int GerValE = EnemyComponent.GetGear();
	eGearTextures[GerValE].Bind();
	m_Registry.get<syre::Mesh>(m_EGears).Render();
	
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.04f)));
	flatShader->SetUniform("offset", glm::vec2(-0.50f, -0.96f));
	m_Registry.get<syre::Texture>(m_AccRect).Bind();
	m_Registry.get<syre::Mesh>(m_AccRect).Render();
	
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
	flatShader->SetUniform("offset", glm::vec2(-0.5f, -0.95f));
	pneedleTextures[GerValP].Bind();
	m_Registry.get<syre::Mesh>(m_Pneedle).Render();
	
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
	flatShader->SetUniform("offset", glm::vec2(-0.5f, -0.95f));
	eneedleTextures[GerValE].Bind();
	m_Registry.get<syre::Mesh>(m_Eneedle).Render();
	
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
	flatShader->SetUniform("offset", glm::vec2(-0.5f, -0.95f));
	m_Registry.get<syre::Texture>(m_Accelerometer).Bind();
	m_Registry.get<syre::Mesh>(m_Accelerometer).Render();
	
	if (lbutton_down == false)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.87, -0.75f));
		m_Registry.get<syre::Texture>(m_GearboxLever).Bind();
		m_Registry.get<syre::Mesh>(m_GearboxLever).Render();
	}
	if (lbutton_down == true)
	{
		double* x = new double;
		double* y = new double;

		glfwGetCursorPos(window, x, y);
		if (-0.75f + 0.6f + (*y * -0.00104f) >= -0.79 && -0.75f + 0.6f + (*y * -0.00104f) <= -0.71)
		{
			flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
			flatShader->SetUniform("offset", glm::vec2(-0.87, -0.75f + 0.6f + (*y * -0.00104f)));
			m_Registry.get<syre::Texture>(m_GearboxLever).Bind();
			m_Registry.get<syre::Mesh>(m_GearboxLever).Render();
		}
		else if (-0.75f + 0.6f + (*y * -0.00104f) <= -0.79 && PlayerComponent.GetBrake() == true)
		{
			PlayerComponent.SetAction(-4);
			PlayerComponent.ChangeGears();
			PlayerComponent.ResetPed();
			lbutton_down = false;
		}
		else if (-0.75f + 0.6f + (*y * -0.00104f) >= -0.71 && PlayerComponent.GetAcc() == true)
		{
			PlayerComponent.SetAction(-5);
			PlayerComponent.ChangeGears();
			PlayerComponent.ResetPed();
			lbutton_down = false;
		}
		else
		{
			lbutton_down = false;
		}
	}


	bool Accelerate = PlayerComponent.GetAcc();
	bool Brake = PlayerComponent.GetBrake();
	if (Accelerate == false && Brake == false)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.87, -0.75f));
		gearboxTextures[0].Bind();
		m_Registry.get<syre::Mesh>(m_Gearbox).Render();
	}
	else if (Brake == true)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.87, -0.75f));
		gearboxTextures[2].Bind();
		m_Registry.get<syre::Mesh>(m_Gearbox).Render();
	}
	else if (Accelerate == true)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.125f)));
		flatShader->SetUniform("offset", glm::vec2(-0.87, -0.75f));
		gearboxTextures[1].Bind();
		m_Registry.get<syre::Mesh>(m_Gearbox).Render();
	}

	if (m_Registry.get<syre::PathAnimator>(m_PCar).HitMax() || m_Registry.get<syre::PathAnimator>(m_enemy).HitMax())
	{
		m_Registry.get<syre::PathAnimator>(m_PCar).Stop();
		m_Registry.get<syre::PathAnimator>(m_enemy).Stop();
	}
	else if (!(m_Registry.get<syre::PathAnimator>(m_PCar).HitMax() && m_Registry.get<syre::PathAnimator>(m_enemy).HitMax()))
	{
		m_Registry.get<syre::PathAnimator>(m_PCar).Resume();
		m_Registry.get<syre::PathAnimator>(m_enemy).Resume();
	}
	if (obstacleComponent.GetEnd() != true)
	{
		if (EnemyComponent.GetSabo() == false)
		{
			if (EnemyComponent.GetAction1() == -1 && EnemyComponent.GetAction2() == -1)
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
					if (EnemyComponent.GetAction1() == -1 && EnemyComponent.GetAction2() == -1)
					{
						EnemyComponent.SetAcc();
						EnemyComponent.ChangeGears();
					}
					else if (EnemyComponent.GetAction2() == -1)
					{
						if (EnemyComponent.GetAcc() == false)
						{
							EnemyComponent.SetAcc();
						}
						else if (EnemyComponent.GetAcc() == true)
						{
							EnemyComponent.ChangeGears();
						}
					}
					if (EnemyComponent.GetGear() == 6)
					{
						speedDemon = false;
					}
				}
				else if (speedDemon == false)
				{
					if (EnemyComponent.GetGear() == 1)
					{
						speedDemon = true;
					}
					EnemyComponent.SetBrk();
					EnemyComponent.ChangeGears();

				}
			}
		}
		else if (EnemyComponent.GetSabo() == true)
		{
			EnemyComponent.ChangeGears(1);
			EnemyComponent.SetAction(-4);
			EnemyComponent.SetAction(-4);
		}
		if (showGear == false)
		{
			showGear = true;
			printf("The enemy's gear level is : ");
			printf("%i", EnemyComponent.GetGear());
			printf("\n");
			printf("\n");
		}

		if (PlayerComponent.GetAction1() != -1 && PlayerComponent.GetAction2() != -1)
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
					m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(0.25,true);
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
			if (EnemyComponent.GetAction1() == 1 || EnemyComponent.GetAction2() == 1)
			{
				temp = EnemyComponent.GetGear();
				EnemyComponent.ChangeGears(PlayerComponent.GetGear());
				PlayerComponent.ChangeGears(temp);
			}
			if (PlayerComponent.GetAction1() == 1 || PlayerComponent.GetAction2() == 1)
			{
				temp = PlayerComponent.GetGear();
				PlayerComponent.ChangeGears(EnemyComponent.GetGear());
				EnemyComponent.ChangeGears(temp);
			}
			if (obstacleComponent.GetObs() == 2)
			{
				obstacleComponent.Resolve(PlayerComponent.GetGear(), EnemyComponent.GetGear());
				if (obstacleComponent.Resolve(PlayerComponent.GetGear(), EnemyComponent.GetGear() == true))
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
				PlayerComponent.SetAction(-6);
				EnemyComponent.SetAction(-6);
			}
		}
	}
	else
	{
	m_Registry.get<syre::PathAnimator>(m_PCar).IncrementSegment(2);//needs changed
	m_Registry.get<syre::PathAnimator>(m_enemy).IncrementSegment(2);//needs changed
		if (PlayerComponent.GetScore() >= EnemyComponent.GetScore())
		{
			printf("PLAYER WINS");
			m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(1.0, true);
			m_Registry.get<syre::PathAnimator>(m_enemy).SetSpeed(1.0, false);
			if (m_Registry.get<syre::PathAnimator>(m_PCar).GetHardStop())
			{
				//game is finished finished
				m_Registry.get<syre::PathAnimator>(m_enemy).Stop();
				//this is where we could go to next level
			}
		}
		else if (PlayerComponent.GetScore() < EnemyComponent.GetScore())
		{
			printf("ENEMY WINS");
			m_Registry.get<syre::PathAnimator>(m_PCar).SetSpeed(1.0, false);
			m_Registry.get<syre::PathAnimator>(m_enemy).SetSpeed(1.0, true);
		}
	}
	flatMorphShader->Bind();
	flatMorphShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.12f)));
	flatMorphShader->SetUniform("offset", glm::vec2(-0.55, -0.97f));
	flatMorphShader->SetUniform("t", 0.0f);
	m_Registry.get<syre::MorphRenderer>(m_Needle).ManualFrameSet(0);
	m_Registry.get<syre::Texture>(m_Needle).Bind();
	m_Registry.get<syre::MorphRenderer>(m_Needle).Render();
	auto pathView = m_Registry.view<syre::PathAnimator, syre::Transform>();
	for (auto entity : pathView)
	{
		auto& transform = m_Registry.get<syre::Transform>(entity);
		m_Registry.get<syre::PathAnimator>(entity).Update(transform, deltaTime);
	}

	//framebuffer bound
	framebuffer->BindBuffer(0);
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



	auto renderView = m_Registry.view<syre::Mesh,syre::Transform,syre::Texture>();
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
		listRenderView.get<syre::TransformList>(entity).ListRender(basicShader, listRenderView.get<syre::Mesh>(entity),deltaTime);
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
		morphListRenderView.get<syre::TransformList>(entity).ListRender(morphShader,morphListRenderView.get<syre::MorphRenderer>(entity));
	}

	framebuffer->UnBindBuffer();

	cubes[activeCube].bind(30);

	colorCorrect->ApplyEffect(framebuffer);

	colorCorrect->DrawToScreen();

	if (!manualCamera)
	{
		camComponent->SetPosition(m_Registry.get<syre::Transform>(m_PCar).GetPosition() + glm::vec3(1.0f, 4.0f, 5.0f));
	}
	camComponent->SetForward(glm::normalize(m_Registry.get<syre::Transform>(m_PCar).GetPosition() - camComponent->GetPosition()));
	/*m_Registry.get<syre::TransformList>(m_Particles1).UpdateCurPos(m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	m_Registry.get<syre::TransformList>(m_Particles2).UpdateCurPos(m_Registry.get<syre::Transform>(m_enemy).GetPosition());*/

	lastFrame = thisFrame;
	return 0;
}

int SceningTest::PausedUpdate()
{
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
	
	

	basicShader->Bind();
	basicShader->SetUniform("u_CamPos", camComponent->GetPosition());
	basicShader->SetUniform("playerPos", m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	basicShader->SetUniform("enemyPos", m_Registry.get<syre::Transform>(m_enemy).GetPosition());

	auto renderView = m_Registry.view<syre::Mesh, syre::Transform, syre::Texture>();
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
	morphShader->SetUniform("u_CamPos", camComponent->GetPosition());
	morphShader->SetUniform("playerPos", m_Registry.get<syre::Transform>(m_PCar).GetPosition());
	morphShader->SetUniform("enemyPos", m_Registry.get<syre::Transform>(m_enemy).GetPosition());
	morphShader->Bind();
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

	if (!manualCamera)
	{
		camComponent->SetPosition(m_Registry.get<syre::Transform>(m_PCar).GetPosition() + glm::vec3(1.0f, 4.0f, 5.0f));
	}
	camComponent->SetForward(glm::normalize(m_Registry.get<syre::Transform>(m_PCar).GetPosition() - camComponent->GetPosition()));

	flatShader->Bind();
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
	flatShader->SetUniform("offset", glm::vec2(0.0, 0.0f));
	flatShader->SetUniform("aspect", camera->GetAspect());
	m_Registry.get<syre::Texture>(m_PauseMenu).Bind();
	m_Registry.get<syre::Mesh>(m_PauseMenu).Render();

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(1.2f)));
	flatShader->SetUniform("offset", glm::vec2(0.0, 0.0f));
	flatShader->SetUniform("aspect", camera->GetAspect());
	m_Registry.get<syre::Texture>(m_TransparentBlack).Bind();
	m_Registry.get<syre::Mesh>(m_TransparentBlack).Render();


	lastFrame = thisFrame;
	return returning;
}

void SceningTest::ImGUIUpdate()
{
	//auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
		// Implementation new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		// ImGui context new frame
		ImGui::NewFrame();
		AudioEngine& audio = AudioEngine::Instance();
		int pauseStatus = audio.GetGlobalParameterValue("IsPaused");
		float sfxVol = audio.GetGlobalParameterValue("SFXVolume");
		float musVol = audio.GetGlobalParameterValue("MusicVolume");

		if (ImGui::Begin("Debug")) {
			// Render our GUI stuff
			ImGui::SliderInt("Active CoCo Effect", &activeCube, 0, cubes.size() - 1);
			ImGui::Text("0 is Neutral, 1 is Cool, 2 is Warm, 3 is Custom");
			ImGui::Checkbox("Ambient Lighting", &ambientOn);
			ImGui::Checkbox("Diffuse Lighting", &diffuseOn);
			ImGui::Checkbox("Specular Lighting", &specularOn);
			ImGui::Checkbox("Emissive Car Lighting", &carLighting);
			ImGui::Checkbox("Specular Ramping", &rampOnSpec);
			ImGui::Checkbox("Diffuse Ramping", &rampOnDiff);
			//ImGui::SliderInt("IsPaused", &pauseStatus, 0, 1);
			ImGui::SliderFloat("Effects Volume", &sfxVol, 0.f, 1.f);
			ImGui::SliderFloat("Music Volume", &musVol, 0.f, 1.f);




			


			/*auto movable = m_Registry.view<syre::Mesh, syre::Transform>();
			auto& camComponent = camera;
			glm::vec3 camPos = camComponent->GetPosition();
			if (ImGui::Button(manualCamera?"Auto Camera": "Manual Camera"))
			{
				manualCamera = !manualCamera;
			}
			if (manualCamera)
			{
				ImGui::SliderFloat3("Camera Position", &camPos.x,-200.f, 200.f);
			}
			camComponent->SetPosition(camPos);*/
			
		}
		ImGui::End();
		audio.SetGlobalParameter("IsPaused",pauseStatus);
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

Camera::sptr& SceningTest::GetCam()
{
	// TODO: insert return statement here
	return camera;
}

int SceningTest::KeyEvents(float delta)
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
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS&&escRelease)
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
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS&&escRelease)
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
			//printf("Mouse at X %f Y %f\n", *x, *y);
			if (m_Registry.get<syre::PathAnimator>(m_PCar).HitMax() || m_Registry.get<syre::PathAnimator>(m_enemy).HitMax())
			{
				for (float i = 0; i <= 5; i++)
				{
					if ((i * 165) + 429 <= *x && (i + 1) * 165 + 429 >= *x && *y >= 457 && *y <= 706 && PlayerComponent.GetCard(i, true) != -1)
					{
						if (PlayerComponent.GetCard(i, true) == 2)
						{
							temp = PlayerComponent.GetGear();
							PlayerComponent.PlayCard(i, EnemyComponent.GetGear());
							EnemyComponent.ChangeGears(temp);
						}
						else
						{
							PlayerComponent.PlayCard(i, 0);
						}
						if (PlayerComponent.GetCard(i, true) == 5)
						{
							EnemyComponent.SetSabo();
							PlayerComponent.PlayCard(i, 0);
						}
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
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			lbutton_down = false;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			m_Registry.get<syre::PathAnimator>(m_PCar).Reset();
		}
		camComponent->SetPosition(curCamPos);
		return 0;
	}
}

