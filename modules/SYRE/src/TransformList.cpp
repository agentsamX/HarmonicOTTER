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
	relativePos = pos;
}

void syre::TransformList::SetCamera(Camera::sptr cam)
{
	camera = cam;
}

void syre::TransformList::ListRender(Shader::sptr shader, syre::Mesh mesh)
{
	for (int i = 0; i < listTransform.size(); i++)
	{
		glm::mat4 transform = listTransform[i].GetModelMat();
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
		glm::mat4 transform = listTransform[i].GetModelMat();
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
