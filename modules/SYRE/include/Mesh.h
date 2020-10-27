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
	};
}

//Following code was borrowed from cg tutorials, that borrowed it from from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}