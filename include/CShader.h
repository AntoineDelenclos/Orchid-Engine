#pragma once
#ifndef CSHADER_H
#define CSHADER_H
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class CShader {
public:
	GLuint Program;

	CShader();
	CShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~CShader();

	void SHAUse();
	//Lie la texture à l'unité donnée et pointe le sampler "samplerName" dessus (le shader doit être actif)
	void SHABindTexture(const char* samplerName, GLuint textureId, GLuint unit);
	//Envoie les valeurs du matériau de core.frag (le shader doit être actif)
	void SHASetMaterial(const glm::vec3& ambient, float shininess, float transparency);
};


#endif // !CSHADER_H