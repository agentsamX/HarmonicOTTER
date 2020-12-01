#pragma once

#include "entt.hpp"
#include "Camera.h"
#include "PathAnimator.h"
#include "Shader.h"
#include "Transform.h"
#include "TransformList.h"
#include "Texture.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>


namespace syre {

	class SceneParent
	{
	public:
		SceneParent();
		~SceneParent();
		virtual void Start();
		virtual void Update();
		virtual void ImGUIUpdate();
		GLFWwindow* window;
		virtual Camera::sptr& GetCam();

	protected:
		entt::registry m_Registry;
		double lastFrame;
		double thisFrame;
		Camera::sptr camera;

	};
}