#include "IlluminationBuffer.h"

void IlluminationBuffer::Init(unsigned width, unsigned height)
{
	//composite buffer
	int index = int(_buffers.size());
	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->AddDepthTarget();
	_buffers[index]->Init(width, height);

	//ilum buffer

	index = int(_buffers.size());
	_buffers.push_back(new Framebuffer());
	_buffers[index]->AddColorTarget(GL_RGBA8);
	_buffers[index]->AddDepthTarget();
	_buffers[index]->Init(width, height);
	
	//loads directional g buffer shader
	index = int(_shaders.size());
	_shaders.push_back(Shader::Create());
	_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index]->LoadShaderPartFromFile("shaders/gBuffer_directional_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();

	//loads ambient gBuffer shader
	index = int(_shaders.size());
	_shaders.push_back(Shader::Create());
	_shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
	_shaders[index]->LoadShaderPartFromFile("shaders/gBuffer_ambient_frag.glsl", GL_FRAGMENT_SHADER);
	_shaders[index]->Link();

	//allocate sun buffer
	_sunBuffer.AllocateMemory(sizeof(DirectionalLight));

	if (_sunEnabled)
	{
		_sunBuffer.SendData(reinterpret_cast<void*>(&_sun), sizeof(DirectionalLight));
	}
	PostEffect::Init(width, height);
}

void IlluminationBuffer::ApplyEffect(GBuffer* gBuffer)
{
	_sunBuffer.SendData(reinterpret_cast<void*>(&_sun), sizeof(DirectionalLight));
	if (_sunEnabled)
	{
		//binds directional light shader
		_shaders[Lights::DIRECTIONAL]->Bind();
		_shaders[Lights::DIRECTIONAL]->SetUniformMatrix("u_LightSpaceMatrix", _lightSpaceViewProj);
		_shaders[Lights::DIRECTIONAL]->SetUniform("u_CamPos", _camPos);

		_sunBuffer.Bind(0);

		gBuffer->BindLighting();

		_buffers[1]->RenderToFSQ();

		gBuffer->UnbindLighting();

		_sunBuffer.Unbind(0);

		_shaders[Lights::DIRECTIONAL]->UnBind();
	}

	//bind ambient
	_shaders[Lights::AMBIENT]->Bind();
	_shaders[Lights::AMBIENT]->SetUniform("u_PlayerPos", _playPos);
	_shaders[Lights::AMBIENT]->SetUniform("u_EnemyPos", _enemPos);

	_sunBuffer.Bind(0);

	gBuffer->BindLighting();
	_buffers[1]->BindColorAsTexture(0, 4);
	_buffers[0]->BindColorAsTexture(0, 5);

	_buffers[0]->RenderToFSQ();

	_buffers[0]->UnbindTexture(5);
	_buffers[1]->UnbindTexture(4);
	gBuffer->UnbindLighting();

	//unbind unifrom buffers
	_sunBuffer.Unbind(0);

	_shaders[Lights::AMBIENT]->UnBind();
}

void IlluminationBuffer::DrawIllumBuffer()
{
	_shaders[_shaders.size() - 1]->Bind();

	_buffers[1]->BindColorAsTexture(0, 0);

	Framebuffer::DrawFullscreenQuad();

	_buffers[1]->UnbindTexture(0);

	_shaders[_shaders.size() - 1]->UnBind();
}

void IlluminationBuffer::SetLightSpaceViewProj(glm::mat4 lightSpaceViewProj)
{
	_lightSpaceViewProj = lightSpaceViewProj;
}

void IlluminationBuffer::SetCamPos(glm::vec3 camPos)
{
	_camPos = camPos;
}

void IlluminationBuffer::SetPlayerPos(glm::vec3 playPos)
{
	_playPos = playPos;
}

void IlluminationBuffer::SetEnemyPos(glm::vec3 enemPos)
{
	_enemPos = enemPos;
}

DirectionalLight& IlluminationBuffer::GetSunRef()
{
	return _sun;
}

void IlluminationBuffer::SetSun(DirectionalLight newSun)
{
	_sun = newSun;
}

void IlluminationBuffer::SetSun(glm::vec4 lightDir, glm::vec4 lightCol)
{
	_sun._lightDirection = lightDir;
	_sun._lightCol = lightCol;
}

void IlluminationBuffer::EnableSun(bool enabled)
{
	_sunEnabled = enabled;
}
