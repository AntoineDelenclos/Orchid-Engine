#include "../../include/interface_modules/CIMNewEntity.h"

#include "imgui.h"

void CIMNewEntity::CIMNewEntityInterfaceModule(CEngine& engine, CEngineInterface& ui) {
    ImGui::Begin("New Entity");
    ImGui::NextColumn();
    static int entityTypeCombo;
    const char* entityItems[] = { "Cube", "Directional Light", "Point Light", "SpotLight" };
    ImGui::Combo("Entity type", &entityTypeCombo, "Cube\0" "Directional Light\0" "Point Light\0" "SpotLight\0");
    //Sliders for XYZ Axis position of the new entity
    const char* axisSliders[] = { "X", "Y", "Z" };
    for (int boucle_axe = 0; boucle_axe < 3; boucle_axe++) {
        std::string axisText = axisSliders[boucle_axe];
        axisText += " Axis";
        ImGui::SliderFloat(axisText.c_str(), &ui.pgfEGINewEntityXYZPos[boucle_axe], -10.0f, 10.0f); //On peut mettre -1000 1000
        ImGui::SameLine();
        std::string axisRound = axisSliders[boucle_axe];
        axisRound += " Round value";
        if (ImGui::SmallButton(axisRound.c_str())) {
            ui.pgfEGINewEntityXYZPos[boucle_axe] = round(ui.pgfEGINewEntityXYZPos[boucle_axe]);
        }
        ImGui::NewLine();
        int button_values[6] = { -100,-10,-1,1,10,100 };
        for (int boucle_button = 0; boucle_button < 6; boucle_button++) {
            ImGui::SameLine();
            std::string buttonTextValue = std::to_string(button_values[boucle_button]) + " ";
            buttonTextValue += axisSliders[boucle_axe];
            if (ImGui::SmallButton(buttonTextValue.c_str())) {
                ui.pgfEGINewEntityXYZPos[boucle_axe] += button_values[boucle_button];
            }
        }
    }
    if (ImGui::SmallButton("Current view position")) {
        ui.pgfEGINewEntityXYZPos[0] = engine.inpENGInputs.camINPChosenCamera.vec3CAMCameraPosition.x;
        ui.pgfEGINewEntityXYZPos[1] = engine.inpENGInputs.camINPChosenCamera.vec3CAMCameraPosition.y;
        ui.pgfEGINewEntityXYZPos[2] = engine.inpENGInputs.camINPChosenCamera.vec3CAMCameraPosition.z;
    }
    ImGui::SliderFloat("Scale ratio", &ui.gfEGINewEntityScaleRatio, 0.0f, 100.0f);
    //Entity's material values
    if (entityTypeCombo == 0) {
        ImGui::SliderFloat3("Cube's ambient", (float*)&ui.vec3EGINewEntityAmbient, 0.0f, 1.0f);
        ImGui::SliderFloat3("Cube's diffuse", (float*)&ui.vec3EGINewEntityDiffuse, 0.0f, 1.0f);
        ImGui::SliderFloat3("Cube's specular", (float*)&ui.vec3EGINewEntitySpecular, 0.0f, 1.0f);
        ImGui::SliderFloat("Cube's shininess", &ui.fEGINewEntityShininess, 0.0f, 1.0f);
        ImGui::SliderFloat("Cube's transparency", &ui.fEGINewEntityTransparency, 0.0f, 1.0f);
    }
    //If the user wants to create a new directional light
    if (entityTypeCombo == 1) { 
        ImGui::ColorEdit3("Light's color", ui.pgfEGINewLightColor);
        ImGui::SliderFloat("Direction X", &ui.gfEGINewLightDirectionX, -10.f, 10.f);
        ImGui::SliderFloat("Direction Y", &ui.gfEGINewLightDirectionY, -10.f, 10.f);
        ImGui::SliderFloat("Direction Z", &ui.gfEGINewLightDirectionZ, -10.f, 10.f);
        ImGui::SliderFloat("Ambient Intensity", &ui.gfEGINewLightAmbientIntensity, 0.f, 1.f);
        ImGui::SliderFloat("Diffuse Strength", &ui.gfEGINewLightDiffuseStrength, 0.f, 1.f);
        ImGui::SliderFloat("Specular Strength", &ui.gfEGINewLightSpecularStrength, 0.f, 256.f);
    }
    //If the user wants to create a new point light
    if (entityTypeCombo == 2) {
        ImGui::ColorEdit3("Light's color", ui.pgfEGINewLightColor);
        ImGui::SliderFloat("KC", &ui.fEGINewLightKC, 0.f, 1.f);
        ImGui::SliderFloat("KL", &ui.fEGINewLightKL, 0.f, 1.f);
        ImGui::SliderFloat("KQ", &ui.fEGINewLightKQ, 0.f, 1.f);
        ImGui::SliderFloat("Ambient Intensity", &ui.gfEGINewLightAmbientIntensity, 0.f, 1.f);
        ImGui::SliderFloat("Diffuse Strength", &ui.gfEGINewLightDiffuseStrength, 0.f, 1.f);
        ImGui::SliderFloat("Specular Strength", &ui.gfEGINewLightSpecularStrength, 0.f, 256.f);
    }
    if (entityTypeCombo == 3) {
        ImGui::ColorEdit3("Light's color", ui.pgfEGINewLightColor);
        ImGui::SliderFloat("Direction X", &ui.gfEGINewLightDirectionX, -10.f, 10.f);
        ImGui::SliderFloat("Direction Y", &ui.gfEGINewLightDirectionY, -10.f, 10.f);
        ImGui::SliderFloat("Direction Z", &ui.gfEGINewLightDirectionZ, -10.f, 10.f);
        ImGui::SliderFloat("Inner CutOff", &ui.fEGINewLightInnerCutOff, 0.f, 1.f);
        ImGui::SliderFloat("Outer CutOff", &ui.fEGINewLightOuterCutOff, 0.f, 1.f);
        ImGui::SliderFloat("Ambient Intensity", &ui.gfEGINewLightAmbientIntensity, 0.f, 1.f);
        ImGui::SliderFloat("Diffuse Strength", &ui.gfEGINewLightDiffuseStrength, 0.f, 1.f);
        ImGui::SliderFloat("Specular Strength", &ui.gfEGINewLightSpecularStrength, 0.f, 256.f);
    }
    if (ImGui::SmallButton("Create entity")) {
        //Create a new entity with the set parameters and reset values to default ones
        entity_type_enum newEntityType;
        glm::vec3 newEntityWorldPosition(ui.pgfEGINewEntityXYZPos[0], ui.pgfEGINewEntityXYZPos[1], ui.pgfEGINewEntityXYZPos[2]);
        unsigned int newEntityGlobalId = engine.uiENGGetNextFreeGlobalID();
        if (entityTypeCombo == 0) {
            newEntityType = cube;
            unsigned int newEntityTypeId = engine.uiENGGetNextFreeEntityID(newEntityType);
            CCube newCube = CCube(newEntityGlobalId, newEntityTypeId, newEntityWorldPosition, "../shaders/core.vert", "../shaders/core.frag", ui.iEGITextureNumber, ui.vec3EGINewEntityAmbient, ui.vec3EGINewEntityDiffuse, ui.vec3EGINewEntitySpecular, ui.fEGINewEntityShininess, ui.fEGINewEntityTransparency);
            newCube.CUBChangeWorldPosition(newCube.vec3ENTWorldPosition);
            newCube.CUBScaleEntitySize(ui.gfEGINewEntityScaleRatio);
            std::cout << newCube.uiCUBId << std::endl;
            ui.rdrEGIRender.RDRCreateMandatoryForCube(engine, newCube, newCube.uiCUBId);
        }
        if (entityTypeCombo == 1) {
            newEntityType = dir_light;
            unsigned int newEntityTypeId = engine.uiENGGetNextFreeEntityID(newEntityType);
            CLight newDirectionalLight = CLight(directional, newEntityTypeId, engine.uiENGGetNextFreeEntityID(dir_light), newEntityWorldPosition, glm::vec3(ui.gfEGINewLightDirectionX, ui.gfEGINewLightDirectionY, ui.gfEGINewLightDirectionZ), ui.pgfEGINewLightColor, ui.gfEGINewLightAmbientIntensity, ui.gfEGINewLightDiffuseStrength, ui.gfEGINewLightSpecularStrength, "../shaders/light.vert", "../shaders/light.frag", ui.iEGITextureNumber);
            newDirectionalLight.LIGFirstTimeSetVerticesPosition();
            ui.rdrEGIRender.RDRCreateMandatoryForLight(engine, newDirectionalLight, newDirectionalLight.uiLIGId);
        }
        if (entityTypeCombo == 2) {
            newEntityType = point_light;
            unsigned int newEntityTypeId = engine.uiENGGetNextFreeEntityID(newEntityType);
            CLight newPointLight = CLight(point, newEntityTypeId, engine.uiENGGetNextFreeEntityID(point_light), newEntityWorldPosition, ui.pgfEGINewLightColor, ui.fEGINewLightKC, ui.fEGINewLightKL, ui.fEGINewLightKQ, ui.gfEGINewLightAmbientIntensity, ui.gfEGINewLightDiffuseStrength, ui.gfEGINewLightSpecularStrength, "../shaders/light.vert", "../shaders/light.frag", ui.iEGITextureNumber);
            newPointLight.LIGFirstTimeSetVerticesPosition();
            ui.rdrEGIRender.RDRCreateMandatoryForLight(engine, newPointLight, newPointLight.uiLIGId);
        }
        if (entityTypeCombo == 3) {
            newEntityType = spot_light;
            unsigned int newEntityTypeId = engine.uiENGGetNextFreeEntityID(newEntityType);
            CLight newSpotLight = CLight(spot, newEntityTypeId, engine.uiENGGetNextFreeEntityID(spot_light), newEntityWorldPosition, glm::vec3(ui.gfEGINewLightDirectionX, ui.gfEGINewLightDirectionY, ui.gfEGINewLightDirectionZ), ui.fEGINewLightInnerCutOff, ui.fEGINewLightOuterCutOff, ui.pgfEGINewLightColor, ui.gfEGINewLightAmbientIntensity, ui.gfEGINewLightDiffuseStrength, ui.gfEGINewLightSpecularStrength, "../shaders/light.vert", "../shaders/light.frag", ui.iEGITextureNumber);
            newSpotLight.LIGFirstTimeSetVerticesPosition();
            ui.rdrEGIRender.RDRCreateMandatoryForLight(engine, newSpotLight, newSpotLight.uiLIGId);
        }
    }
    ImGui::End();
}
