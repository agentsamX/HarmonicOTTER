#version 410

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inUV;

layout(location = 0) out vec2 outUV;

uniform float u_height;

out float heightAdds[4];

void main()
{ 
	float screenwidth=u_height;
	float onePixel;
	onePixel= 1.0/screenwidth;
	for(int i =-4; i<0;i++)
	{
		heightAdds[i+4]=onePixel*i;
	}
	outUV = inUV;
	gl_Position = vec4(inPosition, 1.0);
}