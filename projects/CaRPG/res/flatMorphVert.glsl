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
layout(location = 3) out vec3 outColor;

uniform vec2 offset;
uniform mat4 scale;
uniform float aspect;
uniform float t;

void main() {

	vec3 mixed = mix(inPosition,inPosition2,t);
	vec4 scaled = scale * vec4(mixed.x,-mixed.z*aspect,mixed.y, 1.0);
	gl_Position = vec4(scaled.x+offset.x,scaled.y+offset.y,scaled.zw);

	// Lecture 5
	// Pass vertex pos in world space to frag shader
	outPos = gl_Position.xyz;

	// Normals
	outNormal = inNormal;

	///////////
	outColor = vec3(1.0,1.0,1.0);
	outUV = inUV;
}

