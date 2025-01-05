#pragma once
#include "CEntity.h"

class CCube : public CEntity {
public:
    unsigned int uiCUBId;
	const char* pcCUBVertexShaderName; //Nom du fichier, par exemple : "core.vert"
	const char* pcCUBFragmentShaderName;
	GLfloat* pgfCUBVertices;
	unsigned int uiCUBVerticesSize;
    GLfloat gfCUBScaleRatio;
    
    GLfloat gfCUBLength;
    GLfloat gfCUBHeight;
    GLfloat gfCUBDepth;

	//Material values
	glm::vec3 vec3CUBAmbient;
	glm::vec3 vec3CUBDiffuse;
	glm::vec3 vec3CUBSpecular;
	float fCUBShininess;
	float fCUBTransparency;
    //Texture
	unsigned int uiCUBTextureEngineNumber;
    unsigned int uiCUBSpecularTextureEngineNumber;
    //Les vertices d'un cube de base
    static const GLfloat* cubeVertices() {
        //Par défaut dans OpenGL les valeurs de l'écran vont de -1 à 1
        static const GLfloat cVer[288] = { //Perspective projection Définition d'un cube
            //Positions           //Texture Coords    //Normal
            //Page 8 du carnet contient la référence des faces.
            //Face 4
            -0.1f, -0.1f, -0.1f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f, //All normals goes to zero at initializing
            0.1f, -0.1f, -0.1f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
            0.1f,  0.1f, -0.1f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f, //tester avec notre fonction normalizevector
            0.1f,  0.1f, -0.1f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
            -0.1f,  0.1f, -0.1f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
            -0.1f, -0.1f, -0.1f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
            //Face 1
            -0.1f, -0.1f,  0.1f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
            0.1f, -0.1f,  0.1f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
            0.1f,  0.1f,  0.1f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            0.1f,  0.1f,  0.1f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            -0.1f,  0.1f,  0.1f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            -0.1f, -0.1f,  0.1f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
            //Face 2
            -0.1f,  0.1f,  0.1f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
            -0.1f,  0.1f, -0.1f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
            -0.1f, -0.1f, -0.1f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
            -0.1f, -0.1f, -0.1f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
            -0.1f, -0.1f,  0.1f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
            -0.1f,  0.1f,  0.1f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
            //Face 5
            0.1f,  0.1f,  0.1f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
            0.1f,  0.1f, -0.1f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
            0.1f, -0.1f, -0.1f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
            0.1f, -0.1f, -0.1f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
            0.1f, -0.1f,  0.1f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
            0.1f,  0.1f,  0.1f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
            //Face 6
            -0.1f, -0.1f, -0.1f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
            0.1f, -0.1f, -0.1f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
            0.1f, -0.1f,  0.1f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
            0.1f, -0.1f,  0.1f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
            -0.1f, -0.1f,  0.1f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
            -0.1f, -0.1f, -0.1f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
            //Face 3
            -0.1f,  0.1f, -0.1f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
            0.1f,  0.1f, -0.1f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
            0.1f,  0.1f,  0.1f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            0.1f,  0.1f,  0.1f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            -0.1f,  0.1f,  0.1f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            -0.1f,  0.1f, -0.1f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f
        };
        return cVer;
    }
    unsigned int uiCUBGetVerticesSize();
    void CUBNormalVectorCalculation();
    void CUBDisplayNormalVectors();

	CCube();
    CCube(unsigned int id_global, unsigned int id_cube, glm::vec3 position, const char* vsFile, const char* fragFile, int texture_number);
    CCube(unsigned int id_global, unsigned int id_cube, glm::vec3 position, const char* vsFile, const char* fragFile, int texture_number, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, float transparency);
    ~CCube();

    void CUBFirstTimeSetVerticesPosition();

    void CUBChangeWorldPosition(glm::vec3 new_position);
    void CUBScaleEntitySize(GLfloat ratio);

    void CUBChangeHeight(GLfloat height);
    void CUBChangeLength(GLfloat length);
    void CUBChangeDepth(GLfloat depth);
};