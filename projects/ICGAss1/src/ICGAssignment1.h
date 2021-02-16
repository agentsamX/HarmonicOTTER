#pragma once
#include "SceneParent.h"
#include <cstdlib>
#include <ctime>
class ICGAssignment1
	: public syre::SceneParent
{
public:
	ICGAssignment1(GLFWwindow* inWind);
	void Start();
	int Update();
	void ImGUIUpdate();
	Camera::sptr& GetCam();

private:
	Shader::sptr assignmentShader;


	bool ambientOn=true;
	bool diffuseOn=true;
	bool specularOn=true;
	bool rainbowOn = false;

	entt::entity car;
	entt::entity glass;
	entt::entity pedestal;
};