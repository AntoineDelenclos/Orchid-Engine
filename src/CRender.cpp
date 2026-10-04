#include "../include/CRender.h"

CRender::CRender() {

}
CRender::~CRender() {

}

void CRender::RDRCreateMandatoryForCube(CEngine& engine, CCube& cube_entity, int number) {
	//The engine list keeps its own copy of the entity (and so owns the CPU vertices, which must stay alive for later edits)
	engine.ENGAddCubeEntity(cube_entity);

	glGenVertexArrays(1, &engine.puiENGVAOCubesEngine[number]);
	glGenBuffers(1, &engine.puiENGVBOCubesEngine[number]);
	glBindVertexArray(engine.puiENGVAOCubesEngine[number]);
	glBindBuffer(GL_ARRAY_BUFFER, engine.puiENGVBOCubesEngine[number]);
	glBufferData(GL_ARRAY_BUFFER, cube_entity.uiCUBVerticesSize * sizeof(GLfloat), cube_entity.pgfCUBVertices, GL_STATIC_DRAW);
	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	//Texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//Logique : 1 pour l'id d'attribution, 2 pour le nombre d'infos par point (cf vertices), 8* car maintenant 8 infos par vertices par sommet
	// et 3* car le 1er élément de texture coords commence au 3eme
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); //Unbind VAO
}

//Re-upload the vertices of an already created cube (position, scale, ... changed)
void CRender::RDRUpdateCubeBuffer(CEngine& engine, CCube& cube_entity, int number) {
	if (cube_entity.pgfCUBVertices == nullptr) return;
	glBindBuffer(GL_ARRAY_BUFFER, engine.puiENGVBOCubesEngine[number]);
	glBufferData(GL_ARRAY_BUFFER, cube_entity.uiCUBVerticesSize * sizeof(GLfloat), cube_entity.pgfCUBVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CRender::RDRCreateMandatoryForLight(CEngine& engine, CLight& light_entity, int number) {
	engine.ENGAddLightEntity(light_entity);

	switch (light_entity.enumLIGType) {
	case(directional):
		glGenVertexArrays(1, &engine.puiENGVAODirectionalLightsEngine[number]);
		glGenBuffers(1, &engine.puiENGVBODirectionalLightsEngine[number]);
		glBindVertexArray(engine.puiENGVAODirectionalLightsEngine[number]);
		glBindBuffer(GL_ARRAY_BUFFER, engine.puiENGVBODirectionalLightsEngine[number]);
		break;
	case(point):
		glGenVertexArrays(1, &engine.puiENGVAOPointLightsEngine[number]);
		glGenBuffers(1, &engine.puiENGVBOPointLightsEngine[number]);
		glBindVertexArray(engine.puiENGVAOPointLightsEngine[number]);
		glBindBuffer(GL_ARRAY_BUFFER, engine.puiENGVBOPointLightsEngine[number]);
		break;
	case(spot):
		glGenVertexArrays(1, &engine.puiENGVAOSpotLightsEngine[number]);
		glGenBuffers(1, &engine.puiENGVBOSpotLightsEngine[number]);
		glBindVertexArray(engine.puiENGVAOSpotLightsEngine[number]);
		glBindBuffer(GL_ARRAY_BUFFER, engine.puiENGVBOSpotLightsEngine[number]);
		break;
	}
	glBufferData(GL_ARRAY_BUFFER, light_entity.uiLIGVerticesSize * sizeof(GLfloat), light_entity.pgfLIGVertices, GL_STATIC_DRAW);
	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); //Unbind VAO
}

//Re-upload the vertices of an already created light (position, scale, ... changed)
void CRender::RDRUpdateLightBuffer(CEngine& engine, CLight& light_entity, int number) {
	if (light_entity.pgfLIGVertices == nullptr) return;
	GLuint vbo = 0;
	switch (light_entity.enumLIGType) {
	case(directional): vbo = engine.puiENGVBODirectionalLightsEngine[number]; break;
	case(point):       vbo = engine.puiENGVBOPointLightsEngine[number]; break;
	case(spot):        vbo = engine.puiENGVBOSpotLightsEngine[number]; break;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, light_entity.uiLIGVerticesSize * sizeof(GLfloat), light_entity.pgfLIGVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CRender::RDRCubeVerticesAndTextureRendering(CEngine &engine, CCube &cube_entity, int number) {
    glBindVertexArray(engine.puiENGVAOCubesEngine[number]);
    glDrawArrays(GL_TRIANGLES, 0, cube_entity.uiCUBVerticesSize / 8);
    glBindVertexArray(0);
}

//Est-ce qu'il vaudrait mieux pas mettre le contenu actuel de rdrlightrendering dans le render classique ? car ca dÃ©pend du matÃ©riau et non de la lumiere
void CRender::RDRLightRenderingOnCube(CEngine& engine, CCube& cube_entity) {
	engine.shaENGCoreShader.SHAUse(); //On utilise le shader avant de passer les uniform car uniform -> dernier shader actif
	engine.shaENGCoreShader.SHASetMaterial(cube_entity.vec3CUBAmbient, cube_entity.fCUBShininess, cube_entity.fCUBTransparency);
	engine.shaENGCoreShader.SHABindTexture("material.diffuseTexture", engine.ptexENGAllTextures[cube_entity.uiENTTextureEngineNumber].guiTEXGetNumeroTexture(), 0);
	engine.shaENGCoreShader.SHABindTexture("material.specularTexture", engine.ptexENGAllTextures[cube_entity.uiCUBSpecularTextureEngineNumber].guiTEXGetNumeroTexture(), 1);
	glActiveTexture(GL_TEXTURE0);
}

void CRender::RDRLightVerticesAndTextureRendering(CEngine& engine, CLight& light_entity, int number) {
	GLint lightColorUniformLocation = glGetUniformLocation(engine.shaENGLightShader.Program, "ownLightColor");
	engine.shaENGLightShader.SHAUse();
	glUniform3f(lightColorUniformLocation, light_entity.gfLIGColorLight[0], light_entity.gfLIGColorLight[1], light_entity.gfLIGColorLight[2]);
	//glUniform3f(lightColorUniformLocation, light_entity.vec3LIGColorLight.x, light_entity.vec3LIGColorLight.y, light_entity.vec3LIGColorLight.z);
	//On set les shaders avant de draw
	//std::cout << light_entity.uiLIGId << std::endl;
	glBindTexture(GL_TEXTURE_2D, engine.ptexENGAllTextures[light_entity.uiENTTextureEngineNumber].guiTEXGetNumeroTexture());
	switch (light_entity.enumLIGType) {
	case(directional):
		glBindVertexArray(engine.puiENGVAODirectionalLightsEngine[number]);
		break;
	case(point):
		glBindVertexArray(engine.puiENGVAOPointLightsEngine[number]);
		break;
	case(spot):
		glBindVertexArray(engine.puiENGVAOSpotLightsEngine[number]);
		break;
	}
	glDrawArrays(GL_TRIANGLES, 0, light_entity.uiLIGVerticesSize / 5); //On divise la taille par le nombre d'infos par sommet
	glBindVertexArray(0);
}

void CRender::RDRRenderingCubes(CEngine &engine) {
	for (int boucle_cube = 0; boucle_cube < engine.iENGGetNumberOfEntitiesTypeX(cube); boucle_cube++) {
		if (engine.pcubENGCubeEntitiesList[boucle_cube].bENTActive) { //If the cube isn't activated, now needs to calculate light & to render it
			RDRLightRenderingOnCube(engine, engine.pcubENGCubeEntitiesList[boucle_cube]);
			RDRCubeVerticesAndTextureRendering(engine, engine.pcubENGCubeEntitiesList[boucle_cube], boucle_cube);
		}
	}
}

void CRender::RDRRenderingLightCubes(CEngine& engine) {
	for (int boucle_dir_light = 0; boucle_dir_light < engine.iENGGetNumberOfEntitiesTypeX(dir_light); boucle_dir_light++) {
		if (engine.pligENGDirectionalLightsList[boucle_dir_light].bENTActive) {
			RDRLightVerticesAndTextureRendering(engine, engine.pligENGDirectionalLightsList[boucle_dir_light], boucle_dir_light);
		}
	}
	for (int boucle_point_light = 0; boucle_point_light < engine.iENGGetNumberOfEntitiesTypeX(point_light); boucle_point_light++) {
		if (engine.pligENGPointLightsList[boucle_point_light].bENTActive) {
			RDRLightVerticesAndTextureRendering(engine, engine.pligENGPointLightsList[boucle_point_light], boucle_point_light);
		}
	}
	for (int boucle_spot_light = 0; boucle_spot_light < engine.iENGGetNumberOfEntitiesTypeX(spot_light); boucle_spot_light++) {
		if (engine.pligENGSpotLightsList[boucle_spot_light].bENTActive) {
			RDRLightVerticesAndTextureRendering(engine, engine.pligENGSpotLightsList[boucle_spot_light], boucle_spot_light);
		}
	}
}