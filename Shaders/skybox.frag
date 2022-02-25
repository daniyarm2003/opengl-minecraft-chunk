#version 330 core

in vec3 texPos;

uniform samplerCube skybox;

void main() {
	gl_FragColor = texture(skybox, texPos);
}