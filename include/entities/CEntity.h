#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread> //Utile depuis C++11 pour utiliser sleep_for() ou sleep_until()
#include <cmath>
#include <vector>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define GLEW_STATIC //car on lie via gl32s.lib
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Il faudra rajouter au fur et a mesure (player, model, et peut etre penser a differencier les types de lumiere)
enum entity_type_enum { cube, polyhedron, dir_light, point_light, spot_light, camera, entity, face };

class CEntity {
public:
	entity_type_enum enumENTType;
	unsigned int uiENTId;
    std::string strENTName;
	//On va translate de cette position apres l'avoir dessine en (0,0,0) pour eviter des soucis avec les transformations matricielles
	glm::vec3 vec3ENTWorldPosition;
    bool bENTActive; //If an entity is inactive : no render, no consequences to the surroundings.

	const char* pcENTVertexShaderName; //Nom du fichier, par exemple : "core.vert"
	const char* pcENTFragmentShaderName;
    GLfloat* pgfENTVertices;
    unsigned int uiENTVerticesSize; 

    //On peut stocker le numero de la texture dans l'ensemble des textures ? Et si on fait une liste selectionnable si des textures
    //ca devrait fonctionner
    unsigned int uiENTTextureEngineNumber;
    //Peut etre stocker l'adresse du VAO ou bien sa position dans le VAO/VBO (vbo plutot) et ensuite modifier le vbo avec glBufferSubData par exemple
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

	CEntity();
    CEntity(entity_type_enum type, unsigned int id, glm::vec3 position, const char* vsFile, const char* fragFile);
	CEntity(entity_type_enum type, unsigned int id, glm::vec3 position, const char* vsFile, const char* fragFile, GLfloat* vertices);
    //Seul constructeur vraiment utilise (notamment dans CEngineInterface)
    CEntity(entity_type_enum type, unsigned int id, glm::vec3 position, const char* vsFile, const char* fragFile, int texture_number);
    CEntity(entity_type_enum type, unsigned int id, glm::vec3 position, const char* vsFile, const char* fragFile, int texture_number, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, float transparency);
    CEntity(CEntity* entity); //Constructeur de recopie
	//A completer
	~CEntity();
    //Getters & Setters
    unsigned int uiENTGetVerticesSize();


    void ENTNormalVectorCalculation();

	void ENTChangeWorldPosition(glm::vec3 new_position);
    void ENTScaleEntitySize(GLfloat ratio);

	void ENTDisplayNormalVectors();
};