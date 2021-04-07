#include "MenuScreen.h"

MenuScreen::MenuScreen(GLFWwindow* inWind)
{
	window = inWind;
}

void MenuScreen::Start()
{
	camera = Camera::Create();
	auto& camComponent = camera;
	camComponent->SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camComponent->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camComponent->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camComponent->SetFovDegrees(100.0f); // Set an initial FOV

	m_MenuImage = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(m_MenuImage, "objects/Menu_Plane.obj");
	m_Registry.emplace<syre::Transform>(m_MenuImage, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_MenuImage, "images/MenuMod.png");

	flatShader = Shader::Create();
	flatShader->LoadShaderPartFromFile("flatVert.glsl", GL_VERTEX_SHADER);
	flatShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatShader->Link();

	AudioEngine& engine = AudioEngine::Instance();

	AudioEvent& music = engine.GetEvent("Menu Music");
	music.Play();

}

int MenuScreen::Update()
{
	AudioEngine& engine = AudioEngine::Instance();

	AudioEvent& music = engine.GetEvent("Menu Music");
	AudioBus& musicBus = engine.GetBus("Music");
	engine.Update();

	flatShader->Bind();
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(-0.68f)));
	flatShader->SetUniform("offset", glm::vec2(-0.3f, -0.15f));
	flatShader->SetUniform("aspect", camera->GetAspect());
	m_Registry.get<syre::Texture>(m_MenuImage).Bind();
	m_Registry.get<syre::Mesh>(m_MenuImage).Render();

	double* x = new double;
	double* y = new double;

	glfwGetCursorPos(window, x, y);
	printf("Mouse at X %f Y %f\n", *x, *y);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (153.0f < *x && *x < 330.f)
		{
			if (266.0f < *y && *y < 333.0f)
			{
				return 3;
			}
			if (467.0f<*y&&*y<550.f)
			{
				clickTimes++;
				if (clickTimes > 20)
				{
					won = true;

				}
			}
			else if (570.0f < *y &&*y< 638.0f)
			{
				return -2;
			}
		}
	}

	return 0;
}

void MenuScreen::ImGUIUpdate()
{
}

Camera::sptr& MenuScreen::GetCam()
{
	// TODO: insert return statement here
	return camera;
}

int MenuScreen::GetID()
{
	return 3;
}
