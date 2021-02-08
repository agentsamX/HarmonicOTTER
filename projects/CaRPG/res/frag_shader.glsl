#version 420

layout(location = 0) in vec3 inPos;
layout(location = 3) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
//LECTURE 7
layout(location = 1) in vec2 UV;

uniform sampler2D textureSampler;

uniform layout(binding =20) sampler2D rampTex;

uniform vec3  u_AmbientCol;
uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform float u_DiffuseStrength;

uniform int u_CarEmissive;

uniform int u_RampingSpec;
uniform int u_RampingDiff;


uniform vec3  u_LightPos;
uniform vec3  u_LightCol;

uniform vec3  u_CamPos;

uniform vec3 playerPos;
uniform vec3 enemyPos;


out vec4 frag_color;


void main() {
	float distPlay= max(2.0,distance(playerPos,inPos));
	float distEnemy =max(2.0,distance(enemyPos,inPos));

	if(distPlay>200.f)
		discard;

	
	vec3 textureColor = texture(textureSampler, UV).xyz;


	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	float ambientStrength = u_AmbientStrength;
	vec3 ambient = ambientStrength * lightColor * textureColor;//inColor;
	
	// Diffuse
	vec3 N = normalize(inNormal);
	vec3 lightDir = normalize(u_LightPos - inPos);
	
	float dif =u_RampingDiff==1?texture(rampTex,vec2(max(dot(N, lightDir), 0.0),0.5)).r: max(dot(N, lightDir), 0.0);
	float diffuseStrength=u_DiffuseStrength;
	vec3 diffuse = dif * textureColor*diffuseStrength;//inColor;// add diffuse intensity

	//Attenuation
	float dist = length(u_LightPos - inPos);
	diffuse = diffuse / dist; // (dist*dist)
	
	// Specular
	vec3 camPos = u_CamPos;//Pass this as a uniform from your C++ code
	float specularStrength = u_SpecularStrength; // this can be a uniform
	vec3 camDir = normalize(u_CamPos - inPos);
	vec3 reflectDir = reflect(-lightDir, N);
	float spec = u_RampingSpec==1?texture(rampTex,vec2(pow(max(dot(camDir, reflectDir), 0.0), 4),0.5)).r:pow(max(dot(camDir, reflectDir), 0.0), 4); // Shininess coefficient (can be a uniform)
	vec3 specular = specularStrength * spec* lightColor; // Can also use a specular color
	
	vec3 result = (ambient + diffuse + specular);
	
	frag_color = u_CarEmissive==1?(texture(textureSampler, UV)/(distPlay/10) *vec4(result,1.0)+vec4(1/distPlay,0.0f,1/distEnemy,0.0f)):(texture(textureSampler, UV)*vec4(result,1.0));
}