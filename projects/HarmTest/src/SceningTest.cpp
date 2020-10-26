#include "SceningTest.h"


void SceningTest::Start()
{
	std::string fileName = "monkey.obj";
	entt::entity camera = m_Registry.create();
	entt::entity testModel = m_Registry.create();
	entt::entity shader = m_Registry.create();

	m_Shader = shader;
	m_Camera = camera;
	
	m_Registry.emplace<syre::Mesh>(testModel, fileName);
	m_Registry.emplace<Camera::sptr>(camera);
	m_Registry.emplace<Shader::sptr>(shader);

	auto& shaderComponent = m_Registry.get<Shader::sptr>(shader);
	shaderComponent = Shader::Create();
	shaderComponent->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	shaderComponent->LoadShaderPartFromFile("frag_blinn_phong.glsl", GL_FRAGMENT_SHADER);
	shaderComponent->Link();

	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	float     lightAmbientPow = 0.1f;
	float     lightSpecularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     ambientPow = 0.1f;
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

	auto& camComponent = m_Registry.get<Camera::sptr>(camera);
	camComponent = Camera::Create();
	camComponent->SetPosition(glm::vec3(0, 3, 3)); // Set initial position
	camComponent->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camComponent->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camComponent->SetFovDegrees(100.0f); // Set an initial FOV
}

void SceningTest::Update()
{
	auto& camComponent = m_Registry.get<Camera::sptr>(m_Camera);
	auto& shaderComponent = m_Registry.get<Shader::sptr>(m_Shader);

	shaderComponent->Bind();
	shaderComponent->SetUniform("u_CamPos", camComponent->GetPosition());

	auto renderView = m_Registry.view<syre::Mesh>();
	for (auto entity : renderView)
	{
		glm::mat4 transform = glm::mat4(1.0f);
		shaderComponent->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		shaderComponent->SetUniformMatrix("u_Model", transform);
		shaderComponent->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		renderView.get<syre::Mesh>(entity).Render();
	}
}
