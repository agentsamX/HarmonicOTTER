#version 410

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUV;

layout(location = 0) out vec2 outUV;

uniform float u_width;
uniform float u_height;

out float widthAdds[3];
out float heightAdds[3];

out float onePixelH;
out float onePixelW;


void main()
{ 
	float screenwidth=u_width;
	float screenheight=u_height;
	onePixelW = 1.0/screenwidth;
	onePixelH = 1.0/screenheight;
	for(int i =-3; i<0;i++)
	{
		widthAdds[i+3]=onePixelW*i;
		heightAdds[i+3]=onePixelH*i;
	}
	outUV = inUV;
	gl_Position = vec4(inPosition, 1.0);
}