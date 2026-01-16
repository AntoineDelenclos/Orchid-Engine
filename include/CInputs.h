#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread> //Utile depuis C++11 pour utiliser sleep_for() ou sleep_until()
#include <cmath>
#include <fstream>
#include <map>

//#define GLEW_STATIC //car on lie via gl32s.lib
#include "../libs/GLEW/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include "../libs/GLFW/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/include/GLFW/glfw3.h"

//GLM
#include "../libs/GLM/glm-0.9.9.8/glm/glm/glm.hpp"
#include "../libs/GLM/glm-0.9.9.8/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/GLM/glm-0.9.9.8/glm/glm/gtc/type_ptr.hpp"

#include "GlobalTools.h"
#include "CException.h"
#include "CCamera.h"

class CEngine;

class CInputs {
private:
public:
	glm::mat4 mat4INPMovement;
	std::string strINPKeyBindsPathFile;
	double dINPDiffTime;
	CCamera camINPChosenCamera;
	int iINPCameraState;
	double dINPLastMouseX;
	double dINPLastMouseY;
	double dINPSensitivity;
	bool bINPFirstMouse;
	CInputs();
	CInputs(CCamera &camera);
	~CInputs();
	//Callbacks methods

	//Use keycallback for inputs that doesn't need to be smooth (like instant input)
	void INPKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void INPMouseCallback(GLFWwindow* window, double xpos, double ypos);
	void INPScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void INPSetMovement(glm::mat4 movement);
	void INPSetKeyBindsPathFile(std::string path);
	glm::mat4 mat4INPGetMovement();
	std::string strINPGetKeyBindsPathFile();

	//For inputs that needed to be executed in other classes (like in CEngineInterface)
	bool bINPBackspaceInputTextInterface;

	//For inputs that need to be smooth (like movements input)
	void processInputs(GLFWwindow* window);

	//Bindings
	std::map<std::string, int> mapStrIntINPKeybinds;
	void INPAddingKeybind(std::string function_name, int key);
	void INPWriteMapBindingsOnTxtFile();
	std::string strINPMapBindingsFromFileToString();
	void INPMapBindings(std::string bindings_from_file);
};