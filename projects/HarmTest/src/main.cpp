#include "Mesh.h"
#include "SceneParent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
int main()
{
	GLFWwindow* window;
	glfwInit();
	//Create a new GLFW window
	window = glfwCreateWindow(800, 800, "INFR1350U", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	syre::SceneParent* curScene = new syre::SceneParent;
	std::string fileName = "monkey.obj";
	entt::entity test = curScene->m_Registry.create();
	curScene->m_Registry.emplace<syre::Mesh>(test, fileName);
	while (true)
	{
		curScene->m_Registry.get<syre::Mesh>(test).Render();

	}

	return 0;
} 
