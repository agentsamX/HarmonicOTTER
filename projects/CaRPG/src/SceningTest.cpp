#include "SceningTest.h"
#include "Cars.h"

SceningTest::SceningTest(GLFWwindow* inWind)
{
	window = inWind;
}

void SceningTest::Start()
{
	std::string fileName = "monkey.obj";
	entt::entity camera = m_Registry.create();
	entt::entity testModel = m_Registry.create();
	entt::entity shader = m_Registry.create();
	entt::entity Car = m_Registry.create();
	entt::entity Track = m_Registry.create();

	//cards
	Card1 = m_Registry.create();
	Card2 = m_Registry.create();
	Card3 = m_Registry.create();
	Card4 = m_Registry.create();
	Card5 = m_Registry.create();
	entt::entity morphTest = m_Registry.create();
	m_Registry.emplace<syre::MorphRenderer>(morphTest);
	m_Registry.emplace<syre::Texture>(morphTest, "Car2.png");
	m_Registry.emplace<syre::Transform>(morphTest, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.get<syre::MorphRenderer>(morphTest).AddFrame("cubeMorphTest_1.obj");
	m_Registry.get<syre::MorphRenderer>(morphTest).AddFrame("cubeMorphTest_2.obj");
	m_Registry.get<syre::MorphRenderer>(morphTest).AddFrame("cubeMorphTest_3.obj");
	m_Registry.get<syre::MorphRenderer>(morphTest).AddFrame("cubeMorphTest_2.obj");


	m_Registry.emplace<syre::Mesh>(Track, "Track1.obj");
	m_Registry.emplace<syre::Transform>(Track, glm::vec3(-30.0f, 125.0f, -0.5f), glm::vec3(90.0f, 0.0f, 180.0f), glm::vec3(2.2f));
	m_Registry.emplace<syre::Texture>(Track, "PossibleRoad.png");

	m_Shader = shader;
	m_Camera = camera;
	m_PCar = Car;
	
	m_Registry.emplace<Cars>(Car);
	m_Registry.emplace<syre::Mesh>(Car, "Car2.obj");
	m_Registry.emplace<syre::Transform>(Car, glm::vec3(6.0f, 0.0f, 0.0f),glm::vec3(90.f,0.0f,0.0f),glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(Car, "Car2.png");
	m_Registry.emplace<syre::PathAnimator>(Car,syre::PathType::BEZIER);
	auto& carPath = m_Registry.get<syre::PathAnimator>(Car);

	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //start point
	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of first straight
	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(6.0f, -70.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(35.0f, -98.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of first turn /////////fix curve
	carPath.AddPoint(glm::vec3(35.0f, -98.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(3.0f, -104.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(110.0f, -101.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //end of 2nd straight
	carPath.AddPoint(glm::vec3(110.0f, -101.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(110.0f, -101.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 2nd turn /////////////
	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(155.0f, -140.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(155.0f, -205.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of 3rd str 
	carPath.AddPoint(glm::vec3(155.0f, -205.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(155.0f, -205.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(185.0f, -246.f, 0.0f), glm::vec3(90.0f, 0.0f, 90.0f)); //mid s  //////////
	carPath.AddPoint(glm::vec3(185.0f, -246.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(185.0f, -246.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of S /////////////
	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(236.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(236.f, -420.f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); //end of str
	carPath.AddPoint(glm::vec3(236.f, -420.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(236.f, -420.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(198.f, -458.f, 0.0f), glm::vec3(90.0f, 0.0f, -90.0f)); //mid u turn////////////
	carPath.AddPoint(glm::vec3(198.f, -458.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(198.f, -458.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(161.f, -416.f, 0.0f), glm::vec3(90.0f, 0.0f, -180.0f)); //end u turn/////////////////
	carPath.AddPoint(glm::vec3(161.f, -416.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(161.f, -416.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //end turn ///////
	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(134.f, -381.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(63.f, -373.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //str
	carPath.AddPoint(glm::vec3(63.f, -373.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(63.f, -373.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //turn///////////
	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(24.f, -400.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(16.f, -470.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //str
	carPath.AddPoint(glm::vec3(16.f, -470.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(16.f, -470.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-26.f, -502.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid s //////
	carPath.AddPoint(glm::vec3(-26.f, -502.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-26.f, -502.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-73.f, -537.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end s //////
	carPath.AddPoint(glm::vec3(-73.f, -537.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-73.f, -537.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-114.f, -570.f, 0.0f), glm::vec3(90.0f, 0.0f, -100.0f)); //mid u //////
	carPath.AddPoint(glm::vec3(-114.f, -570.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-114.f, -570.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //end u turn //////
	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-148.f, -529.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-130.f, -393.f, 0.0f), glm::vec3(90.0f, 0.0f, -190.0f)); //str
	carPath.AddPoint(glm::vec3(-130.f, -393.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-130.f, -393.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-88.f, -365.f, 0.0f), glm::vec3(90.0f, 0.0f, -280.0f)); //mid u ////////
	carPath.AddPoint(glm::vec3(-88.f, -365.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-88.f, -365.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-74.f, -405.f, 0.0f), glm::vec3(90.0f, 0.0f, -10.0f)); //end u ////////
	carPath.AddPoint(glm::vec3(-74.f, -405.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-74.f, -405.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-56.f, -450.f, 0.0f), glm::vec3(90.0f, 0.0f, 80.0f)); //mid u ////////
	carPath.AddPoint(glm::vec3(-56.f, -450.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-56.f, -450.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //end u ////////
	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-9.f, -415.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(1.5f, -346.f, 0.0f), glm::vec3(90.0f, 0.0f, 170.0f)); //str
	carPath.AddPoint(glm::vec3(1.5f, -346.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(1.5f, -346.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(90.0f, 0.0f, 250.0f)); //turn ////////
	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-64.f, -289.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-117.f, -286.f, 0.0f), glm::vec3(90.0f, 0.0f, 260.0f)); //str
	carPath.AddPoint(glm::vec3(-117.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-117.f, -286.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-133.f, -252.f, 0.0f), glm::vec3(90.0f, 0.0f, 190.0f)); // mid u ///////////
	carPath.AddPoint(glm::vec3(-133.f, -252.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-133.f, -252.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //end u //////////
	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-107.f, -214.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-34.f, -210.f, 0.0f), glm::vec3(90.0f, 0.0f, 100.0f)); //str
	carPath.AddPoint(glm::vec3(-34.f, -210.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-34.f, -210.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(8.f, -160.f, 0.0f), glm::vec3(90.0f, 0.0f, 190.0f)); //mid u/////////////
	carPath.AddPoint(glm::vec3(8.f, -160.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(8.f, -160.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //end u ////////
	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-36.f, -125.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-108.f, -129.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //str
	carPath.AddPoint(glm::vec3(-108.f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-108.f, -129.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); //turn ///////
	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-145.f, -93.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-145.f, -25.f, 0.0f), glm::vec3(90.0f, 0.0f, 180.0f)); //str
	carPath.AddPoint(glm::vec3(-145.f, -25.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-145.f, -25.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-195.f, 14.f, 0.0f), glm::vec3(90.0f, 0.0f, 270.0f)); //mid u////////////
	carPath.AddPoint(glm::vec3(-195.f, 14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-195.f, 14.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(90.0f, 0.0f, 340.0f)); //end u ///////
	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-226.f, -3.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(90.0f, 0.0f, 340.0f)); //str
	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	carPath.AddPoint(glm::vec3(-276.f, -119.f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));


	
	
	

	carPath.SpeedControl();


	m_Registry.emplace<syre::Mesh>(testModel, fileName);
	m_Registry.emplace<syre::Transform>(testModel,glm::vec3(2.0f,2.0f,2.0f));
	m_Registry.emplace<syre::Texture>(testModel, "Slipstream.png");

	//cards

	m_Registry.emplace<syre::Mesh>(Card1, "Card.obj");
	m_Registry.emplace<syre::Transform>(Card1, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2f));
	m_Registry.emplace<syre::Texture>(Card1, "NO2.png");

	m_Registry.emplace<syre::Mesh>(Card2, "Card.obj");
	m_Registry.emplace<syre::Transform>(Card2, glm::vec3(-3.0f, 0.0f, 2.0f),glm::vec3(0.0,0.0,0.0),glm::vec3(0.2f));
	m_Registry.emplace<syre::Texture>(Card2, "Slipstream.png");

	m_Registry.emplace<syre::Mesh>(Card3, "Card.obj");
	m_Registry.emplace<syre::Transform>(Card3, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2f));
	m_Registry.emplace<syre::Texture>(Card3, "Drift.png");

	m_Registry.emplace<syre::Mesh>(Card4, "Card.obj");
	m_Registry.emplace<syre::Transform>(Card4, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2f));


	m_Registry.emplace<syre::Mesh>(Card5, "Card.obj");
	m_Registry.emplace<syre::Transform>(Card5, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2f));

	flatShader = Shader::Create();
	flatShader->LoadShaderPartFromFile("flatVert.glsl", GL_VERTEX_SHADER);
	flatShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatShader->Link();




	m_Registry.emplace<Camera::sptr>(camera);
	m_Registry.emplace<Shader::sptr>(shader);

	auto& shaderComponent = m_Registry.get<Shader::sptr>(shader);
	shaderComponent = Shader::Create();
	shaderComponent->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	shaderComponent->LoadShaderPartFromFile("frag_shader.glsl", GL_FRAGMENT_SHADER);
	shaderComponent->Link();

	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	float     lightAmbientPow = 0.1f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.5f;
	float     shininess = 4.0f;
	// These are our application / scene level uniforms that don't necessarily update
	// every frame
	shaderComponent->SetUniform("u_LightPos", lightPos);
	shaderComponent->SetUniform("u_LightCol", lightCol);
	shaderComponent->SetUniform("u_AmbientLightStrength", lightAmbientPow);
	shaderComponent->SetUniform("u_SpecularLightStrength", lightSpecularPow);
	shaderComponent->SetUniform("u_AmbientCol", ambientCol);
	shaderComponent->SetUniform("u_AmbientStrength", ambientPow);
	shaderComponent->SetUniform("u_Shininess", shininess);


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

	auto& camComponent = m_Registry.get<Camera::sptr>(camera);
	camComponent = Camera::Create();
	camComponent->SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camComponent->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camComponent->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camComponent->SetFovDegrees(100.0f); // Set an initial FOV

	lastFrame = glfwGetTime();
}

void SceningTest::Update()
{
	
	thisFrame = glfwGetTime();
	float deltaTime = thisFrame - lastFrame;
	auto& camComponent = m_Registry.get<Camera::sptr>(m_Camera);
	auto& shaderComponent = m_Registry.get<Shader::sptr>(m_Shader);
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
	glm::vec3 camX = glm::cross(camComponent->GetForward(), camComponent->GetUp());
	KeyEvents(deltaTime);
	flatShader->Bind();
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
	for (int i = 0; i <= 4; i++)
	{
		//Card slot 1
		flatShader->SetUniform("offset", glm::vec2(-.4f, -.7f));
		
		/*
		//Card slot 5

		if (PlayerComponent.GetCard(i, true) == 1 && i == 4)
		{
			m_Registry.get<syre::Texture>(Card1).Bind();
			m_Registry.get<syre::Mesh>(Card5).Render();
		}
		if (PlayerComponent.GetCard(i, true) == 2 && i == 4)
		{
			m_Registry.get<syre::Texture>(Card2).Bind();
			m_Registry.get<syre::Mesh>(Card5).Render();
		}
		if (PlayerComponent.GetCard(i, true) == 3 && i == 4)
		{
			m_Registry.get<syre::Texture>(Card3).Bind();
			m_Registry.get<syre::Mesh>(Card5).Render();
		}
		if (PlayerComponent.GetCard(i, true) == 4 && i == 4)
		{
			m_Registry.get<syre::Texture>(Card4).Bind();
			m_Registry.get<syre::Mesh>(Card5).Render();
		}
		*/
	}
	auto pathView = m_Registry.view<syre::PathAnimator, syre::Transform>();
	for (auto entity : pathView)
	{
		auto& transform = m_Registry.get<syre::Transform>(entity);
		m_Registry.get<syre::PathAnimator>(entity).Update(transform, deltaTime);
	}


	shaderComponent->Bind();
	shaderComponent->SetUniform("u_CamPos", camComponent->GetPosition());
	auto renderView = m_Registry.view<syre::Mesh,syre::Transform,syre::Texture>();
	for (auto entity : renderView)
	{
		glm::mat4 transform = renderView.get<syre::Transform>(entity).GetModelMat();
		shaderComponent->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		shaderComponent->SetUniformMatrix("u_Model", transform);
		shaderComponent->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		renderView.get<syre::Texture>(entity).Bind();
		renderView.get<syre::Mesh>(entity).Render();
	}
	auto morphRenderView = m_Registry.view<syre::MorphRenderer, syre::Transform, syre::Texture>();
	morphShader->Bind();
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
	if (!manualCamera)
	{
		camComponent->SetPosition(m_Registry.get<syre::Transform>(m_PCar).GetPosition() + glm::vec3(1.0f, 3.0f, 3.0f));
	}
	camComponent->SetForward(glm::normalize(m_Registry.get<syre::Transform>(m_PCar).GetPosition() - camComponent->GetPosition()));

	lastFrame = thisFrame;
}

void SceningTest::ImGUIUpdate()
{
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
		// Implementation new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		// ImGui context new frame
		ImGui::NewFrame();

		if (ImGui::Begin("Debug")) {
			// Render our GUI stuff
			

			auto movable = m_Registry.view<syre::Mesh, syre::Transform>();
			auto& camComponent = m_Registry.get<Camera::sptr>(m_Camera);
			glm::vec3 camPos = camComponent->GetPosition();
			if (ImGui::Button(manualCamera?"Auto Camera": "Manual Camera"))
			{
				manualCamera = !manualCamera;
			}
			if (manualCamera)
			{
				ImGui::SliderFloat3("Camera Position", &camPos.x,-200.f, 200.f);
			}
			camComponent->SetPosition(camPos);
			ImGui::End();
		}

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

void SceningTest::KeyEvents(float delta)
{
	auto& camComponent = m_Registry.get<Camera::sptr>(m_Camera);
	auto& PlayerComponent = m_Registry.get<Cars>(m_PCar);
	glm::vec3 curCamPos = camComponent->GetPosition();
	glm::vec3 curCamFor = camComponent->GetForward();

	if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
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
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double* x = new double;
		double* y = new double;

		glfwGetCursorPos(window, x,y);
		printf("Mouse at X %f Y %f\n", *x, *y);
		if (*x >= 320.0 && *x <= 480.0 && *y <= 798.0 && *y >= 560.0)
		{
			PlayerComponent.PlayCard(0, 0);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		m_Registry.get<syre::PathAnimator>(m_PCar).Reset();
	}
	camComponent->SetPosition(curCamPos);
}

