#pragma once
#include <glm\glm.hpp>
#include "Misk/Event/KeyEvent.h"
#include "Misk/Event/MouseEvent.h"

namespace Misk {


	class Camera
	{
	public:
		Camera();
		Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);

		void freeCamera(float deltaTime);
		void mouseControl(float xOffset, float yOffset);

		glm::mat4 calculateViewMatrix();
		inline glm::vec3 getFront() { return front; }
		inline glm::vec3 getUpVector() { return up; }
		inline glm::vec3 getUpWorldVector() { return glm::vec3(0.0f, 1.0f, 0.0f); }

		glm::vec3 getCameraPosition();
		glm::vec3 getCameraDirection();

		~Camera();

	private:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;

		float yaw;
		float pitch;

		float moveSpeed;
		float turnSpeed;
		void update();
	};
}