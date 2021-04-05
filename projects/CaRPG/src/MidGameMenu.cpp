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
	m_Registry.emplace<syre::Mesh>(m_MenuImage, "objects/RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_MenuImage, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_MenuImage, "images/MidGameMenu2.png");

	m_winBadge = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(m_winBadge, "objects/RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_winBadge, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_winBadge, "images/Completed.png");

	m_MapScreen = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(m_MapScreen, "objects/RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_MapScreen, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_MapScreen, "images/Final A-Star.png");

	m_CarIcon = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(m_CarIcon, "objects/RoadHazard.obj");
	m_Registry.emplace<syre::Transform>(m_CarIcon, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(m_CarIcon, "images/Completed.png");

	flatShader = Shader::Create();
	flatShader->LoadShaderPartFromFile("flatVert.glsl", GL_VERTEX_SHADER);
	flatShader->LoadShaderPartFromFile("flatFrag.glsl", GL_FRAGMENT_SHADER);
	flatShader->Link();
}

int MidGameMenu::Update()
{
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);

	flatShader->Bind();
	if (m_won1)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.05f)));
		flatShader->SetUniform("offset", glm::vec2(-0.55f, -0.05f));
		flatShader->SetUniform("aspect", float(width) / float(height));//this is atypical
		m_Registry.get<syre::Texture>(m_winBadge).Bind();
		m_Registry.get<syre::Mesh>(m_winBadge).Render();
	}
	if (m_won2)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.05f)));
		flatShader->SetUniform("offset", glm::vec2(-0.55f, -0.425f));
		flatShader->SetUniform("aspect", float(width) / float(height));//this is atypical
		m_Registry.get<syre::Texture>(m_winBadge).Bind();
		m_Registry.get<syre::Mesh>(m_winBadge).Render();
	}
	if (m_wonTut)
	{
		flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.05f)));
		flatShader->SetUniform("offset", glm::vec2(-0.55f, 0.325f));
		flatShader->SetUniform("aspect", float(width) / float(height));//this is atypical
		m_Registry.get<syre::Texture>(m_winBadge).Bind();
		m_Registry.get<syre::Mesh>(m_winBadge).Render();
	}


	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(menuScale)));
	flatShader->SetUniform("offset", menuPos);
	flatShader->SetUniform("aspect", float(width) / float(height));//this is atypical
	m_Registry.get<syre::Texture>(m_CarIcon).Bind();
	m_Registry.get<syre::Mesh>(m_CarIcon).Render();

	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.51)));
	flatShader->SetUniform("offset", glm::vec2(0.451f,0.0f));
	flatShader->SetUniform("aspect", float(width) / float(height));//this is atypical
	m_Registry.get<syre::Texture>(m_MapScreen).Bind();
	m_Registry.get<syre::Mesh>(m_MapScreen).Render();
	
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
	flatShader->SetUniform("offset", glm::vec2(0.0f,0.0f));
	flatShader->SetUniform("aspect", 1.0f);//this is atypical
	m_Registry.get<syre::Texture>(m_MenuImage).Bind();
	m_Registry.get<syre::Mesh>(m_MenuImage).Render();
	

	double* x = new double;
	double* y = new double;

	glfwGetCursorPos(window, x, y);
	printf("Mouse at X %f Y %f\n", *x, *y);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (47.0f < *x && *x < 347.f)
		{
			if (200.0f < *y && *y < 283.0f)
			{
				if(!m_wonTut)
					return 3;
			}
			else if (336.0f < *y && *y < 419.0f)
			{
				if(!m_won1)
					return 1;
			}
			else if (471.0f < *y && *y < 556.0f)
			{
				if(!m_won2)
					return 2;
			}

		}
	}

	return 0;
}

void MidGameMenu::ImGUIUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

	if (ImGui::Begin("Debug"))
	{
		ImGui::SliderFloat("Scale", &menuScale, 0.0, 0.5);
		ImGui::SliderFloat2("Pos", &menuPos.x, -1.0f, 1.0f);
	}

	ImGui::End();

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

void MidGameMenu::SetWins(bool tut, bool b1, bool b2)
{
	m_wonTut = tut;
	m_won2 = b2;
	m_won1 = b1;
}

Camera::sptr& MidGameMenu::GetCam()
{
	// TODO: insert return statement here
	return camera;
}
