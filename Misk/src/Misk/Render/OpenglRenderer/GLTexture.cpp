#include "mkpch.h"
#include "GLTexture.h"

#include "stb_image.h"
#include <glad/glad.h>



namespace Misk {

	Texture* Texture::CreateTexture()
	{
		return new GLTexture();
	}

	void GLTexture::loadTexture(const char* path)
	{
		glGenTextures(1, &textureId);

		int w, h, bitDepth;
		unsigned char* data = stbi_load(path, &w, &h, &bitDepth, 0);
		
		if (data)
		{
			GLenum internalFormat;
			GLenum dataFormat;

			if (bitDepth == 4) {
				internalFormat = GL_RGBA;
				dataFormat = GL_RGBA;
			}
			else if (bitDepth == 3) {
				internalFormat = GL_RGB;
				dataFormat = GL_RGB;
			}
			else {
				std::cout << "Unknown texture format" << std::endl;
				textureId = 0; // Return an invalid texture ID to indicate failure
				return;
			}

			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, dataFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			textureId = 0;  // Set texture ID to 0 to indicate failure
			MK_CORE_ERROR("Falid to load texture path '{0}'", path);
			return;
		}

		stbi_image_free(data);
		MK_CORE_INFO("Texture loaded with ID {0}, path '{1}'", textureId, path);


	}
	void GLTexture::applyTexture(unsigned int textureUnit)
	{
		if (textureUnit >= GL_TEXTURE0 && textureUnit < GL_TEXTURE0 + GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
			glActiveTexture(GL_TEXTURE0 + textureUnit); // Activate the specified texture unit
			glBindTexture(GL_TEXTURE_2D, textureId);   // Bind the texture to the unit
		}
	}



}

