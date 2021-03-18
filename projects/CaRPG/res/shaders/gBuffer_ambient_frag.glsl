#version 420

layout(location = 0) in vec2 inUV;

struct DirectionalLight
{
	//Light direction (defaults to down, to the left, and a little forward)
	vec4 _lightDirection;

	//Generic Light controls
	vec4 _lightCol;

	//Ambience controls
	vec4 _ambientCol;
	float _ambientPow;
	
	//Power controls
	float _lightAmbientPow;
	float _lightSpecularPow;
	
	float _shadowBias;
};

layout (std140, binding = 0) uniform u_Lights
{
	DirectionalLight ambience;
};


layout(binding = 0) uniform sampler2D s_albedoTex;
layout(binding = 3) uniform sampler2D s_positionTex;
layout(binding = 4) uniform sampler2D s_lightAccumTex;
layout(binding = 5) uniform sampler2D s_skyBox;

uniform vec3 u_PlayerPos;
uniform vec3 u_EnemyPos;

out vec4 frag_color;

void main()
{

	float distPlay= max(4.0,distance(u_PlayerPos,texture(s_positionTex,inUV).xyz));
	float distEnemy =max(4.0,distance(u_EnemyPos,texture(s_positionTex,inUV).xyz));


     //albedo
    vec4 textureColor=texture(s_albedoTex,inUV);
    //light accum
    vec4 lightAccum = texture(s_lightAccumTex,inUV);
    //skybox
    //vec4 skybox = texture(s_skyBox,inUV);

    vec3 ambient = ambience._lightAmbientPow*ambience._ambientCol.rgb;

    //vec3 result = (ambient +lightAccum.rgb)*textureColor.rgb;
    vec3 result = (ambient +lightAccum.rgb);

    //result = result*skybox.rgb;

    //frag_color=vec4(result,1.0);

	frag_color =textureColor/(distPlay/3)*vec4(result,1.0)+vec4(1/(distPlay),0.0f,1/(distEnemy),0.0f);

}