#include "../../include/interface_modules/CIMDocking.h"

#include "imgui.h"

void CIMDocking::CIMDockingInterfaceModule(CEngine& engine, CEngineInterface& ui) { //https://github.com/ocornut/imgui/issues/7067 documentation Novembre 2023
    //Dockspace
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::Begin("Orchid Engine", NULL, window_flags);
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    ImGui::End();
}
