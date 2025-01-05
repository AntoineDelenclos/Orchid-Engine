#include "../../include/entities/CCube.h"

/// Constructors & Destructors ///
CCube::CCube() {
	enumENTType = entity;
	uiENTId = 0;
	strENTName = "##";
	vec3ENTWorldPosition = glm::vec3(0.0f);
	pcENTVertexShaderName = NULL;
	pcENTFragmentShaderName = NULL;
	pgfENTVertices = NULL;
	uiENTVerticesSize = 0;
}

CCube::CCube(unsigned int id_global, unsigned int id_cube, glm::vec3 position, const char* vsFile, const char* fragFile, int texture_number) {
	enumENTType = cube;
	uiENTId = id_global;
	uiCUBId = id_cube;
	bENTActive = true;
	strENTName = "Cube " + std::to_string(id_cube);
	GLfloat* temp_vertices = nullptr;
	temp_vertices = new (GLfloat[288]);
	for (int i = 0; i < 288; i++) {
		temp_vertices[i] = cubeVertices()[i];
	}
	pgfCUBVertices = temp_vertices;
	uiCUBVerticesSize = 288;
	gfCUBScaleRatio = 1.f;
	vec3ENTWorldPosition = position;
	pcENTVertexShaderName = vsFile;
	pcENTFragmentShaderName = fragFile;
	uiENTTextureEngineNumber = texture_number;
	uiCUBSpecularTextureEngineNumber = 5;
	//Material values
	vec3CUBAmbient = glm::vec3(1.0f, 1.0f, 1.0f);
	vec3CUBDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	vec3CUBSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
	fCUBShininess = 0.25f;
	fCUBTransparency = 1.0f;
}

CCube::CCube(unsigned int id_global, unsigned int id_cube, glm::vec3 position, const char* vsFile, const char* fragFile, int texture_number, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, float transparency) {
	enumENTType = cube;
	uiENTId = id_global;
	uiCUBId = id_cube;
	bENTActive = true;
	GLfloat* temp_vertices = nullptr;
	strENTName = "Cube " + std::to_string(id_cube);
	temp_vertices = new (GLfloat[288]);
	for (int i = 0; i < 288; i++) {
		temp_vertices[i] = cubeVertices()[i];
	}
	pgfCUBVertices = temp_vertices;
	uiCUBVerticesSize = 288;
	gfCUBScaleRatio = 1.f;
	vec3ENTWorldPosition = position;
	pcENTVertexShaderName = vsFile;
	pcENTFragmentShaderName = fragFile;
	uiENTTextureEngineNumber = texture_number;
	uiCUBSpecularTextureEngineNumber = 5;
	//Material values
	vec3CUBAmbient = ambient;
	vec3CUBDiffuse = diffuse;
	vec3CUBSpecular = specular;
	fCUBShininess = shininess;
	fCUBTransparency = transparency;
}

CCube::~CCube() {

}

/// Getters & Setters ///
unsigned int CCube::uiCUBGetVerticesSize() {
	return uiCUBVerticesSize;
}

void CCube::CUBNormalVectorCalculation() { //Utile pour le calcul de la lumière
	//for (int)
}

void CCube::CUBDisplayNormalVectors() {

}

void CCube::CUBFirstTimeSetVerticesPosition() {
	for (int sommet = 0; sommet < 36; sommet++) {
		for (int axe = 0; axe < 3; axe++) {
			pgfCUBVertices[8 * sommet + axe] += vec3ENTWorldPosition[axe] * gfCUBScaleRatio;
		}
	}
}

//Déplace le cube en temps réel
void CCube::CUBChangeWorldPosition(glm::vec3 new_position) {
	for (int sommet = 0; sommet < 36; sommet++) {
		for (int axe = 0; axe < 3; axe++) {
			pgfCUBVertices[8 * sommet + axe] += (new_position[axe] - vec3ENTWorldPosition[axe]);
		}
	}
	vec3ENTWorldPosition = new_position;
}

//Scale la taille de l'entité en temps réel
void CCube::CUBScaleEntitySize(GLfloat ratio) {
	for (int sommet = 0; sommet < 36; sommet++) {
		for (int axe = 0; axe < 3; axe++) {
			pgfCUBVertices[8 * sommet + axe] = cubeVertices()[8 * sommet + axe];
			pgfCUBVertices[8 * sommet + axe] *= ratio;
			pgfCUBVertices[8 * sommet + axe] += vec3ENTWorldPosition[axe];
		}
	}
	gfCUBScaleRatio = ratio;
}

//Change the length of the cube entity (faces 1,3,4,6)
void CCube::CUBChangeLength(GLfloat length) {
	for (int summit = 0; summit < 12; summit++) { //As the order of faces in cubeVertices are 4,1,2,5,6,3 we just need the 2 first and 2 last faces (12*2 summits)
		for (int axis = 0; axis < 3; axis++) {
			pgfCUBVertices[8 * summit + axis] = cubeVertices()[8 * summit + axis];
			pgfCUBVertices[8 * summit + axis] *= gfCUBScaleRatio;
			pgfCUBVertices[8 * summit + axis] += vec3ENTWorldPosition[axis];
		}
	}
	for (int summit = 24; summit < 36; summit++) { //We can simplify the for loop
		for (int axis = 0; axis < 3; axis++) {
			pgfCUBVertices[8 * summit + axis] = cubeVertices()[8 * summit + axis];
			pgfCUBVertices[8 * summit + axis] *= gfCUBScaleRatio;
			pgfCUBVertices[8 * summit + axis] += vec3ENTWorldPosition[axis];
		}
	}
	gfCUBLength = length;
}
