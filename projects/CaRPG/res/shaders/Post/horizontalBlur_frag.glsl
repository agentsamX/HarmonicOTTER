#version 420

layout(location = 0) in vec2 inUV;

in float widthAdds[4];

out vec4 frag_color;

layout (binding = 0) uniform sampler2D s_screenTex;


void main() 
{

	//float gaussNumbers[5] = {.000229,.005977,.060598,.241732,.382928}; //signma of 1.0
	//float gaussNumbers[8] = {.000489,.002403,.009246,.02784,.065602,.120999,.174697,.197448}; //sigma of 2.0
	float gaussNumbers[5] = {.063327,.093095,.122589,.144599,.152781}; //sigma of 3.0
	//float gaussNumbers[8] = {.057099,.060931,.064373,.067333,.06973,.071493,.072573,.72936}; //sigma of 10.0



	vec4 source = texture(s_screenTex, inUV);

	float luminance = 0.2989 * source.r + 0.587 * source.g + 0.114 * source.b;

	frag_color= 
	texture(s_screenTex,vec2(inUV.x-widthAdds[0],inUV.y))*gaussNumbers[0]+texture(s_screenTex,vec2(inUV.x+widthAdds[0],inUV.y))*gaussNumbers[0]+
	texture(s_screenTex,vec2(inUV.x-widthAdds[1],inUV.y))*gaussNumbers[1]+texture(s_screenTex,vec2(inUV.x+widthAdds[1],inUV.y))*gaussNumbers[1]+
	texture(s_screenTex,vec2(inUV.x-widthAdds[2],inUV.y))*gaussNumbers[2]+texture(s_screenTex,vec2(inUV.x+widthAdds[2],inUV.y))*gaussNumbers[2]+
	texture(s_screenTex,vec2(inUV.x-widthAdds[3],inUV.y))*gaussNumbers[3]+texture(s_screenTex,vec2(inUV.x+widthAdds[3],inUV.y))*gaussNumbers[3]+
	texture(s_screenTex,vec2(inUV.x,inUV.y))*gaussNumbers[4];
	
}