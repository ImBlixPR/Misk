#include "mkpch.h"
#include "Cemera.h"

#include "Misk/KeyCode.h"
#include "Misk/Input.h"

#include <glm\gtc\matrix_transform.hpp>
namespace Misk {
	Camera::Camera()
	{
	}

	Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed)
	{
		position = startPosition;
		worldUp = startUp;
		yaw = startYaw;
		pitch = startPitch;

		moveSpeed = startMoveSpeed;
		turnSpeed = startTurnSpeed;

		update();
	}

	void Camera::freeCamera(float deltaTime)
	{
		
		//? warring
		//! it for free camera you have to impement movemnt in defferent class
		float velocity = moveSpeed * deltaTime;
		if (Input::IsKeyPressed(MK_KEY_W))
		{
			position += front * velocity;
		}
		if (Input::IsKeyPressed(MK_KEY_S))
		{
			position -= front * velocity;
		}
		if (Input::IsKeyPressed(MK_KEY_A))
		{
			position -= right * velocity;
		}
		if (Input::IsKeyPressed(MK_KEY_D))
		{
			position += right * velocity;
		}
		if (Input::IsKeyPressed(MK_KEY_SPACE))
		{
			position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
		}
		if (Input::IsKeyPressed(MK_KEY_LEFT_SHIFT))
		{
			position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
		}

	}

	void Camera::mouseControl(float xOffset, float yOffset)
	{
		float xChange = xOffset;
		float yChange = yOffset;
		xChange *= turnSpeed;
		yChange *= turnSpeed;

		yaw += xChange;
		pitch += yChange;

		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}
		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}

		update();
	}

	glm::mat4 Camera::calculateViewMatrix()
	{
		return glm::lookAt(position, position + front, up);
	}

	glm::vec3 Camera::getCameraPosition()
	{
		return position;
	}

	glm::vec3 Camera::getCameraDirection()
	{
		return glm::normalize(front);
	}

	Camera::~Camera()
	{
	}

	void Camera::update()
	{
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front);

		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));

	}
}
