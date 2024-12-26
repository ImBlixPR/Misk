#include "mkpch.h"
#include "Shader.h"

#include "Misk/Platform/OpenGl/Renderer/OpenglShader.h"


namespace Misk {
	Shader* CreateShader()
	{
		return new OpenglShader();
	}
}