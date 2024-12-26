#pragma once

#include <vector>
#include <glm/glm.hpp>


namespace Misk {

	class Light {
	public:
		virtual void init(std::vector<glm::vec4> lightPos) = 0;
		virtual void drawAsSquar() = 0;
		//static Light CreateLight() ;
	};
}