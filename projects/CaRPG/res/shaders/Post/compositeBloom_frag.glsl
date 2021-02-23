#version 420

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout (binding = 0) uniform sampler2D s_bloomedTex;
layout (binding = 1) uniform sampler2D s_basicTex;

uniform float u_Intensity;



void main() 
{
	vec4 colorA = texture(s_basicTex,inUV);
	vec4 colorB = texture(s_bloomedTex,inUV);

	//frag_color = mix(texture(s_bloomedTex,inUV),texture(s_basicTex,inUV),u_Intensity);
	//frag_color = texture(s_basicTex,inUV)+texture(s_bloomedTex,inUV)*u_Intensity;
	frag_color= 1.0 - (1.0-colorA) * (1.0 - colorB);
}