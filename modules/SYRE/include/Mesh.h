/*
Created by Samuel Canonaco
October 13 2020
*/
#include <vector>
#include<string>
#include "GLM/glm.hpp"
#include <GLM/gtc/quaternion.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "VertexArrayObject.h"
#include <algorithm>

namespace syre
{
	class Mesh
	{
	public:
	
		VertexArrayObject::sptr vao=VertexArrayObject::Create();
		Mesh(std::string fileName);
		glm::vec3 Vector3Parser(std::string line, int offset);
		glm::vec2 Vector2Parser(std::string line, int offset);
		void FaceLineProcessor(std::string line,std::vector<unsigned int>& indexVec);
		void Render();
	private:
		void ltrim(std::string& s);
		void rtrim(std::string& s);
		void trim(std::string& s);
	};
}

