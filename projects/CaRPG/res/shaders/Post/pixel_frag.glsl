#version 420

layout(location = 0) in vec2 inUV;

out vec4 frag_color;

layout (binding = 0) uniform sampler2D s_screenTex;


uniform float u_Width;
uniform float u_Height;
uniform int u_Factor;

void main() 
{
	float xPixels = u_Width/float(u_Factor);
	float yPixels = u_Height/float(u_Factor);
    float newUVx = round(inUV.x*xPixels)/xPixels;
	float newUVy = round(inUV.y*yPixels)/yPixels;

	//vec4 source = texture(s_screenTex, newUV);

	frag_color =  texture(s_screenTex, vec2(newUVx,newUVy));
}