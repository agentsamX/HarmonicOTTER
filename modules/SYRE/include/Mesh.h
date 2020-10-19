/*
Created by Samuel Canonaco
October 13 2020
*/
#include <vector>
#include<string>
#include "GLM/glm.hpp"

namespace syre
{
	class Mesh
	{
	public:
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> vertUVs;
		std::vector<glm::vec3> vertNormals;
		std::vector<int> indexedVertices;
		Mesh(std::string fileName);
		glm::vec3 Vector3Parser(std::string line, int offset);
		glm::vec2 Vector2Parser(std::string line, int offset);
		void FaceLineProcessor(std::string line);

	};
}