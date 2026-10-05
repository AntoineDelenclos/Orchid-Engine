#pragma once
#include "CMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stb-master/stb_image.h>


unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class CModel {
public:
    //Model data
    std::vector<Texture> textures_loaded;	//Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<CMesh> meshes;
    std::string directory;
    bool gammaCorrection;
    //Entity values (shown and edited in the Models interface)
    std::string strMODName;
    std::string strMODPath;
    bool bMODActive;
    glm::vec3 vec3MODPosition;
    glm::vec3 vec3MODRotation; //Euler angles in degrees (applied in X, Y, Z order)
    float fMODScale;
    //Material values (mêmes défauts que CCube)
    glm::vec3 vec3MODAmbient = glm::vec3(1.0f);
    float fMODShininess = 0.25f;
    float fMODTransparency = 1.0f;
    CModel(std::string const& path, bool gamma = false);
    bool bMODIsLoaded() const;
    glm::mat4 mat4MODGetModelMatrix() const;
    void Draw(CShader& shader);
private:
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    CMesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};