/*
Created by Samuel Canonaco
October 13 2020
*/
#include <vector>
#include<string>
#include "GLM/glm.hpp"
#include "VertexArrayObject.h"

namespace syre
{
	class Mesh
	{
	public:
	
		VertexBuffer::sptr vbo=VertexBuffer::Create();
		IndexBuffer::sptr ibo=IndexBuffer::Create();
		VertexArrayObject::sptr vao=VertexArrayObject::Create();
		Mesh(std::string fileName);
		glm::vec3 Vector3Parser(std::string line, int offset);
		glm::vec2 Vector2Parser(std::string line, int offset);
		void FaceLineProcessor(std::string line,std::vector<unsigned int> indexVec);
		void Render();
	};
}