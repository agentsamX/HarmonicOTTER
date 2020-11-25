#pragma once

#include "entt.hpp"
#include "Mesh.h"
#include "Camera.h"
#include "MorphRenderer.h"
#include "Shader.h"
#include "Transform.h"
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
	protected:
		entt::registry m_Registry;
		double lastFrame;
		double thisFrame;

	};
}