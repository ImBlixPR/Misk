#include "mkpch.h"
#include "OpenglShader.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>




namespace Misk {


	OpenglShader::OpenglShader()
	{
	}

	OpenglShader::OpenglShader(const char* vShaderPath, const char* fShaderPath)
	{
		vertexCode = loadShaderCode(vShaderPath);
		fragmentCode = loadShaderCode(fShaderPath);
	}

	void OpenglShader::init(const char* vShaderPath, const char* fShaderPath)
	{
		vertexCode = loadShaderCode(vShaderPath);
		fragmentCode = loadShaderCode(fShaderPath);

		shaderId = glCreateProgram();
		if (!shaderId)
		{
			printf("Error creating shader program!\n");
			return;
		}

		addShader(vertexCode, GL_VERTEX_SHADER);
		addShader(fragmentCode, GL_FRAGMENT_SHADER);

		GLint result = 0;
		GLchar eLog[1024] = { 0 };

		glLinkProgram(shaderId);
		glGetProgramiv(shaderId, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shaderId, sizeof(eLog), NULL, eLog);
			printf("Error linking program: '%s'\n", eLog);
			return;
		}

		glValidateProgram(shaderId);
		glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shaderId, sizeof(eLog), NULL, eLog);
			printf("Error validating program: '%s'\n", eLog);
			return;
		}

	}

	void OpenglShader::use()
	{
		glUseProgram(shaderId);
	}

	void OpenglShader::clearShader()
	{
		if (shaderId != 0)
		{
			glDeleteProgram(shaderId);
			shaderId = 0;
		}
	}

	void OpenglShader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
	}

	void OpenglShader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (GLint)value);
	}

	void OpenglShader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderId, name.c_str()), (GLfloat)value);
	}




	void OpenglShader::setVec3f(const std::string& name, glm::vec3 value) const
	{
		glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, glm::value_ptr(value));
	}

	void OpenglShader::setVec4f(const std::string& name, glm::vec4 value) const
	{
		glUniform4fv(glGetUniformLocation(shaderId, name.c_str()), 1, glm::value_ptr(value));
	}

	void OpenglShader::setMat4f(const std::string& name, glm::mat4 value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenglShader::setMat3f(const std::string& name, glm::mat3 value) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	OpenglShader::~OpenglShader()
	{
		clearShader();
	}


	void OpenglShader::addShader(std::string shaderCode, GLenum shaderType)
	{
		GLuint theShader = glCreateShader(shaderType);

		const GLchar* theCode[1];
		theCode[0] = shaderCode.c_str();

		GLint codeLenght[1];
		codeLenght[0] = strlen(shaderCode.c_str());

		glShaderSource(theShader, 1, theCode, codeLenght);
		glCompileShader(theShader);

		GLint result = 0;
		GLchar eLog[1024] = { 0 };


		glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
			printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
			return;
		}

		glAttachShader(shaderId, theShader);
	}

	std::string OpenglShader::loadShaderCode(const char* path)
	{
		std::string content;
		std::ifstream fileStream(path, std::ios::in);

		if (!fileStream.is_open())
		{
			printf("Faild to read %s| File doesn't exist.", path);
		}

		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();

		return content;
	}

}