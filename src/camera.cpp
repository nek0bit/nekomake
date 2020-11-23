#include "camera.hpp"

Camera::Camera(int& viewWidth, int& viewHeight) : viewWidth{ viewWidth }, viewHeight{ viewHeight }, eye{ 0.0f, 0.0f, 0.0f },
center{ 0.0f, 0.0f, -1.0f }, up{ 0.0f, 1.0f, 0.0f }, yaw{ 0.0f }, pitch{ 0.0f }, roll{ 0.0f }
{
	projection = glm::perspective(glm::radians(45.0f), (float)viewWidth / (float)viewHeight, 0.1f, 100.0f);
}

Camera::~Camera()
{

}

void Camera::set(Shader &shader) {
	shader.use();
	shader.setUniformMatrix4fv(shader.projectionLoc, glm::value_ptr(projection));
	shader.setUniformMatrix4fv(shader.viewLoc, glm::value_ptr(view));
}

void Camera::update()
{
	// Update euler angles
	center.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	center.y = sin(glm::radians(pitch));
	center.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	view = glm::lookAt(eye, eye + glm::normalize(center), up);
}

// Generic functions
void Camera::rotateYaw(float amount)
{
	yaw += amount;
	if (yaw > 360.0)
	{
		yaw = 0.0;
	}
	else if (yaw < 0.0)
	{
		yaw = 360.0;
	}
}

void Camera::rotatePitch(float amount)
{
	pitch += amount;
	if (pitch > 360.0)
	{
		pitch = 0.0;
	}
	else if (pitch < 0.0)
	{
		pitch = 360.0;
	}
}

void Camera::rotateRoll(float amount)
{
	roll += amount;
}