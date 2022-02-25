#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H

#include "resources.h"
#include "drawable.h"
#include "transform.h"
#include "blocks.h"
#include "chunk.h"

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace globals {

	extern GLFWwindow* window;

	extern bool* keys;

	extern double time;
	extern double dt;

	extern rsrc::ResourceManager* resourceManager;

	extern std::vector<blocks::Block*> blocklist;
	extern std::vector<chunk::Chunk*> chunks;

	extern rsrc::SkyboxDrawer* skyboxDrawer;

	extern structs::Camera camera;
	extern structs::Mouse mouse;

	extern constexpr unsigned int WIDTH = 800;
	extern constexpr unsigned int HEIGHT = 600;

	extern bool initWindow(std::string title);

	namespace faceverts {
		extern float* vertsFront;
		extern float* vertsBack;

		extern float* vertsLeft;
		extern float* vertsRight;

		extern float* vertsTop;
		extern float* vertsBottom;
	}

	extern float* skyboxVertices;
}

#endif