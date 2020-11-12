#version 410

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 UV;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inColor;


uniform sampler2D textureSampler;


out vec4 frag_color;


void main() {
	
	vec3 textureColor = texture(textureSampler, UV).xyz;
	frag_color = texture(textureSampler, UV);
}