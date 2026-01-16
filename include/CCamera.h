#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread> //Utile depuis C++11 pour utiliser sleep_for() ou sleep_until()
#include <cmath>
#include <vector>
#include "../libs/GLM/glm-0.9.9.8/glm/glm/glm.hpp"
#include "../libs/GLM/glm-0.9.9.8/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/GLM/glm-0.9.9.8/glm/glm/gtc/type_ptr.hpp"

//#define GLEW_STATIC //car on lie via gl32s.lib
#include "../libs/GLEW/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include "../libs/GLFW/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/include/GLFW/glfw3.h"

class CCamera {
public:
	GLfloat fCAMYaw;
	GLfloat fCAMPitch;
	GLfloat fCAMFovZoom;
	float fCAMCameraSpeedMovement;
	glm::vec3 vec3CAMCameraPosition;
	glm::vec3 vec3CAMCameraTarget;
	glm::vec3 vec3CAMCameraDirection;
	glm::vec3 vec3CAMCameraUp;
	glm::vec3 vec3CAMCameraRight;

	glm::mat4 mat4CAMModel;
	glm::mat4 mat4CAMView;
	glm::mat4 mat4CAMProjection;

	glm::vec3 vec3CAMCameraFront;

	CCamera();
	~CCamera();
};