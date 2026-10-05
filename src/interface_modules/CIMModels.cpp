#include "../../include/interface_modules/CIMModels.h"

#include "imgui.h"

//Interface to load a 3D model from a path (the list is in "Entities Lists", the edition in "Selected entity")
void CIMModels::CIMModelsInterfaceModule(CEngine& engine, CEngineInterface& ui) {
    ImGui::Begin("Models");
    //Loading a new model
    ImGui::InputText("Path", ui.pcEGINewModelPath, sizeof(ui.pcEGINewModelPath));
    static bool bLoadFailed = false;
    if (ImGui::SmallButton("Load model")) {
        bLoadFailed = !engine.ENGAddModel(ui.pcEGINewModelPath);
        if (!bLoadFailed) {
            ui.siEGISelectedModel = (int)engine.modENGModels.size() - 1;
            ui.siEGISelectedType = 4; //Shown in the "Selected entity" window
        }
    }
    if (bLoadFailed) {
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Could not load this model");
    }

    ImGui::End();
}
