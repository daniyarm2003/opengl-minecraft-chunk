#version 330 core

layout (location=0) in vec3 aPos;

out vec3 texPos;

uniform mat4 viewProjMat;

void main() {
	texPos = aPos;
	vec4 pos = viewProjMat * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	gl_Position = pos.xyww;
}