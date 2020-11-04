#include "MidtermScene.h" 


MidtermScene::MidtermScene(GLFWwindow* inWind)
{
	window = inWind;
}

void MidtermScene::Start()
{
	std::string filename = "box.bmp";
	entt::entity camera = m_Registry.create();
	entt::entity shader = m_Registry.create();

	puck = m_Registry.create();
	paddleL = m_Registry.create();
	paddleR = m_Registry.create();
	counterL = m_Registry.create();
	counterR = m_Registry.create();
	win = m_Registry.create();
	entt::entity table = m_Registry.create();
	entt::entity plane = m_Registry.create();
	


	m_Shader = shader;
	m_Camera = camera;
	//syre::Mesh* puckMesh = new syre::Mesh(filename);

	m_Registry.emplace<syre::Mesh>(puck, "midterm_puck.obj");
	m_Registry.emplace<syre::Transform>(puck, glm::vec3(0.0f, -2.f, -6.0f),glm::vec3(90.0f,0.0f,0.0f),glm::vec3(1.0f));
	m_Registry.emplace<Puck>(puck,puckBaseSpeed,0.f);
	m_Registry.emplace<syre::Texture>(puck, "green.png");

	m_Registry.emplace<syre::Mesh>(paddleL, "midterm_paddle.obj");
	m_Registry.emplace<syre::Transform>(paddleL, glm::vec3(leftBound, -2.f, -6.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(paddleL, "blue.png");


	m_Registry.emplace<syre::Mesh>(paddleR, "midterm_paddle.obj");
	m_Registry.emplace<syre::Transform>(paddleR, glm::vec3(rightBound, -2.f, -6.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(paddleR, "red.png");

	m_Registry.emplace<syre::Mesh>(table, "midterm_table.obj");
	m_Registry.emplace<syre::Transform>(table,glm::vec3(0.0f, -2.0f, -6.0f), glm::vec3(90.0f, 0.0f, 90.0f), glm::vec3(1.0f));
	m_Registry.emplace<syre::Texture>(table, "tabletex.png");

	m_Registry.emplace<syre::Mesh>(counterL, "midterm_scorecounter.obj");
	m_Registry.emplace<syre::Transform>(counterL, glm::vec3(5.0f, -20.0f, -6.0f), glm::vec3(90.0f, 90.0f, 90.0f), glm::vec3(6.0f));
	m_Registry.emplace<syre::Texture>(counterL, "scorecounter.png");

	m_Registry.emplace<syre::Mesh>(counterR, "midterm_scorecounter.obj");
	m_Registry.emplace<syre::Transform>(counterR, glm::vec3(-5.0f, -20.0f, -6.0f), glm::vec3(90.0f, 90.0f, 90.0f), glm::vec3(6.0f));
	m_Registry.emplace<syre::Texture>(counterR, "scorecounter.png");

	m_Registry.emplace<syre::Mesh>(plane, "plane.obj");
	m_Registry.emplace<syre::Transform>(plane, glm::vec3(0.0f, -14.35f, -6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f));
	m_Registry.emplace<syre::Texture>(plane, "black.png");

	m_Registry.emplace<syre::Mesh>(win, "midterm_win.obj");
	m_Registry.emplace<syre::Transform>(win, glm::vec3(8.0f, -7.0f, 0.0f), glm::vec3(160.0f, 0.0f, 180.0f), glm::vec3(4.0f));



	m_Registry.emplace<Camera::sptr>(camera);
	m_Registry.emplace<Shader::sptr>(shader);

	auto& shaderComponent = m_Registry.get<Shader::sptr>(shader);
	shaderComponent = Shader::Create();
	shaderComponent->LoadShaderPartFromFile("vertex_shader.glsl", GL_VERTEX_SHADER);
	shaderComponent->LoadShaderPartFromFile("frag_shader.glsl", GL_FRAGMENT_SHADER);
	shaderComponent->Link();
	
	glm::vec3 lightPos = glm::vec3(0.0f, -6.0f, 10.0f);
	glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
	float     ambientPow = 0.3f;
	float     specularPow = 1.0f;
	glm::vec3 ambientCol = glm::vec3(1.0f);
	float     shininess = 4.0f;
	// These are our application / scene level uniforms that don't necessarily update
	// every frame
	shaderComponent->SetUniform("u_LightPos", lightPos);
	shaderComponent->SetUniform("u_LightCol", lightCol);
	shaderComponent->SetUniform("u_SpecularStrength", specularPow);
	shaderComponent->SetUniform("u_AmbientStrength", ambientPow);
	shaderComponent->SetUniform("u_AmbientCol", ambientCol);
	shaderComponent->SetUniform("u_Shininess", shininess);

	auto& camComponent = m_Registry.get<Camera::sptr>(camera);
	camComponent = Camera::Create();
	camComponent->SetPosition(glm::vec3(0, 3, 5)); // Set initial position
	camComponent->SetUp(glm::vec3(0, 0, 1)); // Use a z-up coordinate system
	camComponent->LookAt(glm::vec3(0.0f)); // Look at center of the screen
	camComponent->SetFovDegrees(100.0f); // Set an initial FOV

	lastFrame = glfwGetTime();
}

void MidtermScene::Update()
{
	thisFrame = glfwGetTime();
	float deltaTime = thisFrame - lastFrame;
	rHitTime += deltaTime;
	lHitTime += deltaTime;

	auto& camComponent = m_Registry.get<Camera::sptr>(m_Camera);
	auto& shaderComponent = m_Registry.get<Shader::sptr>(m_Shader);

	KeyEvents(deltaTime);

	shaderComponent->Bind();
	shaderComponent->SetUniform("u_CamPos", camComponent->GetPosition());
	if (rHit)
	{
		glm::vec3 paddleRTrans = m_Registry.get<syre::Transform>(paddleR).GetPosition();
		if (rHitTime <= 0.1f)
		{
			m_Registry.get<syre::Transform>(paddleR).SetPosition(glm::vec3(glm::mix(-8.f, -7.f, rHitTime / 0.1f), paddleRTrans.y, paddleRTrans.z));
		}
		else if (rHitTime < 0.2f)
		{
			m_Registry.get<syre::Transform>(paddleR).SetPosition(glm::vec3(glm::mix(-7.f, -8.f, rHitTime / 0.2f), paddleRTrans.y, paddleRTrans.z));

		}
		else
		{
			rHit = false;
			m_Registry.get<syre::Transform>(paddleR).SetPosition(glm::vec3(rightBound, paddleRTrans.y, paddleRTrans.z));
		}
	}
	if (lHit)
	{
		glm::vec3 paddleLTrans = m_Registry.get<syre::Transform>(paddleL).GetPosition();
		if (lHitTime <= 0.1f)
		{
			m_Registry.get<syre::Transform>(paddleL).SetPosition(glm::vec3(glm::mix(8.f, 7.f, lHitTime / 0.1f), paddleLTrans.y, paddleLTrans.z));
		}
		else if (lHitTime < 0.2f)
		{
			m_Registry.get<syre::Transform>(paddleL).SetPosition(glm::vec3(glm::mix(7.f, 8.f, lHitTime / 0.2f), paddleLTrans.y, paddleLTrans.z));

		}
		else
		{
			lHit = false;
			m_Registry.get<syre::Transform>(paddleL).SetPosition(glm::vec3(leftBound, paddleLTrans.y, paddleLTrans.z));
		}

	}
	glm::vec3 curRotL = m_Registry.get<syre::Transform>(counterL).GetRotation();
	glm::vec3 curRotR = m_Registry.get<syre::Transform>(counterR).GetRotation();
	if (curRotL.y>=targRotL)
	{
		m_Registry.get<syre::Transform>(counterL).SetRotation(glm::vec3(curRotL.x, curRotL.y -deltaTime*50.0f, curRotL.z));

	}
	if (curRotR.y >= targRotR)
	{
		m_Registry.get<syre::Transform>(counterR).SetRotation(glm::vec3(curRotR.x, curRotR.y - deltaTime * 50.0f, curRotR.z));

	}

	glm::vec3 transform = m_Registry.get<syre::Transform>(puck).GetPosition();
	glm::vec2 velocity = m_Registry.get<Puck>(puck).GetVelo();
	transform.x += velocity.x * deltaTime;
	transform.y += velocity.y * deltaTime;
	bool collided = false;
	if (transform.x > leftBound|| transform.x < rightBound)
	{
		transform.x = (transform.x/abs(transform.x))*8;
		m_Registry.get<Puck>(puck).SetVelo(glm::vec2(-velocity.x,velocity.y));
		if (transform.y > -3.f && transform.y < -1.f)
		{
			if (transform.x > 0)
			{
				targRotR -= 36.0f;
				if (targRotR < -198.f)
				{
					m_Registry.emplace<syre::Texture>(win, "red.png");
					transform = (glm::vec3(0.0f, 0.0f, -60.f));
					m_Registry.get<Puck>(puck).SetVelo(glm::vec2(0.0f, 0.0f));

				}
				else
				{
					transform = (glm::vec3(6.0f, -2.f, -6.f));
					m_Registry.get<Puck>(puck).SetVelo(glm::vec2(0.0f, 0.0f));	
				}


			}
			else
			{
				targRotL -= 36.0f;
				if (targRotL < -198.f)
				{
					m_Registry.emplace<syre::Texture>(win, "blue.png");
					transform = (glm::vec3(0.0f, 0.0f, -60.f));
					m_Registry.get<Puck>(puck).SetVelo(glm::vec2(0.0f, 0.0f));
				}
				else
				{
					transform = (glm::vec3(-6.0f, -2.f, -6.f));
					m_Registry.get<Puck>(puck).SetVelo(glm::vec2(0.0f, 0.0f));
				}

			}
		}
		collided = true;
	}
	if (transform.y > lowerBound || transform.y < upperBound)
	{
		transform.y =-2.f+ (transform.y / abs(transform.y))*4.f;
		m_Registry.get<Puck>(puck).SetVelo(glm::vec2(velocity.x, -velocity.y));
		collided = true;
	}

	glm::vec2 paddleLTrans = m_Registry.get<syre::Transform>(paddleL).GetPosition();
	glm::vec2 paddleRTrans = m_Registry.get<syre::Transform>(paddleR).GetPosition();
	glm::vec2 paddleLdiff = paddleLTrans - glm::vec2(transform.x, transform.y);
	glm::vec2 paddleRdiff = paddleRTrans - glm::vec2(transform.x, transform.y);
	if (glm::length(paddleLdiff) < 2.0f)
	{
		glm::vec2 iVelo = glm::vec2(transform.x, transform.y);
		glm::vec2 reflectVec = paddleLdiff;

		m_Registry.get<Puck>(puck).SetVelo((glm::normalize(reflectVec) * -puckBaseSpeed) * (lHit ? 2.0f : 1.0f));
				
		collided = true;
	}
	else if(glm::length(paddleRdiff) < 2.0f)
	{
		glm::vec2 iVelo = glm::vec2(transform.x, transform.y);
		glm::vec2 reflectVec = paddleRdiff;
		
		m_Registry.get<Puck>(puck).SetVelo((glm::normalize(reflectVec) * -puckBaseSpeed) * (rHit ? 2.0f : 1.0f));
	
		collided = true;
	}
	
	if (!collided)
	{
		//m_Registry.get<Puck>(puck).SetVelo(glm::vec2(velocity.x *= 1.0f+(0.5f * deltaTime), velocity.y));
		m_Registry.get<Puck>(puck).SetVelo(glm::vec2(velocity.x *= 1.0f-(0.1f * deltaTime), velocity.y *= 1.0f - (0.1f * deltaTime)));


	}
	m_Registry.get<syre::Transform>(puck).SetPosition(transform);


	auto renderView = m_Registry.view<syre::Mesh, syre::Transform,syre::Texture>();
	for (auto entity : renderView)
	{
		glm::mat4 transform = renderView.get<syre::Transform>(entity).GetModelMat();
		shaderComponent->SetUniformMatrix("u_ModelViewProjection", camComponent->GetViewProjection() * transform);
		shaderComponent->SetUniformMatrix("u_Model", transform);
		shaderComponent->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		renderView.get<syre::Texture>(entity).Bind();
		renderView.get<syre::Mesh>(entity).Render();
	}
	lastFrame = thisFrame;
}

void MidtermScene::ImGUIUpdate()
{
	// Implementation new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	// ImGui context new frame
	ImGui::NewFrame();

	/*if (ImGui::Begin("Debug")) {
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
	}*/

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

void MidtermScene::KeyEvents(float delta)
{
	glm::vec3 paddleLTrans = m_Registry.get<syre::Transform>(paddleL).GetPosition();
	glm::vec3 paddleRTrans = m_Registry.get<syre::Transform>(paddleR).GetPosition();


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		paddleLTrans.y -= 5.f * delta;
		if (paddleLTrans.y <= upperBound)
		{
			paddleLTrans.y = upperBound;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		paddleLTrans.y += 5.f * delta;
		if (paddleLTrans.y >= lowerBound)
		{
			paddleLTrans.y = lowerBound;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (lHitTime >= 0.75f)
		{
			lHit = true;
			lHitTime = 0.0f;
		}
	}
	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		paddleRTrans.y -= 5.f * delta;
		if (paddleRTrans.y <= upperBound)
		{
			paddleRTrans.y = upperBound;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		paddleRTrans.y += 5.f * delta;
		if (paddleRTrans.y >= lowerBound)
		{
			paddleRTrans.y = lowerBound;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (rHitTime >= 0.75f)
		{
			rHit = true;
			rHitTime = 0.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		if (targRotL >= -198.f && targRotR >= -198.f)
		{
			m_Registry.get<syre::Transform>(puck).SetPosition(glm::vec3(0.0f, -2.0f, -6.0f));

			
			m_Registry.get<Puck>(puck).SetVelo(glm::vec3(puckBaseSpeed, 0.0f, 0.0f));
		}
	}
	
	
	m_Registry.get<syre::Transform>(paddleL).SetPosition(paddleLTrans);
	m_Registry.get<syre::Transform>(paddleR).SetPosition(paddleRTrans);

}
