#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace structs {
	struct Transform {
	public:
		glm::vec3 pos;
		glm::quat rot;
		glm::vec3 scale;

		Transform();
		Transform(glm::vec3 pos, glm::quat rot, glm::vec3 scale);

		glm::mat4 toMat4();
	};

	struct Camera {
	public:
		Transform transform;
		glm::vec3 eulers;

		float fov;

		Camera();

		glm::mat4 getViewMat();
		glm::mat4 getViewMatNoTrnsl();
	};

	struct Mouse {
	public:
		glm::vec2 pos;
		glm::vec2 lastPos;

		bool* clicked;

		Mouse();
		~Mouse();
	};
}

#endif