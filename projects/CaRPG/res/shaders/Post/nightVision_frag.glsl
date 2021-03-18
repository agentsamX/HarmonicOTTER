#version 420

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout (binding = 0) uniform sampler2D s_screenTex;


uniform float u_Intensity = 1.0;

void main() 
{
	vec4 source = texture(s_screenTex, inUV);

	float luminance = 0.2989 * source.r + 0.587 * source.g + 0.114 * source.b;

	float dropOff= floor(luminance*1.5f);
	float greenCut = floor(1.f/(luminance*1.5f));

	frag_color.rgb =vec3(luminance*dropOff,luminance/greenCut,dropOff*luminance);
    frag_color.a = source.a;
}