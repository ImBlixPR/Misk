#pragma once


#include <string>
#include <glm/glm.hpp>




namespace Misk {


	class Shader {
	public:
		virtual void init(const char* vShaderPath, const char* fShaderPath) = 0;

		virtual void use() = 0;



	public:
		//uniform set functions
		virtual void setBool(const std::string& name, bool value) const = 0;
		virtual void setInt(const std::string& name, int value) const = 0;
		virtual void setFloat(const std::string& name, float value) const = 0;
		virtual void setVec3f(const std::string& name, glm::vec3 value) const = 0;
		virtual void setVec4f(const std::string& name, glm::vec4 value) const = 0;
		virtual void setMat4f(const std::string& name, glm::mat4 value) const = 0;
		virtual void setMat3f(const std::string& name, glm::mat3 value) const = 0;

	};


	Shader* CreateShader();

}