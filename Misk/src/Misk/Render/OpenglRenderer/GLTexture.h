#pragma once
#include "Misk/Render/Texture.h"


namespace Misk {
	class GLTexture : public Texture{
	public:

		virtual void loadTexture(const char* path) override;

		virtual void applyTexture(unsigned int textureUnit) override;
	};

}