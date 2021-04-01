#include "CombinedBloom.h"

void CombinedBloom::Init(unsigned width, unsigned height)
{
    int index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);

    index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);

    index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);

    index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
    _buffers[index]->AddDepthTarget();
    _buffers[index]->Init(width, height);

    //load shader
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/brightPass_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/horizontalBlur_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/horizontalBlur_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/verticalBlur_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/verticalBlur_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/passthrough_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/compositeBloom_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/horizontalBlur_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/horizontalBlurBox_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/verticalBlur_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/verticalBlurBox_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();

    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/horizontalBlur_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/horizontalBlurBox_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/verticalBlur_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/verticalBlurBox_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();
    index = int(_shaders.size());
    _shaders.push_back(Shader::Create());
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/radialBlur_vert.glsl", GL_VERTEX_SHADER);
    _shaders[index]->LoadShaderPartFromFile("shaders/Post/radialBlur_frag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();

}

void CombinedBloom::ApplyEffect(PostEffect* buffer)
{
    
    
    BindShader(1);
    _shaders[1]->SetUniform("u_Intensity", _threshold);
    buffer->BindColorAsTexture(0, 0, 0);
    _buffers[0]->RenderToFSQ();
    buffer->UnbindTexture(0);
    UnbindShader();

    _shaders[widShader]->SetUniform("u_width", 1280.f);
    _shaders[heiShader]->SetUniform("u_height", 720.f);

    BindShader(widShader);
    _buffers[0]->BindColorAsTexture(0, 0);
    _buffers[1]->RenderToFSQ();
    _buffers[0]->UnbindTexture(0);
    UnbindShader();

    BindShader(heiShader);
    _buffers[1]->BindColorAsTexture(0, 0);
    _buffers[2]->RenderToFSQ();
    _buffers[1]->UnbindTexture(0);
    UnbindShader();


    for (int i = 0; i < _passes; i++)
    {
        _buffers[1]->Clear();

        BindShader(widShader);
        _buffers[2]->BindColorAsTexture(0, 0);
        _buffers[1]->RenderToFSQ();
        _buffers[2]->UnbindTexture(0);
        UnbindShader();

        _buffers[2]->Clear();

        BindShader(heiShader);
        _buffers[1]->BindColorAsTexture(0, 0);
        _buffers[2]->RenderToFSQ();
        _buffers[1]->UnbindTexture(0);
        UnbindShader();
    }

    BindShader(4);
    _buffers[2]->BindColorAsTexture(0, 0);
    buffer->BindColorAsTexture(0,0,1);
    _buffers[3]->RenderToFSQ();
    _buffers[2]->UnbindTexture(0);
    UnbindShader();

    _buffers[0]->Clear();
    BindShader(0);
    _buffers[3]->BindColorAsTexture(0, 0);
    _buffers[0]->RenderToFSQ();
    _buffers[3]->UnbindTexture(0);
    UnbindShader();



}

void CombinedBloom::DrawToScreen()
{
    BindShader(0);

    BindColorAsTexture(0, 0, 0);

    _buffers[0]->DrawFullscreenQuad();

    UnbindTexture(0);

    UnbindShader();
    
}


float CombinedBloom::GetThreshold() const
{
    return _threshold;
}

void CombinedBloom::SetThreshold(float threshold)
{
    _threshold = threshold;
}

int CombinedBloom::GetPasses() const
{
    return _passes;
}

void CombinedBloom::SetPasses(int passes)
{
    _passes = passes;
}

void CombinedBloom::SetBlurType(int type)
{
    if (type == GAUSS)
    {
        widShader = 2;
        heiShader = 3;
    }
    else if(type==BOX)
    {
        widShader = 5;
        heiShader = 6;
    }
    else if (type == RADIAL)
    {
        widShader = 7;
        heiShader = 7;
    }
    _blurType = BlurType(type);

}

int CombinedBloom::GetBlurType()
{
    return _blurType;
}
