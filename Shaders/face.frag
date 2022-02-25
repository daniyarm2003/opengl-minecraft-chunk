#version 330 core

in vec3 fragCol;
in vec2 uvCoord;

uniform sampler2D face;

void main() {
	gl_FragColor = texture(face, uvCoord) * vec4(fragCol, 1.0f);
}