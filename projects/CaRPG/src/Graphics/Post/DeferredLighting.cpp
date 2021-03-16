#include "DeferredLighting.h"

void DeferredLighting::Init(unsigned width, unsigned height)
{
    int index = int(_buffers.size());
    _buffers.push_back(new Framebuffer());
    _buffers[index]->AddColorTarget(GL_RGBA8);
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
    _shaders[index]->LoadShaderPartFromFile("shaders/deferredFrag.glsl", GL_FRAGMENT_SHADER);
    _shaders[index]->Link();

    glm::vec3 lightPos = glm::vec3(-3.0f, 0.0f, -2.0f);
    glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 ambientCol = glm::vec3(1.0f);

    _shaders[1]->SetUniform("u_LightPos", lightPos);
    _shaders[1]->SetUniform("u_LightCol", lightCol);
    _shaders[1]->SetUniform("u_AmbientCol", ambientCol);
}

void DeferredLighting::ApplyEffect(PostEffect* buffer)
{
    BindShader(1);
    _shaders[1]->SetUniform("u_CamPos", cameraPosition);
    _shaders[1]->SetUniform("u_SpecularStrength", specularOn ? 1.0f : 0.0f);
    _shaders[1]->SetUniform("u_AmbientStrength", ambientOn ? 0.6f : 0.0f);
    _shaders[1]->SetUniform("u_DiffuseStrength", diffuseOn ? 1.0f : 0.0f);
    _shaders[1]->SetUniform("u_TextureOn", textureOn ? 1 : 0);
    _shaders[1]->SetUniform("u_toonBands", toonOn ? toonBands : 0);

    buffer->BindColorAsTexture(0, 0, 0);
    buffer->BindColorAsTexture(0, 1, 1);
    buffer->BindColorAsTexture(0, 2, 2);

    _buffers[0]->RenderToFSQ();

    buffer->UnbindTexture(0);
    buffer->UnbindTexture(1);
    buffer->UnbindTexture(2);

    UnbindShader();

}

void DeferredLighting::DrawToScreen()
{
    BindShader(0);

    BindColorAsTexture(0, 0, 0);

    _buffers[0]->DrawFullscreenQuad();

    UnbindTexture(0);

    UnbindShader();
}

void DeferredLighting::UpdateUniforms(glm::vec3 camPos, bool spec, bool ambi, bool diff, bool tex, bool toon, int bands)
{
    cameraPosition = camPos;
    specularOn = spec;
    ambientOn = ambi;
    diffuseOn = diff;
    textureOn = tex;
    toonOn = toon;
    toonBands = bands;
}
