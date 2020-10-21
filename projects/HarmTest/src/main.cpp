#include "Mesh.h"
#include "Scene.h"
int main()
{
	syre::Scene* curScene = new syre::Scene;
	std::string fileName;
	entt::entity test = curScene->m_Registry.create();
	curScene->m_Registry.emplace<syre::Mesh>(test, fileName);

	syre::Mesh testMesh("C:\\tmp\\justACube.obj");
	return 0;
} 
