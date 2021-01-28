#include "MidGameMenu.h"

MidGameMenu::MidGameMenu(GLFWwindow* inWind)
{
	window = inWind;
}

void MidGameMenu::Start()
{
	camera = Camera::Create();
	auto& camComponent = camera;
	camComponent->SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camComponent->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camComponent->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camComponent->SetFovDegrees(100.0f); // Set an initial FOV

	m_MenuImage = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(m_MenuImage, "RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_MenuImage, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_MenuImage, "MidGameMenu.png");

	flatShader = Shader::Create();
	flatShader->LoadShaderPartFromFile("flatVert.glsl", GL_VERTEX_SHADER);
	flatShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatShader->Link();
}

int MidGameMenu::Update()
{
	flatShader->Bind();
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
	flatShader->SetUniform("offset", glm::vec2(0.0f, 0.0f));
	flatShader->SetUniform("aspect", 1.0f);//this is atypical
	m_Registry.get<syre::Texture>(m_MenuImage).Bind();
	m_Registry.get<syre::Mesh>(m_MenuImage).Render();

	double* x = new double;
	double* y = new double;

	glfwGetCursorPos(window, x, y);
	//printf("Mouse at X %f Y %f\n", *x, *y);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (47.0f < *x && *x < 347.f)
		{
			if (84.0f < *y && *y < 168.0f)
			{

				return 1;
			}
		}
	}

	return 0;
}

void MidGameMenu::ImGUIUpdate()
{
}

Camera::sptr& MidGameMenu::GetCam()
{
	// TODO: insert return statement here
	return camera;
}
