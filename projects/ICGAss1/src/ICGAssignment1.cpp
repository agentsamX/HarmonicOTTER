#include "ICGAssignment1.h"

ICGAssignment1::ICGAssignment1(GLFWwindow* inWind)
{
    window = inWind;
}

void ICGAssignment1::Start()
{
    camera = Camera::Create();
    camera->SetPosition(glm::vec3(0, -15.0f, 6.0f)); // Set initial position
    camera->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
    camera->LookAt(glm::vec3(0.0f)); // Look at center of the screen
    camera->SetFovDegrees(100.0f); // Set an initial FOV

    assignmentShader = Shader::Create();
	assignmentShader->LoadShaderPartFromFile("fragShader.glsl",GL_FRAGMENT_SHADER);
	assignmentShader->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	assignmentShader->Link();

	assignmentShader->Bind();

	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	float lightSpecularPow = 1.0f;
	float lightDiffusePow = 1.0f;
	float lightAmbientPow = 0.5f;

	glm::vec3 ambientCol = glm::vec3(1.0f);
	float shininess = 4.0f;
	// These are our application / scene level uniforms that don't necessarily update
	// every frame
	assignmentShader->SetUniform("u_LightPos", lightPos);
	assignmentShader->SetUniform("u_LightCol", lightCol);
	assignmentShader->SetUniform("u_AmbientCol", ambientCol);
	assignmentShader->SetUniform("u_SpecularStrength", lightSpecularPow);
	assignmentShader->SetUniform("u_AmbientStrength", lightAmbientPow);
	assignmentShader->SetUniform("u_DiffuseStrength", lightDiffusePow);
	assignmentShader->SetUniform("u_Shininess", shininess);

	car = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(car, "SnubNoseCar.obj");
	m_Registry.emplace<syre::Transform>(car, glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(2.0f));
	m_Registry.emplace<syre::Texture>(car, "red.png");

	glass = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(glass, "cylinder.obj");
	m_Registry.emplace<syre::Transform>(glass, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(6.0f));
	m_Registry.emplace<syre::Texture>(glass, "transparentBlue.png");

	pedestal = m_Registry.create();
	m_Registry.emplace<syre::Mesh>(pedestal, "pedestal.obj");
	m_Registry.emplace<syre::Transform>(pedestal, glm::vec3(0.0f, 0.0f, -8.0f), glm::vec3(90.0f, 0.0f, 290.0f), glm::vec3(8.0f));
	m_Registry.emplace<syre::Texture>(pedestal, "pedestal.png");


}

int ICGAssignment1::Update()
{
	assignmentShader->Bind();

	assignmentShader->SetUniform("u_SpecularStrength", specularOn?0.7f:0.0f);
	assignmentShader->SetUniform("u_AmbientStrength", ambientOn?0.3f:0.0f);
	assignmentShader->SetUniform("u_DiffuseStrength", diffuseOn?1.0f:0.0f);

	if (rainbowOn)
	{
		assignmentShader->SetUniform("time",float(glfwGetTime()));
	}
	else
	{
		assignmentShader->SetUniform("time", 0.0f);
	}


	assignmentShader->SetUniform("u_CamPos", camera->GetPosition());
	glm::mat4 transform = m_Registry.get<syre::Transform>(car).GetModelMat();
	assignmentShader->SetUniformMatrix("u_ModelViewProjection", camera->GetViewProjection() * transform);
	assignmentShader->SetUniformMatrix("u_Model", transform);
	assignmentShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
	m_Registry.get<syre::Texture>(car).Bind();
	m_Registry.get<syre::Mesh>(car).Render();
	glm::vec3 carPos = m_Registry.get<syre::Transform>(car).GetPosition();
	m_Registry.get<syre::Transform>(car).SetPosition(glm::vec3(carPos.x,carPos.y,(sin(glfwGetTime())*4)+4));


	transform = m_Registry.get<syre::Transform>(glass).GetModelMat();
	assignmentShader->SetUniformMatrix("u_ModelViewProjection", camera->GetViewProjection() * transform);
	assignmentShader->SetUniformMatrix("u_Model", transform);
	assignmentShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
	m_Registry.get<syre::Texture>(glass).Bind();
	m_Registry.get<syre::Mesh>(glass).Render();

	transform = m_Registry.get<syre::Transform>(pedestal).GetModelMat();
	assignmentShader->SetUniformMatrix("u_ModelViewProjection", camera->GetViewProjection() * transform);
	assignmentShader->SetUniformMatrix("u_Model", transform);
	assignmentShader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
	m_Registry.get<syre::Texture>(pedestal).Bind();
	m_Registry.get<syre::Mesh>(pedestal).Render();

	camera->LookAt(m_Registry.get<syre::Transform>(car).GetPosition());
    return 0;
}

void ICGAssignment1::ImGUIUpdate()
{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		// ImGui context new frame
		ImGui::NewFrame();

		if (ImGui::Begin("Debug")) {
			// Render our GUI stuff


			auto& camComponent = camera;
			glm::vec3 camPos = camComponent->GetPosition();
			
			
			ImGui::SliderFloat3("Camera Position", &camPos.x,-20.f, 20.f);

			ImGui::Checkbox("Ambient Lighting", &ambientOn);
			ImGui::Checkbox("Diffuse Lighting", &diffuseOn);
			ImGui::Checkbox("Specular Lighting", &specularOn);
			ImGui::Checkbox("Rainbow Mode", &rainbowOn);
			if (ImGui::Button("1"))
			{
				ambientOn = false;
				diffuseOn = false;
				specularOn = false;
				rainbowOn = false;
			}
			if (ImGui::Button("2"))
			{
				ambientOn = true;
				diffuseOn = false;
				specularOn = false;
				rainbowOn = false;
			}
			if (ImGui::Button("3"))
			{
				ambientOn = false;
				diffuseOn = false;
				specularOn = true;
				rainbowOn = false;
			}
			if (ImGui::Button("4"))
			{
				ambientOn = true;
				diffuseOn = true;
				specularOn = true;
				rainbowOn = false;
			}
			if (ImGui::Button("5"))
			{
				ambientOn = true;
				diffuseOn = true;
				specularOn = true;
				rainbowOn = true;
			}
			

			camComponent->SetPosition(camPos);
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

Camera::sptr& ICGAssignment1::GetCam()
{
    return camera;
}
