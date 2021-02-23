#version 420

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout (binding = 0) uniform sampler2D s_screenTex;


uniform float u_Intensity=0.5;

void main() 
{
	vec4 source = texture(s_screenTex, inUV);

	float luminance = 0.2989 * source.r + 0.587 * source.g + 0.114 * source.b;

	if(luminance<u_Intensity)
	{
		discard;
	}
	frag_color=source;
}