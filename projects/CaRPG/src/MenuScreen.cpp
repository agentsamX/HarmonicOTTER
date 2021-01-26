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
}

int MenuScreen::Update()
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		return 1;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		return 2;
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
