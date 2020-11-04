#pragma once
#include <string>
#define STB_IMAGE_IMPLENTATION
#include <stb_image.h>
#include"GLFW/glfw3.h"
namespace syre {
	class Texture {
	public:
		Texture(std::string);
		void Bind();
	private:
		
		int width, height;
		int channels;
		GLuint textureHandle;

	};
}