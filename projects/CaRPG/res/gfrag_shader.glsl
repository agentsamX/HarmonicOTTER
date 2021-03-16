#version 420

//Data for this model
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inColor;

//albedo textures
uniform sampler2D textureSampler;

//multi render targets
layout(location = 0) out vec4 outColors;
layout(location = 1) out vec3 outNormals;
layout(location = 2) out vec3 outSpecs;
layout(location = 3) out vec3 outPositions;

void main()
{
    vec4 textureColor = texture(textureSampler,inUV);

    outColors=textureColor;

    //normals are in -1,1
    //we want them out 0,1
    outNormals=(normalize(inNormal)*0.5)+0.5;

    //outputs spec
    outSpecs=vec3(1,0,0);

    outPositions=inPos;

}