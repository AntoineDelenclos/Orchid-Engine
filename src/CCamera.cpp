#include "../include/CCamera.h"

CCamera::CCamera() {
	fCAMYaw = -90.f;
	fCAMPitch = 0.f;
	fCAMFovZoom = 45.f;
	fCAMCameraSpeedMovement = 20.f; //Speed of the camera movement (body wise not for the sensi of the camera view movement)
	fCAMCameraSensitivity = 0.05f;
	vec3CAMCameraPosition = glm::vec3{ 0.f,0.f,0.f };
	vec3CAMCameraFront = glm::vec3{ 0.f,0.f,-1.f };
	vec3CAMCameraUp = glm::vec3{ 0.f,1.f,0.f };
	vec3CAMCameraDirection.x = cos(glm::radians(fCAMYaw)) * cos(glm::radians(fCAMPitch));
	vec3CAMCameraDirection.y = sin(glm::radians(fCAMPitch));
	vec3CAMCameraDirection.z = sin(glm::radians(fCAMYaw)) * cos(glm::radians(fCAMPitch));
	mat4CAMModel = glm::mat4(1.f);
	mat4CAMModel = glm::rotate(mat4CAMModel, glm::radians(0.0f), glm::vec3(0.5f, 1.0f, 0.0f)); //Perspective projection ROTATION = 0.0f ICI
	mat4CAMView = glm::mat4(1.f);
	mat4CAMView = glm::lookAt(vec3CAMCameraPosition, vec3CAMCameraPosition+vec3CAMCameraFront, vec3CAMCameraUp);
	mat4CAMProjection = glm::perspective(glm::radians(fCAMFovZoom), (float)1920 / (float)1080, 0.1f, 100.f);
}

CCamera::~CCamera() {

}