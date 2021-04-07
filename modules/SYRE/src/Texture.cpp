#include "Texture.h"

syre::Texture::Texture(std::string file){

	unsigned char* image;

	stbi_set_flip_vertically_on_load(true);

	image = stbi_load(file.c_str(), &width, &height, &channels, 0);

	/*if (image)
		printf("Image loaded: %i x %i\n",width,height);
	else printf("Failed to load image\n");*/

	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, (channels==4)?GL_RGBA:GL_RGB, width, height, 0, (channels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);

	//texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void syre::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureHandle);

}
