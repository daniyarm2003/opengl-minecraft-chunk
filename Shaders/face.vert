#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aCol;
layout (location=2) in vec2 aUV;
layout (location=3) in mat4 transform;

uniform mat4 viewProjMat;

out vec2 uvCoord;
out vec3 fragCol;

void main() {
	gl_Position = viewProjMat * transform * vec4(aPos, 1.0f);
	
	fragCol = aCol;
	uvCoord = aUV;
}