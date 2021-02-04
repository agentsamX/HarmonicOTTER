#pragma once

#include "Graphics/Framebuffer.h"
#include "Shader.h"

class PostEffect
{
public:
	//Initialize this effects (will be overriden in derived classes)
	virtual void Init(unsigned width, unsigned height);

	//applies
	virtual void ApplyEffect(PostEffect* previousBuffer);
	virtual void DrawToScreen();

	//reshapes the buffer
	virtual void Reshape(unsigned width, unsigned height);

	//clears
	void Clear();

	//unloads buffers
	void Unload();

	//binds
	void BindBuffer(int index);
	void UnBindBuffer();

	//Bind Textures
	void BindColorAsTexture(int index, int colorBuffer, int textureSlot);
	void BindDepthAsTexture(int index, int textureSlot);
	void UnbindTexture(int textureSlot);

	//shader
	void BindShader(int index);
	void UnbindShader();

protected:
	std::vector<Framebuffer*> _buffers;

	std::vector<Shader::sptr> _shaders;

};