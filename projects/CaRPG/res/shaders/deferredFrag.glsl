#version 420

layout(location = 0) in vec2 inUV;

layout (binding = 0) uniform sampler2D s_Color;
layout (binding = 2) uniform sampler2D s_Normal;
layout (binding = 3) uniform sampler2D s_Pos;


uniform layout(binding =20) sampler2D rampTex;

uniform vec3  u_AmbientCol;
uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform float u_DiffuseStrength;

uniform int u_TextureOn = 1;

uniform int u_RampingSpec;
uniform int u_RampingDiff;

uniform int u_toonBands = 0;


uniform vec3  u_LightPos;
uniform vec3  u_LightCol;

uniform vec3  u_CamPos;


layout (location = 0) out vec4 frag_color;
layout (location = 1) out vec4 light_result;


void main() {
		
	vec3 textureColor = (u_TextureOn==1)?texture(s_Color,inUV).xyz:vec3(0.7f);


	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	float ambientStrength = u_AmbientStrength;
	vec3 ambient = ambientStrength * lightColor * textureColor;//texture(s_Color,inUV);
	
	// Diffuse
	vec3 N = (normalize(texture(s_Normal,inUV).rgb)*2.0)-1.0;
	vec3 lightDir = normalize(u_LightPos - texture(s_Pos,inUV).xyz);
	
	float dif =u_RampingDiff==1?texture(rampTex,vec2(max(dot(N, lightDir), 0.0),0.5)).r: max(dot(N, lightDir), 0.0);
	float diffuseStrength=u_DiffuseStrength;
	vec3 diffuse = dif * textureColor*diffuseStrength;//texture(s_Color,inUV);// add diffuse intensity

	//Attenuation
	float dist = length(u_LightPos - texture(s_Pos,inUV).xyz);
	diffuse = diffuse / dist; // (dist*dist)
	
	// Specular
	vec3 camPos = u_CamPos;//Pass this as a uniform from your C++ code
	float specularStrength = u_SpecularStrength; // this can be a uniform
	vec3 camDir = normalize(u_CamPos - texture(s_Pos,inUV).xyz);
	vec3 reflectDir = reflect(-lightDir, N);
	float spec = u_RampingSpec==1?texture(rampTex,vec2(pow(max(dot(camDir, reflectDir), 0.0), 4),0.5)).r:pow(max(dot(camDir, reflectDir), 0.0), 4); // Shininess coefficient (can be a uniform)
	vec3 specular = specularStrength * spec* lightColor; // Can also use a specular color
	
	vec3 result = (u_toonBands==0)? (ambient + diffuse + specular):round((ambient+diffuse+specular)*u_toonBands)/u_toonBands;
	
	light_result = vec4(specular+(dif*diffuseStrength)+(ambientStrength*lightColor),1.0);
	frag_color = vec4(textureColor,1.0)*vec4(result,1.0);
}