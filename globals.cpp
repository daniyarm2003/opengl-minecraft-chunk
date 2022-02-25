#include "globals.h"

#include "resources.h"
#include "transform.h"
#include "blocks.h"
#include "chunk.h"

#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

double globals::time = 0.0;
double globals::dt = 1.0 / 60.0;

bool* globals::keys = new bool[400];

GLFWwindow* globals::window = nullptr;

rsrc::ResourceManager* globals::resourceManager = new rsrc::ResourceManager();

vector<blocks::Block*> globals::blocklist = vector<blocks::Block*>();
vector<chunk::Chunk*> globals::chunks = vector<chunk::Chunk*>();

rsrc::SkyboxDrawer* globals::skyboxDrawer = nullptr;

structs::Camera globals::camera = structs::Camera();
structs::Mouse globals::mouse = structs::Mouse();

float* globals::faceverts::vertsFront = new float[] {
	-0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.125f, -0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.125f, 0.125f, 0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
	
};

float* globals::faceverts::vertsBack = new float[] {
	-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.125f, -0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.125f, 0.125f, -0.125f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

float* globals::faceverts::vertsLeft = new float[] {
	-0.125, -0.125, -0.125, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.125, 0.125, -0.125, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.125, -0.125, 0.125, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.125, 0.125, 0.125, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.125, -0.125, 0.125, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.125, 0.125, -0.125, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

float* globals::faceverts::vertsRight = new float[] {
	0.125, -0.125, -0.125, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.125, -0.125, 0.125, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.125, 0.125, -0.125, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

	0.125, 0.125, 0.125, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.125, 0.125, -0.125, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.125, -0.125, 0.125, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
};

float* globals::faceverts::vertsTop = new float[] {
	-0.125, 0.125, -0.125, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.125, 0.125, -0.125, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.125, 0.125, 0.125, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	0.125, 0.125, 0.125, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.125, 0.125, 0.125, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.125, 0.125, -0.125, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
};

float* globals::faceverts::vertsBottom = new float[] {
	-0.125, -0.125, -0.125, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.125, -0.125, 0.125, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.125, -0.125, -0.125, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	0.125, -0.125, 0.125, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.125, -0.125, -0.125, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.125, -0.125, 0.125, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
};

float* globals::skyboxVertices = new float[] {
	     
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

bool globals::initWindow(string title) {
	glfwInit();

	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);

#ifdef __APPLE__

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#endif

	globals::window = glfwCreateWindow(globals::WIDTH, globals::HEIGHT, title.c_str(), nullptr, nullptr);

	if (!globals::window) {
		cout << "F in the chat for the broken window :(" << endl;
		glfwTerminate();

		return false;
	}

	for (unsigned int i = 0; i < 400; i++) {
		globals::keys[i] = false;
	}

	glfwMakeContextCurrent(globals::window);
	return true;
}