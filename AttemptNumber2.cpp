#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <thread>

#include <vector>

#include "globals.h"
#include "drawable.h"
#include "transform.h"
#include "blocks.h"
#include "chunk.h"

using namespace std;
using namespace glm;

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (action) {
	case GLFW_PRESS:
		globals::keys[key] = true;
		break;

	case GLFW_RELEASE:
		globals::keys[key] = false;
		break;
	}
}

bool firstMove = true;

void mousePosCallback(GLFWwindow* window, double xPos, double yPos) {
	vec2 newPos = vec2((float)xPos, (float)yPos);

	globals::mouse.pos = newPos;

	if (firstMove) {
		firstMove = false;
		globals::mouse.lastPos = newPos;
	}
}

void mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
	glfwSetInputMode(globals::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void init() {
	globals::resourceManager->loadShader("face_shader", "face", "face");
	globals::resourceManager->loadShader("skybox_shader", "skybox", "skybox");

	globals::resourceManager->loadTexture2D("craft_f", "crafting_table_front");
	globals::resourceManager->loadTexture2D("craft_s", "crafting_table_side");
	globals::resourceManager->loadTexture2D("craft_t", "crafting_table_top");
	globals::resourceManager->loadTexture2D("oak_p", "oak_planks");

	globals::resourceManager->loadTexture2D("grassb_s", "grass_block_side");
	globals::resourceManager->loadTexture2D("grassb_t", "grass_block_top");
	globals::resourceManager->loadTexture2D("dirt", "dirt");

	string skyTxtrs[] = {
		"skyboxfront",
		"skyboxback",
		"skyboxdown",
		"skyboxup",
		"skyboxright",
		"skyboxleft",
	};

	globals::resourceManager->loadSkyboxTextures("skybox", skyTxtrs);

	globals::skyboxDrawer = new rsrc::SkyboxDrawer("skybox_shader", "skybox");

	globals::blocklist.push_back(new blocks::Block(0U, "grassb_s", "grassb_s", "grassb_s", "grassb_s", "grassb_t", "dirt"));
	globals::blocklist.push_back(new blocks::Block(1U, "dirt", "dirt", "dirt", "dirt", "dirt", "dirt"));

	chunk::Chunk* c = new chunk::Chunk(0, 0);

	c->populate();

	globals::chunks.push_back(c);

	globals::camera.transform.pos.y = 3.0f;
}

void update() {
	if (globals::keys[GLFW_KEY_ESCAPE]) {
		glfwSetInputMode(globals::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		globals::mouse.lastPos = globals::mouse.pos;
	}

	vec2 dMousePos = globals::mouse.pos - globals::mouse.lastPos;

	globals::camera.eulers.x = clamp(globals::camera.eulers.x - dMousePos.y / 100.0f, -radians(89.0f), radians(89.0f));
	globals::camera.eulers.y -= dMousePos.x / 100.0f;

	float df = globals::keys[GLFW_KEY_W] ? -0.1f : globals::keys[GLFW_KEY_S] ? 0.1f : 0.0f;
	globals::camera.transform.pos += globals::camera.transform.rot * vec3(0.0f, 0.0f, df);

	globals::mouse.lastPos = globals::mouse.pos;

	globals::camera.fov = globals::keys[GLFW_KEY_C] ? 15.0f : 45.0f;

	for (vector<chunk::Chunk*>::iterator it = globals::chunks.begin(); it != globals::chunks.end(); it++) {
		(*it)->draw();
	}
}

void draw() {
	glClearColor(0.0f, 0.65f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (vector<blocks::Block*>::iterator it = globals::blocklist.begin(); it != globals::blocklist.end(); it++) {
		for (unsigned int i = 0; i < 6; i++) {
			(*it)->faces[i].draw();
		}
	}

	globals::skyboxDrawer->draw();
}

int main()
{
	if (!globals::initWindow("OpenGL Minecraft Chunk")) {
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, globals::WIDTH, globals::HEIGHT);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glfwSetFramebufferSizeCallback(globals::window, windowResizeCallback);
	glfwSetKeyCallback(globals::window, keyInputCallback);
	glfwSetCursorPosCallback(globals::window, mousePosCallback);
	glfwSetMouseButtonCallback(globals::window, mouseClickCallback);

	init();

	while (!glfwWindowShouldClose(globals::window)) {
		globals::time = glfwGetTime();

		glfwPollEvents();

		update();

		draw();

		glfwSwapBuffers(globals::window);

		this_thread::sleep_for(chrono::nanoseconds((long long)(1.0 / 60.0 * 1000000000.0)));

		globals::dt = glfwGetTime() - globals::time;
	}

	delete[] globals::keys;
	delete globals::resourceManager;

	delete[] globals::faceverts::vertsFront;
	delete[] globals::faceverts::vertsBack;
	delete[] globals::faceverts::vertsLeft;
	delete[] globals::faceverts::vertsRight;
	delete[] globals::faceverts::vertsTop;
	delete[] globals::faceverts::vertsBottom;

	delete[] globals::skyboxVertices;

	delete globals::skyboxDrawer;

	for (vector<chunk::Chunk*>::iterator it = globals::chunks.begin(); it != globals::chunks.end(); it++) {
		delete* it;
	}

	for (vector<blocks::Block*>::iterator it = globals::blocklist.begin(); it != globals::blocklist.end(); it++) {
		delete* it;
	}

	glfwTerminate();

	return 0;
}