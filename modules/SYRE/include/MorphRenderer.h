#pragma once
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "IndexBuffer.h"

#include <vector>
#include <string>
#include "GLM/glm.hpp"

namespace syre
{
	struct Frame
	{
		VertexBuffer::sptr VBO;
	};
	class MorphRenderer
	{
	public:
		MorphRenderer();
		void AddFrame(std::string fileName);
		void Render();
		float Update(float delta);
		void ManualFrameSet(int frame);
		float GetT();

	private:
		glm::vec3 Vector3Parser(std::string line, int offset);
		glm::vec2 Vector2Parser(std::string line, int offset);
		void FaceLineProcessor(std::string line, std::vector<unsigned int>& indexVec);
		void ltrim(std::string& s);
		void rtrim(std::string& s);
		void trim(std::string& s);
		IndexBuffer::sptr ibo;
		VertexArrayObject::sptr vao;
		std::vector<Frame> Keys;
		bool usingManual=false;
		bool doesLoop = true;
		bool playing = true;
		float frameTime=0.5f;
		float timer = 0.0f;
		int curFrame = 0;
	};
}


