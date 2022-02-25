#include <glm/glm.hpp>
#include <glad/glad.h>

#include <vector>
#include <iostream>

#include "resources.h"
#include "drawable.h"
#include "globals.h"

using namespace std;
using namespace glm;

namespace rsrc {
	void BlockFaceDrawer::bufferInstances() {

		if (this->iTransforms.size() == 0)
			return;

		mat4* iTransformsPtr = this->iTransforms.data();

		glBindBuffer(GL_ARRAY_BUFFER, this->ivbo);
		glBufferData(GL_ARRAY_BUFFER, this->iTransforms.size() * sizeof(mat4), &iTransformsPtr[0], GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	BlockFaceDrawer::BlockFaceDrawer(float* originVerts, unsigned int size, string shader, string texture) {
		this->iTransforms = vector<mat4>();

		this->shader = shader;
		this->texture = texture;

		glGenVertexArrays(1, &this->vao);

		glGenBuffers(1, &this->vbo);
		glGenBuffers(1, &this->ivbo);

		this->bufferInstances();

		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glBufferData(GL_ARRAY_BUFFER, size, originVerts, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, this->ivbo);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)0);

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)sizeof(vec4));

		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(2 * sizeof(vec4)));

		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(3 * sizeof(vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	BlockFaceDrawer::~BlockFaceDrawer() {
		glDeleteBuffers(1, &this->vbo);
		glDeleteBuffers(1, &this->ivbo);

		glDeleteVertexArrays(1, &this->vao);
	}

	void BlockFaceDrawer::draw() {
		if (this->iTransforms.size() == 0)
			return;

		glActiveTexture(GL_TEXTURE0);
		globals::resourceManager->bindTexture(this->texture);

		rsrc::Shader* shader = globals::resourceManager->useShader(this->shader);
		shader->unifInt("face", 0);
		shader->unifMat4("viewProjMat", globals::camera.getViewMat());

		glBindVertexArray(this->vao);

		this->bufferInstances();

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, (GLsizei)this->iTransforms.size());

		glBindVertexArray(0);

		this->iTransforms.clear();
	}

	SkyboxDrawer::SkyboxDrawer(string shader, string texture) {
		this->shader = shader;
		this->texture = texture;

		glGenVertexArrays(1, &this->vao);
		glGenBuffers(1, &this->vbo);

		glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

		glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), globals::skyboxVertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	SkyboxDrawer::~SkyboxDrawer() {
		glDeleteBuffers(1, &this->vbo);
		glDeleteVertexArrays(1, &this->vao);
	}

	void SkyboxDrawer::draw() {
		glDepthFunc(GL_LEQUAL);
		glFrontFace(GL_CCW);

		glBindVertexArray(this->vao);

		glActiveTexture(GL_TEXTURE0);
		globals::resourceManager->bindTexture(this->texture);

		rsrc::Shader* shader = globals::resourceManager->useShader(this->shader);

		shader->unifInt("skybox", 0);
		shader->unifMat4("viewProjMat", globals::camera.getViewMatNoTrnsl());

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glFrontFace(GL_CW);
		glDepthFunc(GL_LESS);
	}
}