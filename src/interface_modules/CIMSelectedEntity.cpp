#include "../../include/interface_modules/CIMSelectedEntity.h"

#include "imgui.h"
#include "../../include/interface_modules/CIMTextures.h"

//Display informations about selected entity : ID, Position X,Y,Z et texture pour l'instant
void CIMSelectedEntity::CIMSelectedEntityInterfaceModule(CEngine& engine, CEngineInterface& ui) {
    ImGui::Begin("Selected entity"); //Essayer de passer le nom de l'entité
    //Pour nos différentes entités cubes
    if (ui.siEGISelectedEntity_cube >= 0 && ui.siEGISelectedType == 0) {
        ImGui::Checkbox("Active", &engine.pcubENGCubeEntitiesList[ui.siEGISelectedEntity_cube].bENTActive);
        static char nameBuffer[128];
        strcpy_s(nameBuffer, sizeof(nameBuffer),
                 engine.pcubENGCubeEntitiesList[ui.siEGISelectedEntity_cube].strENTName.c_str());
        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            engine.pcubENGCubeEntitiesList[ui.siEGISelectedEntity_cube].strENTName = nameBuffer;
        }
        float Xc, Yc, Zc;
        int pos_cub = ui.siEGISelectedEntity_cube;
        Xc = engine.pcubENGCubeEntitiesList[pos_cub].vec3ENTWorldPosition.x;
        Yc = engine.pcubENGCubeEntitiesList[pos_cub].vec3ENTWorldPosition.y;
        Zc = engine.pcubENGCubeEntitiesList[pos_cub].vec3ENTWorldPosition.z;
        ImGui::SliderFloat("X", &ui.fEGINewX, -10.f, 10.f);
        ImGui::SliderFloat("Y", &ui.fEGINewY, -10.f, 10.f);
        ImGui::SliderFloat("Z", &ui.fEGINewZ, -10.f, 10.f);
        float difXc = ui.fEGINewX - Xc; float difYc = ui.fEGINewY - Yc; float difZc = ui.fEGINewZ - Zc;
        if (difXc != 0 || difYc != 0 || difZc != 0) {
            engine.pcubENGCubeEntitiesList[pos_cub].CUBChangeWorldPosition(glm::vec3(ui.fEGINewX, ui.fEGINewY, ui.fEGINewZ));
            ui.rdrEGIRender.RDRUpdateCubeBuffer(engine, engine.pcubENGCubeEntitiesList[pos_cub], engine.pcubENGCubeEntitiesList[pos_cub].uiCUBId);
        }
        ImGui::Text("Position : X = %.3f, Y = %.3f, Z = %.3f", Xc, Yc, Zc);
        ImGui::SliderFloat("Scale Ratio", &ui.gfEGINewRatio, 0.01f, 10.f);
        GLfloat ScaleRatio = engine.pcubENGCubeEntitiesList[pos_cub].gfCUBScaleRatio;
        GLfloat difScaleRatio = ui.gfEGINewRatio - ScaleRatio;
        if (difScaleRatio != 0) {
            engine.pcubENGCubeEntitiesList[pos_cub].CUBScaleEntitySize(ui.gfEGINewRatio);
            ui.rdrEGIRender.RDRUpdateCubeBuffer(engine, engine.pcubENGCubeEntitiesList[pos_cub], engine.pcubENGCubeEntitiesList[pos_cub].uiCUBId);
        }
        ImGui::SliderFloat("Length", &ui.gfEGINewCubeLength, 0.01f, 10.f);
        GLfloat CubeLength = engine.pcubENGCubeEntitiesList[pos_cub].gfCUBLength;
        GLfloat difCubeLength = ui.gfEGINewCubeLength - CubeLength;
        if (difCubeLength != 0) {
            engine.pcubENGCubeEntitiesList[pos_cub].CUBChangeLength(ui.gfEGINewCubeLength);
            ui.rdrEGIRender.RDRUpdateCubeBuffer(engine, engine.pcubENGCubeEntitiesList[pos_cub], engine.pcubENGCubeEntitiesList[pos_cub].uiCUBId);
        }
        glm::vec3 cubeRotation = engine.pcubENGCubeEntitiesList[pos_cub].vec3CUBRotation;
        if (ImGui::SliderFloat3("Rotation (deg)", (float*)&cubeRotation, -180.f, 180.f)) {
            engine.pcubENGCubeEntitiesList[pos_cub].CUBChangeRotation(cubeRotation);
            ui.rdrEGIRender.RDRUpdateCubeBuffer(engine, engine.pcubENGCubeEntitiesList[pos_cub], engine.pcubENGCubeEntitiesList[pos_cub].uiCUBId);
        }
        ImGui::Text("Texture :"); ImGui::SameLine(); //It's also the diffuse map
        if (ImGui::ImageButton((void*)(intptr_t)(engine.pcubENGCubeEntitiesList[pos_cub].uiENTTextureEngineNumber + 1), ImVec2(SIZE_TEXTURE_INTERFACE, SIZE_TEXTURE_INTERFACE))) {
            CIMTextures::CIMTexturesInterfaceModule(engine, ui);
            engine.pcubENGCubeEntitiesList[pos_cub].uiENTTextureEngineNumber = ui.iEGITextureNumber;
        }
        ImGui::Text("Specular map :"); ImGui::SameLine();
        if (ImGui::ImageButton((void*)(intptr_t)(engine.pcubENGCubeEntitiesList[pos_cub].uiCUBSpecularTextureEngineNumber + 1), ImVec2(SIZE_TEXTURE_INTERFACE, SIZE_TEXTURE_INTERFACE))) {
            CIMTextures::CIMTexturesInterfaceModule(engine, ui);
            std::cout << "actuel = " << engine.pcubENGCubeEntitiesList[pos_cub].uiCUBSpecularTextureEngineNumber << std::endl;
            engine.pcubENGCubeEntitiesList[pos_cub].uiCUBSpecularTextureEngineNumber = ui.iEGITextureNumber;
            std::cout << "nouveau = " << ui.iEGITextureNumber << std::endl;
        }
    }
    //Cas d'une Directional Light
    if (ui.siEGISelectedEntity_dir_light >= 0 && ui.siEGISelectedType == 1) {
        ImGui::Checkbox("Active", &engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].bENTActive);
        static char nameBuffer[128];
        strcpy_s(nameBuffer, sizeof(nameBuffer),
                 engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].strENTName.c_str());
        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].strENTName = nameBuffer;
        }
        unsigned int pos_lig = ui.siEGISelectedEntity_dir_light;
        float Xl, Yl, Zl; //Update the cube light position (only when it's needed)
        Xl = engine.pligENGDirectionalLightsList[pos_lig].vec3ENTWorldPosition.x;
        Yl = engine.pligENGDirectionalLightsList[pos_lig].vec3ENTWorldPosition.y;
        Zl = engine.pligENGDirectionalLightsList[pos_lig].vec3ENTWorldPosition.z;
        ImGui::SliderFloat("X", &ui.fEGINewX, -10.f, 10.f);
        ImGui::SliderFloat("Y", &ui.fEGINewY, -10.f, 10.f);
        ImGui::SliderFloat("Z", &ui.fEGINewZ, -10.f, 10.f);
        float difXl = ui.fEGINewX - Xl; float difYl = ui.fEGINewY - Yl; float difZl = ui.fEGINewZ - Zl;
        if (difXl != 0 || difYl != 0 || difZl != 0) {
            engine.pligENGDirectionalLightsList[pos_lig].LIGChangeWorldPosition(glm::vec3(ui.fEGINewX, ui.fEGINewY, ui.fEGINewZ));
            ui.rdrEGIRender.RDRUpdateLightBuffer(engine, engine.pligENGDirectionalLightsList[pos_lig], engine.pligENGDirectionalLightsList[pos_lig].uiLIGId);
        }
        ImGui::Text("Position : X = %.3f, Y = %.3f, Z = %.3f", Xl, Yl, Zl);
        ImGui::SliderFloat("Scale Ratio", &ui.gfEGINewRatio, 0.01f, 10.f); //Update the scale ratio of the light cube (when update is needed)
        GLfloat ScaleRatio = engine.pligENGDirectionalLightsList[pos_lig].gfLIGScaleRatio;
        GLfloat difScaleRatio = ui.gfEGINewRatio - ScaleRatio;
        if (difScaleRatio != 0) {
            engine.pligENGDirectionalLightsList[pos_lig].LIGScaleEntitySize(ui.gfEGINewRatio);
            ui.rdrEGIRender.RDRUpdateLightBuffer(engine, engine.pligENGDirectionalLightsList[pos_lig], engine.pligENGDirectionalLightsList[pos_lig].uiLIGId);
        }
        ImGui::ColorEdit3("Light Color", engine.pligENGDirectionalLightsList[pos_lig].gfLIGColorLight); //Update the light's color and settings
        float Xd, Yd, Zd; //Update the light's direction
        Xd = engine.pligENGDirectionalLightsList[pos_lig].vec3LIGDirection.x;
        Yd = engine.pligENGDirectionalLightsList[pos_lig].vec3LIGDirection.y;
        Zd = engine.pligENGDirectionalLightsList[pos_lig].vec3LIGDirection.z;
        ImGui::SliderFloat("X Direction", &ui.fEGINewDirectionX, -10.f, 10.f);
        ImGui::SliderFloat("Y Direction", &ui.fEGINewDirectionY, -10.f, 10.f);
        ImGui::SliderFloat("Z Direction", &ui.fEGINewDirectionZ, -10.f, 10.f);
        float difXd = ui.fEGINewDirectionX - Xd; float difYd = ui.fEGINewDirectionY - Yd; float difZd = ui.fEGINewDirectionZ - Zd;
        if (difXd != 0 || difYd != 0 || difZd != 0) {
            engine.pligENGDirectionalLightsList[pos_lig].LIGChangeLightDirection(glm::vec3(ui.fEGINewDirectionX, ui.fEGINewDirectionY, ui.fEGINewDirectionZ));
        }
        ImGui::SliderFloat("Ambient Intensity", &engine.pligENGDirectionalLightsList[pos_lig].gfLIGAmbientIntensity, 0.f, 1.f);
        ImGui::SliderFloat("Diffuse Strength", &engine.pligENGDirectionalLightsList[pos_lig].gfLIGDiffuseStrength, 0.f, 1.f);
        ImGui::SliderFloat("Specular Strength", &engine.pligENGDirectionalLightsList[pos_lig].gfLIGSpecularStrength, 0.f, 256.f);
    }
    //Cas d'une Point Light
    if (ui.siEGISelectedEntity_point_light >= 0 && ui.siEGISelectedType == 2) {
        ImGui::Checkbox("Active", &engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].bENTActive);
        static char nameBuffer[128];
        strcpy_s(nameBuffer, sizeof(nameBuffer),
                 engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].strENTName.c_str());
        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].strENTName = nameBuffer;
        }
        unsigned int pos_lig = ui.siEGISelectedEntity_point_light;
        float Xl, Yl, Zl; //Update the cube light position (only when it's needed)
        Xl = engine.pligENGPointLightsList[pos_lig].vec3ENTWorldPosition.x;
        Yl = engine.pligENGPointLightsList[pos_lig].vec3ENTWorldPosition.y;
        Zl = engine.pligENGPointLightsList[pos_lig].vec3ENTWorldPosition.z;
        ImGui::SliderFloat("X", &ui.fEGINewX, -10.f, 10.f);
        ImGui::SliderFloat("Y", &ui.fEGINewY, -10.f, 10.f);
        ImGui::SliderFloat("Z", &ui.fEGINewZ, -10.f, 10.f);
        float difXl = ui.fEGINewX - Xl; float difYl = ui.fEGINewY - Yl; float difZl = ui.fEGINewZ - Zl;
        if (difXl != 0 || difYl != 0 || difZl != 0) {
            engine.pligENGPointLightsList[pos_lig].LIGChangeWorldPosition(glm::vec3(ui.fEGINewX, ui.fEGINewY, ui.fEGINewZ));
            ui.rdrEGIRender.RDRUpdateLightBuffer(engine, engine.pligENGPointLightsList[pos_lig], engine.pligENGPointLightsList[pos_lig].uiLIGId);
        }
        ImGui::Text("Position : X = %.3f, Y = %.3f, Z = %.3f", Xl, Yl, Zl);
        ImGui::SliderFloat("Scale Ratio", &ui.gfEGINewRatio, 0.01f, 10.f); //Update the scale ratio of the light cube (when update is needed)
        GLfloat ScaleRatio = engine.pligENGPointLightsList[pos_lig].gfLIGScaleRatio;
        GLfloat difScaleRatio = ui.gfEGINewRatio - ScaleRatio;
        if (difScaleRatio != 0) {
            engine.pligENGPointLightsList[pos_lig].LIGScaleEntitySize(ui.gfEGINewRatio);
            ui.rdrEGIRender.RDRUpdateLightBuffer(engine, engine.pligENGPointLightsList[pos_lig], engine.pligENGPointLightsList[pos_lig].uiLIGId);
        }
        ImGui::ColorEdit3("Light Color", engine.pligENGPointLightsList[pos_lig].gfLIGColorLight); //Update the light's color and settings
        float KC = engine.pligENGPointLightsList[pos_lig].fLIGPointKC;
        float KL = engine.pligENGPointLightsList[pos_lig].fLIGPointKL;
        float KQ = engine.pligENGPointLightsList[pos_lig].fLIGPointKQ;
        ImGui::SliderFloat("KC Constant", &ui.fEGINewKC, 0.f, 1.f);
        ImGui::SliderFloat("KL Constant", &ui.fEGINewKL, 0.f, 1.f);
        ImGui::SliderFloat("KQ Constant", &ui.fEGINewKQ, 0.f, 1.f);
        float difKC = ui.fEGINewKC - KC; float difKL = ui.fEGINewKL - KL; float difKQ = ui.fEGINewKQ - KQ;
        if (difKC != 0 || difKL != 0 || difKQ != 0) {
            engine.pligENGPointLightsList[pos_lig].LIGChangeKConstants(ui.fEGINewKC, ui.fEGINewKL, ui.fEGINewKQ);
        }
        ImGui::SliderFloat("Ambient Intensity", &engine.pligENGPointLightsList[pos_lig].gfLIGAmbientIntensity, 0.f, 1.f);
        ImGui::SliderFloat("Diffuse Strength", &engine.pligENGPointLightsList[pos_lig].gfLIGDiffuseStrength, 0.f, 1.f);
        ImGui::SliderFloat("Specular Strength", &engine.pligENGPointLightsList[pos_lig].gfLIGSpecularStrength, 0.f, 256.f);
    }
    //Cas d'une Spotlight
    if (ui.siEGISelectedEntity_spot_light >= 0 && ui.siEGISelectedType == 3) {
        ImGui::Checkbox("Active", &engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].bENTActive);
        static char nameBuffer[128];
        strcpy_s(nameBuffer, sizeof(nameBuffer),
                 engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].strENTName.c_str());
        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].strENTName = nameBuffer;
        }
        unsigned int pos_lig = ui.siEGISelectedEntity_spot_light;
        float Xl, Yl, Zl; //Update the cube light position (only when it's needed)
        Xl = engine.pligENGSpotLightsList[pos_lig].vec3ENTWorldPosition.x;
        Yl = engine.pligENGSpotLightsList[pos_lig].vec3ENTWorldPosition.y;
        Zl = engine.pligENGSpotLightsList[pos_lig].vec3ENTWorldPosition.z;
        ImGui::SliderFloat("X", &ui.fEGINewX, -10.f, 10.f);
        ImGui::SliderFloat("Y", &ui.fEGINewY, -10.f, 10.f);
        ImGui::SliderFloat("Z", &ui.fEGINewZ, -10.f, 10.f);
        float difXl = ui.fEGINewX - Xl; float difYl = ui.fEGINewY - Yl; float difZl = ui.fEGINewZ - Zl;
        if (difXl != 0 || difYl != 0 || difZl != 0) {
            engine.pligENGSpotLightsList[pos_lig].LIGChangeWorldPosition(glm::vec3(ui.fEGINewX, ui.fEGINewY, ui.fEGINewZ));
            ui.rdrEGIRender.RDRUpdateLightBuffer(engine, engine.pligENGSpotLightsList[pos_lig], engine.pligENGSpotLightsList[pos_lig].uiLIGId);
        }
        ImGui::Text("Position : X = %.3f, Y = %.3f, Z = %.3f", Xl, Yl, Zl);
        ImGui::SliderFloat("Scale Ratio", &ui.gfEGINewRatio, 0.01f, 10.f); //Update the scale ratio of the light cube (when update is needed)
        GLfloat ScaleRatio = engine.pligENGSpotLightsList[pos_lig].gfLIGScaleRatio;
        GLfloat difScaleRatio = ui.gfEGINewRatio - ScaleRatio;
        if (difScaleRatio != 0) {
            engine.pligENGSpotLightsList[pos_lig].LIGScaleEntitySize(ui.gfEGINewRatio);
            ui.rdrEGIRender.RDRUpdateLightBuffer(engine, engine.pligENGSpotLightsList[pos_lig], engine.pligENGSpotLightsList[pos_lig].uiLIGId);
        }
        ImGui::ColorEdit3("Light Color", engine.pligENGSpotLightsList[pos_lig].gfLIGColorLight); //Update the light's color and settings
        float Xd, Yd, Zd; //Update the light's direction
        Xd = engine.pligENGSpotLightsList[pos_lig].vec3LIGDirection.x;
        Yd = engine.pligENGSpotLightsList[pos_lig].vec3LIGDirection.y;
        Zd = engine.pligENGSpotLightsList[pos_lig].vec3LIGDirection.z;
        ImGui::SliderFloat("X Direction", &ui.fEGINewDirectionX, -10.f, 10.f);
        ImGui::SliderFloat("Y Direction", &ui.fEGINewDirectionY, -10.f, 10.f);
        ImGui::SliderFloat("Z Direction", &ui.fEGINewDirectionZ, -10.f, 10.f);
        float difXd = ui.fEGINewDirectionX - Xd; float difYd = ui.fEGINewDirectionY - Yd; float difZd = ui.fEGINewDirectionZ - Zd;
        if (difXd != 0 || difYd != 0 || difZd != 0) {
            engine.pligENGSpotLightsList[pos_lig].LIGChangeLightDirection(glm::vec3(ui.fEGINewDirectionX, ui.fEGINewDirectionY, ui.fEGINewDirectionZ));
        }
        ImGui::SliderFloat("Inner CutOff Angle", &engine.pligENGSpotLightsList[pos_lig].fLIGInnerCutOff, 0.f, 1.f);
        ImGui::SliderFloat("Outer CutOff Angle", &engine.pligENGSpotLightsList[pos_lig].fLIGOuterCutOff, 0.f, 1.f);
        ImGui::SliderFloat("Ambient Intensity", &engine.pligENGSpotLightsList[pos_lig].gfLIGAmbientIntensity, 0.f, 1.f);
        ImGui::SliderFloat("Diffuse Strength", &engine.pligENGSpotLightsList[pos_lig].gfLIGDiffuseStrength, 0.f, 1.f);
        ImGui::SliderFloat("Specular Strength", &engine.pligENGSpotLightsList[pos_lig].gfLIGSpecularStrength, 0.f, 256.f);
    }
    //Cas d'un modèle 3D custom (chargé depuis la fenêtre "Models")
    if (ui.siEGISelectedModel >= 0 && ui.siEGISelectedModel < (int)engine.modENGModels.size() && ui.siEGISelectedType == 4) {
        CModel& model = engine.modENGModels[ui.siEGISelectedModel];
        ImGui::Checkbox("Active", &model.bMODActive);
        char nameBuffer[128];
        strcpy_s(nameBuffer, sizeof(nameBuffer), model.strMODName.c_str());
        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            model.strMODName = nameBuffer;
        }
        ImGui::Text("File : %s", model.strMODPath.c_str());
        ImGui::Text("Meshes : %d", (int)model.meshes.size());
        ImGui::SliderFloat3("Position", (float*)&model.vec3MODPosition, -10.f, 10.f);
        ImGui::SliderFloat3("Rotation (deg)", (float*)&model.vec3MODRotation, -180.f, 180.f);
        ImGui::SliderFloat("Scale", &model.fMODScale, 0.01f, 10.f);
        if (ImGui::SmallButton("Reset transform")) {
            model.vec3MODPosition = glm::vec3(0.0f);
            model.vec3MODRotation = glm::vec3(0.0f);
            model.fMODScale = 1.0f;
        }
        ImGui::SliderFloat3("Ambient", (float*)&model.vec3MODAmbient, 0.f, 1.f);
        ImGui::SliderFloat("Shininess", &model.fMODShininess, 0.f, 1.f);
        ImGui::SliderFloat("Transparency", &model.fMODTransparency, 0.f, 1.f);
    }
    ImGui::End();
}
