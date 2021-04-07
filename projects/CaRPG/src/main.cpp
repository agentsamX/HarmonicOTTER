
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>

#include "SceneParent.h"
#include "SceningTest.h"
#include "MenuScreen.h"
#include "MidGameMenu.h"
#include "Scene2.h"
#include "TutorialScene.h"

//taken from CG tutorials
extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x01;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 0x01;
}
void GlDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::string sourceTxt;
	switch (source) {
	case GL_DEBUG_SOURCE_API: sourceTxt = "DEBUG"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceTxt = "WINDOW"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceTxt = "SHADER"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY: sourceTxt = "THIRD PARTY"; break;
	case GL_DEBUG_SOURCE_APPLICATION: sourceTxt = "APP"; break;
	case GL_DEBUG_SOURCE_OTHER: default: sourceTxt = "OTHER"; break;
	}
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW:          LOG_INFO("[{}] {}", sourceTxt, message); break;
	case GL_DEBUG_SEVERITY_MEDIUM:       LOG_WARN("[{}] {}", sourceTxt, message); break;
	case GL_DEBUG_SEVERITY_HIGH:         LOG_ERROR("[{}] {}", sourceTxt, message); break;
#ifdef LOG_GL_NOTIFICATIONS
	case GL_DEBUG_SEVERITY_NOTIFICATION: LOG_INFO("[{}] {}", sourceTxt, message); break;
#endif
	default: break;
	}
}

GLFWwindow* window;
Camera::sptr camera = nullptr;

void GlfwWindowResizedCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	camera->ResizeWindow(width, height);
}
bool initGLFW() {
	if (glfwInit() == GLFW_FALSE) {
		LOG_ERROR("Failed to initialize GLFW");
		return false;
	}

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	//Create a new GLFW window
	window = glfwCreateWindow(1280,720, "CaRPG by Harmonic Industries", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set our window resized callback
	glfwSetWindowSizeCallback(window, GlfwWindowResizedCallback);

	return true;
}

bool initGLAD() {
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		LOG_ERROR("Failed to initialize Glad");
		return false;
	}
	return true;
}

void InitImGui() {
	// Creates a new ImGUI context
	ImGui::CreateContext();
	// Gets our ImGUI input/output 
	ImGuiIO& io = ImGui::GetIO();
	// Enable keyboard navigation
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// Allow docking to our window
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// Allow multiple viewports (so we can drag ImGui off our window)
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	// Allow our viewports to use transparent backbuffers
	io.ConfigFlags |= ImGuiConfigFlags_TransparentBackbuffers;

	// Set up the ImGui implementation for OpenGL
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");

	// Dark mode FTW
	ImGui::StyleColorsDark();

	// Get our imgui style
	ImGuiStyle& style = ImGui::GetStyle();
	//style.Alpha = 1.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.8f;
	}
}

void ShutdownImGui()
{
	// Cleanup the ImGui implementation
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	// Destroy our ImGui context
	ImGui::DestroyContext();
}

std::vector<std::function<void()>> imGuiCallbacks;
void RenderImGui() {
	// Implementation new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	// ImGui context new frame
	ImGui::NewFrame();

	if (ImGui::Begin("Debug")) {
		// Render our GUI stuff
		for (auto& func : imGuiCallbacks) {
			func();
		}
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

	// If we have multiple viewports enabled (can drag into a new window)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		// Update the windows that ImGui is using
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		// Restore our gl context
		glfwMakeContextCurrent(window);
	}
}
//end of cg tutorial copy

int main()
{
	//cg tutorial
	Logger::Init();

	if (!initGLFW())
		return 1;

	if (!initGLAD())
		return 1;

	Framebuffer::InitFullscreenQuad();

	//glEnable(GL_DEBUG_OUTPUT);
	//turn off for build for gdw
	glDebugMessageCallback(GlDebugMessage, nullptr);
	//end of cg tutorial


	MidGameMenu* midMenu = new MidGameMenu(window);

	std::vector<syre::SceneParent*> scenes;////////////
	scenes.push_back(new MenuScreen(window));
	scenes.push_back(new SceningTest(window));//////////////////////
	
	syre::SceneParent* curScene = scenes[0];
	
	glEnable(GL_DEPTH_TEST);


	int width = 0;
	int height = 0;
	glfwGetWindowSize(window, &width, &height);

	glm::mat4 transform = glm::mat4(1.0f);
	
	glDisable(GL_CULL_FACE);

	InitImGui();

	AudioEngine& engine = AudioEngine::Instance();
	engine.Init();
	engine.LoadBank("Master");
	engine.LoadBank("Master.strings");
	engine.LoadBus("Music", "{65daa684-95d9-408f-b23f-d587e44e016b}");
	engine.CreateEventW("Menu Music", "{aefe09ea-1546-4ae9-9982-bf60713fdd02}");
	engine.CreateEventW("Ambient", "{18c986e1-88b0-45ce-82c7-567d3447f2e8}");
	//effects
	engine.CreateEventW("Accelerate", "{e960091c-f5a8-442d-a048-d368c7084021}");
	engine.CreateEventW("Brake", "{fa0e36c1-c1c1-48bf-838c-e8b3762717e1}");
	engine.CreateEventW("E-Brake", "{91e753b6-4232-4b65-ae35-bbf0b2b21a98}");
	engine.CreateEventW("Drift", "{3eb39553-5d08-456c-998b-822942c1f860}");
	engine.CreateEventW("MultiNitro", "{6d8f789b-95db-4007-bd66-f26c1f377b3c}");
	engine.CreateEventW("Nitro", "{36f21e41-ce5e-49c7-b670-4841094f5242}");
	engine.CreateEventW("Quick Shift", "{11071f63-d5b9-4ff5-bf03-13eed2834d51}");
	engine.CreateEventW("Sabotage", "{df8e111c-4f91-43c6-9247-fa321d748db8}");
	engine.CreateEventW("Slipstream", "{50d08bc6-b9f1-4411-906f-69506bd36f13}");
	//tut
	engine.CreateEventW("Tut-AfterFirstTurn", "{01b60b7e-4a57-4659-a8b3-f6cae078bd56}");
	engine.CreateEventW("Tut-AfterUTurn", "{02ae5be0-c7a6-49be-8936-8e882f5e799f}");
	engine.CreateEventW("Tut-BeforeChicane", "{e6a8f8be-cea9-4cb1-a53c-6a46fb291d84}");
	engine.CreateEventW("Tut-EndOfRace", "{7f7b8204-b9b5-4fa6-9cc3-ef6d9a3926d5}");
	engine.CreateEventW("Tut-StartOfRace", "{8cf9dd30-c887-433a-8ccc-4a0e668247a6}");

	
	curScene->Start();

	camera = curScene->GetCam();
	GlfwWindowResizedCallback(window, 1280, 720);


	/*glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
	glfwSetCursor(window, cursor);
	*/
	int returned = 0;
	bool wonTut = false;
	bool won1 = false;
	bool won2 = false;
	bool debugMenu = false;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); ////////
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		returned = curScene->Update();
		if (returned != 0)
		{
			if (curScene->GetWon())
			{
				int temp = curScene->GetID();
				if (temp == 0)
					wonTut = true;
				else if (temp == 1)
					won1 = true;
				else if (temp == 2)
					won2 = true;
				else if (temp == 3)
					debugMenu = true;
			}

			if(returned==1)
			{
				delete scenes[scenes.size() - 1];
				scenes.pop_back();
				scenes.push_back(new SceningTest(window)); //////////////////////
				curScene = scenes[1];

				curScene->Start();
				camera = curScene->GetCam();
				GlfwWindowResizedCallback(window, 1280, 720);
				curScene->Update();
			}
			else if (returned == 2)
			{
				delete scenes[scenes.size() - 1];
				scenes.pop_back();
				scenes.push_back(new Scene2(window)); //////////////////////
				curScene = scenes[1];

				curScene->Start();
				camera = curScene->GetCam();
				GlfwWindowResizedCallback(window, 1280, 720);
				curScene->Update();
			}
			else if (returned == 3)
			{
				delete scenes[scenes.size() - 1];
				scenes.pop_back();
				scenes.push_back(new TutorialScene(window)); //////////////////////
				curScene = scenes[1];

				curScene->Start();
				camera = curScene->GetCam();
				GlfwWindowResizedCallback(window, 1280, 720);
				curScene->Update();
			}
			else if (returned == -2)
			{
				break;
			}
			else if (returned == -1)
			{
				curScene = midMenu;

				midMenu->SetWins(wonTut, won1, won2);

				curScene->Start();
				camera = curScene->GetCam();
				GlfwWindowResizedCallback(window, 1280, 720);
				curScene->Update();
			}
			

		}
		if(debugMenu)
			curScene->ImGUIUpdate();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	ShutdownImGui();
	return 0;
} 
