#include "TransformList.h"

syre::TransformList::TransformList()
{
}

void syre::TransformList::SetDefaultRot(glm::vec3 rot)
{
	useDefaultRot = true;
	defaultRot = rot;
}

void syre::TransformList::SetDefaultSca(glm::vec3 sca)
{
	useDefaultSca = true;
	defaultScale = sca;
}

void syre::TransformList::SetRelativePos(glm::vec3 pos)
{
	useRelative = true;
	lastRelative = relativePos;
	relativePos = pos;
}

void syre::TransformList::UpdateCurPos(glm::vec3 pos)
{
	lastCurPos = curPos;
	curPos = pos;
}

void syre::TransformList::SetCamera(Camera::sptr cam)
{
	camera = cam;
}

void syre::TransformList::ListRender(Shader::sptr shader, syre::Mesh mesh)
{
	for (int i = 0; i < listTransform.size(); i++)
	{
		glm::mat4 transform;
		if (useRelative)
		{
			transform = syre::Transform(glm::vec3(relativePos + listTransform[i].GetPosition()), listTransform[i].GetRotation(), listTransform[i].GetScale()).GetModelMat();
		}
		else
		{
			transform = listTransform[i].GetModelMat();
		}
		shader->SetUniformMatrix("u_ModelViewProjection", camera->GetViewProjection() * transform);
		shader->SetUniformMatrix("u_Model", transform);
		shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		mesh.Render();
	}
}

void syre::TransformList::ListRender(Shader::sptr shader, syre::Mesh mesh, float deltaTime)
{
	if (particalized)
	{
		ParticleUpdate(deltaTime);
	}
	for (int i = 0; i < listTransform.size(); i++)
	{
		glm::mat4 transform;
		if (useRelative)
		{
			transform = syre::Transform(glm::vec3(relativePos + listTransform[i].GetPosition()), listTransform[i].GetRotation(), listTransform[i].GetScale()).GetModelMat();
		}
		else
		{
			transform = listTransform[i].GetModelMat();
		}
		shader->SetUniformMatrix("u_ModelViewProjection", camera->GetViewProjection() * transform);
		shader->SetUniformMatrix("u_Model", transform);
		shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		mesh.Render();
	}
}

void syre::TransformList::ListRender(Shader::sptr shader, syre::MorphRenderer morph)
{
	for (int i = 0; i < listTransform.size(); i++)
	{
		glm::mat4 transform;
		if (useRelative)
		{
			transform = syre::Transform(glm::vec3(relativePos + listTransform[i].GetPosition()),listTransform[i].GetRotation(),listTransform[i].GetScale()).GetModelMat();
		}
		else
		{
			transform = listTransform[i].GetModelMat();
		}
		shader->SetUniformMatrix("u_ModelViewProjection", camera->GetViewProjection() * transform);
		shader->SetUniformMatrix("u_Model", transform);
		shader->SetUniformMatrix("u_ModelRotation", glm::mat3(transform));
		morph.Render();
	}
}

void syre::TransformList::AddPos(glm::vec3 pos)
{
	listTransform.push_back(syre::Transform(pos, defaultRot, defaultScale));
}

void syre::TransformList::AddTrans(glm::vec3 pos, glm::vec3 rot)
{
}

void syre::TransformList::ParticleUpdate(float deltaTime)
{
	if (curPos != lastCurPos)
	{
		for (int i = 0; i < lifeTimes.size(); i++)
		{
			lifeTimes[i] += deltaTime;
			if(lifeTimes[i]>=timeDegrade)
			{
				lifeTimes.erase(lifeTimes.begin()+i-1);
				listTransform.erase(listTransform.begin() + i - 1);
			}
		}
		emitTimer += deltaTime;
		if (timeEmit <= emitTimer)
		{
			listTransform.push_back(syre::Transform(curPos,defaultRot,defaultScale));
			lifeTimes.push_back(0.0f);
			emitTimer = 0.0f;

		}
	}

}

void syre::TransformList::Particalize(float timeE,float timeD)
{
	timeEmit = timeE;
	timeDegrade = timeD;
	particalized = true;
}
