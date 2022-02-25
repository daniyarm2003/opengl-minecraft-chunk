#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "transform.h"
#include "globals.h"

using namespace glm;

namespace structs {
	Transform::Transform() {
		this->pos = vec3(0.0f, 0.0f, 0.0f);
		this->rot = quat(vec3(0.0f, 0.0f, 0.0f));
		this->scale = vec3(1.0f, 1.0f, 1.0f);
	}

	Transform::Transform(vec3 pos, quat rot, vec3 scale) {
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	mat4 Transform::toMat4() {
		mat4 trans(1.0f);

		mat4 trnsl(1.0f);
		mat4 scale(1.0f);

		trnsl = glm::translate(trnsl, this->pos);
		scale = glm::scale(scale, this->scale);

		trans = trnsl * glm::toMat4(this->rot) * scale * trans;

		return trans;
	}

	Camera::Camera() {
		this->transform = Transform();
		this->eulers = vec3();
		this->fov = 45.0f;
	}

	mat4 Camera::getViewMat() {
		this->transform.rot = angleAxis(this->eulers.y, vec3(0.0f, 1.0f, 0.0f)) * angleAxis(this->eulers.x, vec3(1.0f, 0.0f, 0.0f));

		return perspective(radians(this->fov), (float)globals::WIDTH / (float)globals::HEIGHT, 0.1f, 100.0f) * lookAt(this->transform.pos, this->transform.pos + vec3(this->transform.rot * vec4(0.0f, 0.0f, -1.0f, 1.0f)), vec3(0.0f, 1.0f, 0.0f));
	}

	mat4 Camera::getViewMatNoTrnsl() {
		this->transform.rot = angleAxis(this->eulers.y, vec3(0.0f, 1.0f, 0.0f)) * angleAxis(this->eulers.x, vec3(1.0f, 0.0f, 0.0f));

		return perspective(radians(this->fov), (float)globals::WIDTH / (float)globals::HEIGHT, 0.1f, 100.0f) * lookAt(vec3(0.0f), vec3(this->transform.rot * vec4(0.0f, 0.0f, -1.0f, 1.0f)), vec3(0.0f, 1.0f, 0.0f));
	}

	Mouse::Mouse() {
		this->pos = vec2(0.0f, 0.0f);
		this->lastPos = vec2(0.0f, 0.0f);

		this->clicked = new bool[3];

		for (unsigned int i = 0; i < 3; i++) {
			this->clicked[i] = false;
		}
	}

	Mouse::~Mouse() {
		delete[] this->clicked;
	}
}