#pragma once

#include "Misk/Render/Shader.h"

#include <glad/glad.h>

namespace Misk {

	class OpenglShader : public Shader
	{
	public:
		OpenglShader();

		OpenglShader(const char* vShaderPath, const char* fShaderPath);


		void init(const char* vShaderPath, const char* fShaderPath) override;

		void use() override;

		void clearShader();
		~OpenglShader();


	public:
		//uniform set functions
		void setBool(const std::string& name, bool value) const override;
		void setInt(const std::string& name, int value) const override;
		void setFloat(const std::string& name, float value) const override;
		void setVec3f(const std::string& name, glm::vec3 value) const override;
		void setVec4f(const std::string& name, glm::vec4 value) const override;
		void setMat4f(const std::string& name, glm::mat4 value) const override;
		void setMat3f(const std::string& name, glm::mat3 value) const override;


	private:

		std::string vertexCode;
		std::string fragmentCode;

		unsigned int shaderId;

	private:
		void addShader(std::string shaderCode, GLenum shaderType);

		std::string loadShaderCode(const char* path);
	};

}

