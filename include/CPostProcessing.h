#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread> //Utile depuis C++11 pour utiliser sleep_for() ou sleep_until()
#include <cmath>

//#define GLEW_STATIC //car on lie via gl32s.lib
#include "../libs/GLEW/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include "../libs/GLFW/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/include/GLFW/glfw3.h"

//GLM
#include "../libs/GLM/glm-0.9.9.8/glm/glm/glm.hpp"
#include "../libs/GLM/glm-0.9.9.8/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/GLM/glm-0.9.9.8/glm/glm/gtc/type_ptr.hpp"

#include "CException.h"

class CPostProcessing {
private:
    GLfloat glfPOPBrightness;
    GLfloat glfPOPContrast;
    GLfloat glfPOPSaturation;
    GLfloat glfPOPGamma;
    GLfloat* pglfPOPBrightnessLimits;
    GLfloat* pglfPOPContrastLimits;
    GLfloat* pglfPOPSaturationLimits;
    GLfloat* pglfPOPGammaLimits;
    bool bPOPNormeRec709;

public:
    CPostProcessing();
    ~CPostProcessing();
    void POPSetBrightness(GLfloat brightness);
    void POPSetContrast(GLfloat contrast);
    void POPSetSaturation(GLfloat saturation);
    void POPSetGamma(GLfloat gamma);
    GLfloat glfPOPGetBrightness();
    GLfloat glfPOPGetContrast();
    GLfloat glfPOPGetSaturation();
    GLfloat glfPOPGetGamma();
    void POPSetBrightnessLimits(GLfloat below, GLfloat above);
    void POPSetContrastLimits(GLfloat below, GLfloat above);
    void POPSetSaturationLimits(GLfloat below, GLfloat above);
    void POPSetGammaLimits(GLfloat below, GLfloat above);
    GLfloat* pglfPOPGetBrightnessLimits();
    GLfloat* pglfPOPGetContrastLimits();
    GLfloat* pglfPOPGetSaturationLimits();
    GLfloat* pglfPOPGetGammaLimits();
    void POPSetNormeRec709(bool bNorme);
};