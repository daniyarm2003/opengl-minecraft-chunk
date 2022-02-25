#pragma once

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <iostream>

#include "resources.h"

namespace rsrc {
	class BlockFaceDrawer {
	public:
		GLuint vao, vbo, ivbo;
		std::vector<glm::mat4> iTransforms;

		std::string shader, texture;

		BlockFaceDrawer(float* originVerts, unsigned int size, std::string shader, std::string texture);
		~BlockFaceDrawer();

		void draw();

		void bufferInstances();
	};

	struct SkyboxDrawer {
	public:
		GLuint vao, vbo;

		std::string shader, texture;

		SkyboxDrawer(std::string shader, std::string texture);
		~SkyboxDrawer();

		void draw();
	};
}

#endif