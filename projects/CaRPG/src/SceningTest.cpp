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

	//cards
	NO2Card = m_Registry.create();
	SlipstreamCard = m_Registry.create();


	m_Shader = shader;
	m_Camera = camera;
	m_PCar = Car;
	
	m_Registry.emplace<Cars>(Car);
	m_Registry.emplace<syre::Mesh>(Car, "Car2.obj");
	m_Registry.emplace<syre::Transform>(Car, glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(90.f,0.0f,0.0f),glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(Car, "Car2.png");
	m_Registry.emplace<syre::MorphRenderer>(Car);

	m_Registry.emplace<syre::Mesh>(testModel, fileName);
	m_Registry.emplace<syre::Transform>(testModel,glm::vec3(2.0f,2.0f,2.0f));
	m_Registry.emplace<syre::Texture>(testModel, "Slipstream.png");

	//cards
	m_Registry.emplace<syre::Mesh>(NO2Card, "CardNO2.obj");
	m_Registry.emplace<syre::Transform>(NO2Card, glm::vec3(-3.0f, 0.0f, 2.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2f));
	m_Registry.emplace<syre::Texture>(NO2Card, "NO2.png");

	m_Registry.emplace<syre::Mesh>(SlipstreamCard, "CardNO2.obj");
	m_Registry.emplace<syre::Transform>(SlipstreamCard, glm::vec3(-3.0f, 0.0f, 2.0f),glm::vec3(0.0,0.0,0.0),glm::vec3(0.2f));
	m_Registry.emplace<syre::Texture>(SlipstreamCard, "Slipstream.png");


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
	morphShader->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
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
	glm::vec3 camX = glm::cross(camComponent->GetForward(), camComponent->GetUp());

	KeyEvents(deltaTime);
	flatShader->Bind();
	flatShader->SetUniformMatrix("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)));
	flatShader->SetUniform("offset", glm::vec2(-.4f, -.7f));
	m_Registry.get<syre::Texture>(NO2Card).Bind();
	m_Registry.get<syre::Mesh>(NO2Card).Render();
	flatShader->SetUniform("offset", glm::vec2(0.f, -.7f));
	m_Registry.get<syre::Texture>(SlipstreamCard).Bind();
	m_Registry.get<syre::Mesh>(SlipstreamCard).Render();


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
	for (auto entity : morphRenderView)
	{
		glm::mat4 transform = morphRenderView.get<syre::Transform>(entity).GetModelMat();
		morphShader->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		morphShader->SetUniformMatrix("u_Model", transform);
		morphShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		morphShader->SetUniform("t", morphRenderView.get<syre::MorphRenderer>(entity).Update(deltaTime));
		morphRenderView.get<syre::Texture>(entity).Bind();
		morphRenderView.get<syre::MorphRenderer>(entity).Render();
	}
}

void SceningTest::ImGUIUpdate()
{
		// Implementation new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		// ImGui context new frame
		ImGui::NewFrame();

		if (ImGui::Begin("Debug")) {
			// Render our GUI stuff
			auto movable = m_Registry.view<syre::Mesh, syre::Transform>();
			for (auto entity : movable)
			{
				auto& transform = m_Registry.get<syre::Transform>(entity);
				ImGui::SliderFloat("Entity x", &transform.position.x, -2.0f, 2.0f);
				ImGui::SliderFloat("Entity y", &transform.position.y, -2.0f, 2.0f);
				ImGui::SliderFloat("Entity z", &transform.position.z, -2.0f, 2.0f);
				ImGui::SliderFloat("Entity rotx", &transform.rotationEuler.x, 0.f, 360.0f);
				ImGui::SliderFloat("Entity roty", &transform.rotationEuler.y, 0.0f, 360.0f);
				ImGui::SliderFloat("Entity rotz", &transform.rotationEuler.z, 0.0f, 360.0f);
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
		curCamPos.x += 0.01f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		curCamPos.x -= 0.01f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		curCamPos.y -= 0.01f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		curCamPos.y += 0.01f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		curCamFor.x += 0.01f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		curCamFor.x -= 0.01f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		curCamFor.y -= 0.01f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		curCamFor.y += 0.01f * delta;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		PlayerComponent.PlayCard(0);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double* x = new double;
		double* y = new double;

		glfwGetCursorPos(window, x,y);
		printf("Mouse at X %f Y %f\n", *x, *y);
	}
	camComponent->SetPosition(curCamPos);
	camComponent->SetForward(glm::normalize(curCamFor));
}

