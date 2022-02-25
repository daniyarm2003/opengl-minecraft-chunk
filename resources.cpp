#pragma warning(disable: 4172)

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <map>

#include "resources.h"
#include "stb_image.h"

using namespace std;
using namespace glm;

namespace rsrc {
	bool Shader::compileShader(GLuint shader) {
		glCompileShader(shader);

		int success;
		char infoLog[512];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			cout << infoLog << endl;

			return false;
		}

		return true;
	}

	Shader::Shader() {
		this->programID = 0;
	}

	Shader::Shader(string vsFile, string fsFile) {
		ifstream vsFileStream("Shaders/" + vsFile + ".vert");
		ifstream fsFileStream("Shaders/" + fsFile + ".frag");

		string vsSource = "";
		string fsSource = "";

		char c;

		while (vsFileStream.get(c)) {
			vsSource.push_back(c);
		}

		while (fsFileStream.get(c)) {
			fsSource.push_back(c);
		}

		const char* vsSourcePtr = vsSource.c_str();
		const char* fsSourcePtr = fsSource.c_str();

		GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vShaderID, 1, &vsSourcePtr, nullptr);
		glShaderSource(fShaderID, 1, &fsSourcePtr, nullptr);

		this->compileShader(vShaderID);
		this->compileShader(fShaderID);

		this->programID = glCreateProgram();

		glAttachShader(this->programID, vShaderID);
		glAttachShader(this->programID, fShaderID);
		glLinkProgram(this->programID);

		int success;
		char infoLog[512];

		glGetProgramiv(this->programID, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(this->programID, 512, nullptr, infoLog);
			cout << "F in the chat for the broken shader program :(" << endl;
		}

		glDeleteShader(vShaderID);
		glDeleteShader(fShaderID);
	}

	Shader::~Shader() {
		glDeleteProgram(this->programID);
	}

	void Shader::use() {
		glUseProgram(this->programID);
	}

	void Shader::unifBool(string name, bool val) {
		glUniform1i(glGetUniformLocation(this->programID, name.c_str()), (GLint)val);
	}

	void Shader::unifInt(string name, GLint val) {
		glUniform1i(glGetUniformLocation(this->programID, name.c_str()), val);
	}

	void Shader::unif1(string name, GLfloat val) {
		glUniform1f(glGetUniformLocation(this->programID, name.c_str()), val);
	}

	void Shader::unif2(string name, GLfloat x, GLfloat y) {
		glUniform2f(glGetUniformLocation(this->programID, name.c_str()), x, y);
	}

	void Shader::unif3(string name, GLfloat x, GLfloat y, GLfloat z) {
		glUniform3f(glGetUniformLocation(this->programID, name.c_str()), x, y, z);
	}

	void Shader::unif4(string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
		glUniform4f(glGetUniformLocation(this->programID, name.c_str()), x, y, z, w);
	}

	void Shader::unifVec2(string name, vec2 vec) {
		glUniform2f(glGetUniformLocation(this->programID, name.c_str()), vec.x, vec.y);
	}

	void Shader::unifVec3(string name, vec3 vec) {
		glUniform3f(glGetUniformLocation(this->programID, name.c_str()), vec.x, vec.y, vec.z);
	}

	void Shader::unifVec4(string name, vec4 vec) {
		glUniform4f(glGetUniformLocation(this->programID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::unifMat4(string name, mat4 mat) {
		glUniformMatrix4fv(glGetUniformLocation(this->programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}

	Shader::operator GLuint() const {
		return this->programID;
	}

	ResourceManager::ResourceManager() {
		this->shaderMap = map<string, Shader*>();
		this->textureMap = map<string, pair<GLuint, GLuint>*>();

		stbi_set_flip_vertically_on_load(true);
	}

	ResourceManager::~ResourceManager() {
		for (map<string, Shader*>::iterator it = this->shaderMap.begin(); it != shaderMap.end(); it++) {
			delete it->second;
		}

		for (map<string, pair<GLuint, GLuint>*>::iterator it = this->textureMap.begin(); it != textureMap.end(); it++) {
			glDeleteTextures(1, &it->second->second);
			delete it->second;
		}
	}

	void ResourceManager::loadShader(string id, string vShaderFile, string fShaderFile) {
		this->shaderMap.insert(pair<string, Shader*>(id, new Shader(vShaderFile, fShaderFile)));
	}

	void ResourceManager::loadTexture2D(string id, string file) {
		GLuint textureID;

		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		int width, height, nrChannels;

		unsigned char* data = stbi_load(("Textures/" + file + ".png").c_str(), &width, &height, &nrChannels, 0);

		if (!data) {
			cout << "F in the chat for the broken texture :(" << endl;
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		this->textureMap.insert(pair<string, pair<GLuint, GLuint>*>(id, new pair<GLuint, GLuint>(GL_TEXTURE_2D, textureID)));
	}

	void ResourceManager::loadSkyboxTextures(string id, string* faces) {
		GLuint textureID;

		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		for (unsigned int i = 0; i < 6; i++) {
			int width, height, nrChannels;

			unsigned char* data = stbi_load(("Textures/" + faces[i] + ".jpg").c_str(), &width, &height, &nrChannels, 0);

			if (!data) {
				cout << "F in the chat for the broken texture :(" << endl;
				return;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}

		this->textureMap.insert(pair<string, pair<GLuint, GLuint>*>(id, new pair<GLuint, GLuint>(GL_TEXTURE_CUBE_MAP, textureID)));
	}

	Shader* ResourceManager::useShader(string id) {
		Shader* shader = this->shaderMap[id];
		shader->use();

		return shader;
	}

	pair<GLuint, GLuint>* ResourceManager::bindTexture(string id) {
		pair<GLuint, GLuint>* texture = this->textureMap[id];

		glBindTexture(texture->first, texture->second);

		return texture;
	}
}