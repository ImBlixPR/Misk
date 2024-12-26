#pragma once
#include <filesystem>


namespace Misk {
	class Texture {
	public:
		Texture(){}
		unsigned int textureId;
		std::filesystem::path mFilePath;

		virtual void loadTexture(const char* path) = 0;

		virtual void applyTexture(unsigned int textureUnit) = 0;

		static Texture* CreateTexture();
	};

}