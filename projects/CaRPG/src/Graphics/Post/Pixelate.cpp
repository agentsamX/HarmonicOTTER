#include "Pixelate.h"
void Pixelate::Init(unsigned width, unsigned height)
{
    int index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);

    _width = width;
    _height = height;

    //load shader
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/pixel_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
}

void Pixelate::ApplyEffect(PostEffect* buffer)
{
    BindShader(0);
    _shaders[0]->SetUniform("u_Width", _width);
    _shaders[0]->SetUniform("u_Height", _height);
    _shaders[0]->SetUniform("u_Factor", pixelFactor);



    buffer->BindColorAsTexture(0, 0, 0);

    _buffers[0]->RenderToFSQ();

    buffer->UnbindTexture(0);

    UnbindShader();
}

int Pixelate::GetFactor() const
{
	return pixelFactor;
}

void Pixelate::SetFactor(int factor)
{
    pixelFactor = factor;
}
