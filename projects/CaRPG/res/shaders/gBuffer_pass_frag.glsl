#version 420

//Data for this model
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUV;

//albedo textures
uniform sampler2D s_Diffuse;
uniform sampler2D s_Diffuse2;
uniform sampler2D s_Specular;
uniform float u_TextureMix;

//multi render targets
layout(location = 0) out vec4 outColors;
layout(location = 1) out vec3 outNormals;
layout(location = 2) out vec3 outSpecs;
layout(location = 3) out vec3 outPositions;

void main()
{
    vec4 textureColor1 = texture(s_Diffuse,inUV);
    vec4 textureColor2 = texture(s_Diffuse2,inUV);
    vec4 textureColor = mix(textureColor1,textureColor2,u_TextureMix);

    outColors=textureColor;

    //normals are in -1,1
    //we want them out 0,1
    outNormals=(normalize(inNormal)*0.5)+0.5;

    //outputs spec
    outSpecs=texture(s_Specular,inUV).rgb;

    outPositions=inPos;

}