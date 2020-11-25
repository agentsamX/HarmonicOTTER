#version 410

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inUV;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inPosition2;
layout(location = 4) in vec3 inUV2;
layout(location = 5) in vec3 inNormal2;

layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outUV;
layout(location = 2) out vec3 outNormal;
layout(location = 4) out vec3 outColor;

uniform mat4 u_ModelViewProjection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform mat3 u_ModelRotation;
uniform vec3 u_LightPos;
uniform float t;


void main() {

	gl_Position = u_ModelViewProjection * vec4(inPosition, 1.0);

	// Lecture 5
	// Pass vertex pos in world space to frag shader
	outPos = (u_Model * vec4(mix(inPosition,inPosition2,t), 1.0)).xyz;

	// Normals
	outNormal = u_ModelRotation * mix(inNormal,inNormal2,t);

	///////////
	outColor = vec3(1.0,1.0,1.0);
	outUV = inUV;
}