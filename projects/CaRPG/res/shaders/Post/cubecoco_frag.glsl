#version 420

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout (binding = 0) uniform sampler2D s_screenTex;

layout (binding = 30) uniform sampler3D s_cocoTex;

uniform float u_Intensity = 1.0;

void main() 
{
	vec4 source = texture(s_screenTex, inUV);

	vec3 scale = vec3((64.0-1.0)/64.0);
	vec3 offset = vec3(1.0/(2.0*64.0));

	vec4 corrected = texture(s_cocoTex,scale * source.xyz + offset);

	frag_color.rgb = mix(source.rgb,corrected.rgb,u_Intensity);
    frag_color.a = source.a;
}