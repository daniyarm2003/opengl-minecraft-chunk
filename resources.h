#pragma once

#ifndef RESOURCES_H
#define RESOURCES_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <map>

namespace rsrc {

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 col;
		glm::vec2 uv;
	};

	struct Shader {
	private:
		bool compileShader(GLuint shader);
		GLuint programID;

	public:
		Shader();
		Shader(std::string vsFile, std::string fsFile);
		~Shader();

		void use();

		void unifBool(std::string name, bool val);
		void unifInt(std::string name, GLint val);

		void unif1(std::string name, GLfloat val);
		void unif2(std::string name, GLfloat x, GLfloat y);
		void unif3(std::string name, GLfloat x, GLfloat y, GLfloat z);
		void unif4(std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

		void unifVec2(std::string name, glm::vec2 vec);
		void unifVec3(std::string name, glm::vec3 vec);
		void unifVec4(std::string name, glm::vec4 vec);

		void unifMat4(std::string name, glm::mat4 mat);

		operator GLuint() const;
	};

	struct ResourceManager {
	public:
		std::map<std::string, Shader*> shaderMap;
		std::map<std::string, std::pair<GLuint, GLuint>*> textureMap;

		ResourceManager();
		~ResourceManager();

		void loadTexture2D(std::string id, std::string file);
		void loadSkyboxTextures(std::string id, std::string* faces);

		void loadShader(std::string id, std::string vShaderFile, std::string fShaderFile);

		std::pair<GLuint, GLuint>* bindTexture(std::string id);
		Shader* useShader(std::string id);
	};
}

#endif