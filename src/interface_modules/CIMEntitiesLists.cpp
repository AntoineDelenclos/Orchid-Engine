#include "../../include/interface_modules/CIMEntitiesLists.h"

#include "imgui.h"

void CIMEntitiesLists::CIMEntitiesListsInterfaceModule(CEngine& engine, CEngineInterface& ui) {
    ImGui::Begin("Entities Lists");  
    std::string strHeaderCube = "Cube entities ("; strHeaderCube += std::to_string(engine.iENGGetNumberOfEntitiesTypeX(cube)).c_str(); strHeaderCube += ')';
    if (ImGui::CollapsingHeader(strHeaderCube.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) { //Mettre en DefaultOpen permet de réouvrir si on ajoute une entité du type correspondant
        int draw_lines_cube = engine.iENGGetNumberOfEntitiesTypeX(cube);
        static int max_height_in_lines_cube = 5;
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::DragInt("Max Height (in Lines) Cubes", &max_height_in_lines_cube, 0.2f);
        ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1), ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * max_height_in_lines_cube));
        if (ImGui::BeginChild("ConstrainedChildCube", ImVec2(-FLT_MIN, 0.0f), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY)) {
            for (int nb_ent = 0; nb_ent < draw_lines_cube; nb_ent++) {
                char label[128];
                sprintf_s(label, engine.pcubENGCubeEntitiesList[nb_ent].strENTName.c_str(), nb_ent);
                ImU32 text_color; glm::vec4 rgbc;
                if (engine.pcubENGCubeEntitiesList[nb_ent].bENTActive) {
                    rgbc = vec4HexToRGBAColor(ACTIVE_COLOR);
                }
                else {
                    rgbc = vec4HexToRGBAColor(UNACTIVE_COLOR);
                }
                text_color = IM_COL32(rgbc.x, rgbc.y, rgbc.z, rgbc.w);
                ImGui::PushStyleColor(ImGuiCol_Text, text_color);
                bool selected = ImGui::Selectable(label, ui.siEGISelectedEntity_cube == nb_ent);
                ImGui::PopStyleColor();
                if (selected) {
                    ui.siEGISelectedEntity_cube = nb_ent;
                    ui.siEGISelectedType = 0;
                    ui.fEGINewX = engine.pcubENGCubeEntitiesList[ui.siEGISelectedEntity_cube].vec3ENTWorldPosition.x;
                    ui.fEGINewY = engine.pcubENGCubeEntitiesList[ui.siEGISelectedEntity_cube].vec3ENTWorldPosition.y;
                    ui.fEGINewZ = engine.pcubENGCubeEntitiesList[ui.siEGISelectedEntity_cube].vec3ENTWorldPosition.z;
                    ui.gfEGINewRatio = engine.pcubENGCubeEntitiesList[ui.siEGISelectedEntity_cube].gfCUBScaleRatio;
                    ui.gfEGINewCubeLength = engine.pcubENGCubeEntitiesList[ui.siEGISelectedEntity_cube].gfCUBLength;
                }
            }
        }
        ImGui::EndChild();
    }

    std::string strHeaderDirLight = "Directional light entities ("; strHeaderDirLight += std::to_string(engine.iENGGetNumberOfEntitiesTypeX(dir_light)).c_str(); strHeaderDirLight += ')';
    if (ImGui::CollapsingHeader(strHeaderDirLight.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
        int draw_lines_directional = engine.iENGGetNumberOfEntitiesTypeX(dir_light);
        static int max_height_in_lines_directional = 5;
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::DragInt("Max Height (in Lines) Directional Lights", &max_height_in_lines_directional, 0.2f);
        ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1), ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * max_height_in_lines_directional));
        if (ImGui::BeginChild("ConstrainedChildDirectional", ImVec2(-FLT_MIN, 0.0f), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY)) {
            for (int nb_ent = 0; nb_ent < draw_lines_directional; nb_ent++) {
                char label[128];
                sprintf_s(label, engine.pligENGDirectionalLightsList[nb_ent].strENTName.c_str(), nb_ent);
                ImU32 text_color; glm::vec4 rgbc;
                if (engine.pligENGDirectionalLightsList[nb_ent].bENTActive) {
                    rgbc = vec4HexToRGBAColor(ACTIVE_COLOR);
                }
                else {
                    rgbc = vec4HexToRGBAColor(UNACTIVE_COLOR);
                }
                text_color = IM_COL32(rgbc.x, rgbc.y, rgbc.z, rgbc.w);
                ImGui::PushStyleColor(ImGuiCol_Text, text_color);
                bool selected = ImGui::Selectable(label, ui.siEGISelectedEntity_dir_light == nb_ent);
                ImGui::PopStyleColor();
                if (selected) {
                    ui.siEGISelectedEntity_dir_light = nb_ent;
                    ui.siEGISelectedType = 1;
                    ui.fEGINewX = engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].vec3ENTWorldPosition.x;
                    ui.fEGINewY = engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].vec3ENTWorldPosition.y;
                    ui.fEGINewZ = engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].vec3ENTWorldPosition.z;
                    ui.gfEGINewRatio = engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].gfLIGScaleRatio;
                    ui.fEGINewDirectionX = engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].vec3LIGDirection.x;
                    ui.fEGINewDirectionY = engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].vec3LIGDirection.y;
                    ui.fEGINewDirectionZ = engine.pligENGDirectionalLightsList[ui.siEGISelectedEntity_dir_light].vec3LIGDirection.z;
                }
            }
        }
        ImGui::EndChild();
    }
    
    std::string strHeaderPointLight = "Point light entities ("; strHeaderPointLight += std::to_string(engine.iENGGetNumberOfEntitiesTypeX(point_light)).c_str(); strHeaderPointLight += ')';
    if (ImGui::CollapsingHeader(strHeaderPointLight.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
        int draw_lines_point = engine.iENGGetNumberOfEntitiesTypeX(point_light);
        static int max_height_in_lines_point = 5;
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::DragInt("Max Height (in Lines) Point Lights", &max_height_in_lines_point, 0.2f);
        ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1), ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * max_height_in_lines_point));
        if (ImGui::BeginChild("ConstrainedChildPoint", ImVec2(-FLT_MIN, 0.0f), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY)) {
            for (int nb_ent = 0; nb_ent < draw_lines_point; nb_ent++) {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                char label[128];
                sprintf_s(label, engine.pligENGPointLightsList[nb_ent].strENTName.c_str(), nb_ent);
                ImU32 text_color; glm::vec4 rgbc;
                if (engine.pligENGPointLightsList[nb_ent].bENTActive) {
                    rgbc = vec4HexToRGBAColor(ACTIVE_COLOR);
                }
                else {
                    rgbc = vec4HexToRGBAColor(UNACTIVE_COLOR);
                }
                text_color = IM_COL32(rgbc.x, rgbc.y, rgbc.z, rgbc.w);
                ImGui::PushStyleColor(ImGuiCol_Text, text_color);
                bool selected = ImGui::Selectable(label, ui.siEGISelectedEntity_point_light == nb_ent);
                ImGui::PopStyleColor();
                if (selected) {
                    ui.siEGISelectedEntity_point_light = nb_ent;
                    ui.siEGISelectedType = 2;
                    ui.fEGINewX = engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].vec3ENTWorldPosition.x;
                    ui.fEGINewY = engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].vec3ENTWorldPosition.y;
                    ui.fEGINewZ = engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].vec3ENTWorldPosition.z;
                    ui.gfEGINewRatio = engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].gfLIGScaleRatio;
                    ui.fEGINewKC = engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].fLIGPointKC;
                    ui.fEGINewKL = engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].fLIGPointKL;
                    ui.fEGINewKQ = engine.pligENGPointLightsList[ui.siEGISelectedEntity_point_light].fLIGPointKQ;
                }
            }
        }
        ImGui::EndChild();
    }

    std::string strHeaderSpotLight = "Spotlight entities ("; strHeaderSpotLight += std::to_string(engine.iENGGetNumberOfEntitiesTypeX(spot_light)).c_str(); strHeaderSpotLight += ')';
    if (ImGui::CollapsingHeader(strHeaderSpotLight.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
        int draw_lines_spot = engine.iENGGetNumberOfEntitiesTypeX(spot_light);
        static int max_height_in_lines_spot = 5;
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::DragInt("Max Height (in Lines) SpotLights", &max_height_in_lines_spot, 0.2f);
        ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1), ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * max_height_in_lines_spot));
        if (ImGui::BeginChild("ConstrainedChildSpot", ImVec2(-FLT_MIN, 0.0f), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY)) {
            for (int nb_ent = 0; nb_ent < draw_lines_spot; nb_ent++) {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                char label[128];
                sprintf_s(label, engine.pligENGSpotLightsList[nb_ent].strENTName.c_str(), nb_ent);
                ImU32 text_color; glm::vec4 rgbc;
                if (engine.pligENGSpotLightsList[nb_ent].bENTActive) {
                    rgbc = vec4HexToRGBAColor(ACTIVE_COLOR);
                }
                else {
                    rgbc = vec4HexToRGBAColor(UNACTIVE_COLOR);
                }
                text_color = IM_COL32(rgbc.x, rgbc.y, rgbc.z, rgbc.w);
                ImGui::PushStyleColor(ImGuiCol_Text, text_color);
                bool selected = ImGui::Selectable(label, ui.siEGISelectedEntity_spot_light == nb_ent);
                ImGui::PopStyleColor();
                if (selected) {
                    ui.siEGISelectedEntity_spot_light = nb_ent;
                    ui.siEGISelectedType = 3;
                    ui.fEGINewX = engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].vec3ENTWorldPosition.x;
                    ui.fEGINewY = engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].vec3ENTWorldPosition.y;
                    ui.fEGINewZ = engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].vec3ENTWorldPosition.z;
                    ui.gfEGINewRatio = engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].gfLIGScaleRatio;
                    ui.fEGINewDirectionX = engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].vec3LIGDirection.x;
                    ui.fEGINewDirectionY = engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].vec3LIGDirection.y;
                    ui.fEGINewDirectionZ = engine.pligENGSpotLightsList[ui.siEGISelectedEntity_spot_light].vec3LIGDirection.z;
                }
            }
        }
        ImGui::EndChild();
    }    
    std::string strHeaderModel = "Model entities (" + std::to_string(engine.modENGModels.size()) + ")";
    if (ImGui::CollapsingHeader(strHeaderModel.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
        int draw_lines_model = (int)engine.modENGModels.size();
        static int max_height_in_lines_model = 5;
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::DragInt("Max Height (in Lines) Models", &max_height_in_lines_model, 0.2f);
        ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1), ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * max_height_in_lines_model));
        if (ImGui::BeginChild("ConstrainedChildModel", ImVec2(-FLT_MIN, 0.0f), ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY)) {
            for (int nb_ent = 0; nb_ent < draw_lines_model; nb_ent++) {
                //"##model<index>" keeps the ImGui id unique even if two models share the same name
                std::string label = engine.modENGModels[nb_ent].strMODName + "##model" + std::to_string(nb_ent);
                glm::vec4 rgbc = vec4HexToRGBAColor(engine.modENGModels[nb_ent].bMODActive ? ACTIVE_COLOR : UNACTIVE_COLOR);
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(rgbc.x, rgbc.y, rgbc.z, rgbc.w));
                bool selected = ImGui::Selectable(label.c_str(), ui.siEGISelectedModel == nb_ent);
                ImGui::PopStyleColor();
                if (selected) {
                    ui.siEGISelectedModel = nb_ent;
                    ui.siEGISelectedType = 4; //Edited in the "Selected entity" window
                }
            }
        }
        ImGui::EndChild();
    }
    ImGui::End();
}
