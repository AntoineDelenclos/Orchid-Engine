#include "../../include/interface_modules/CIMMenuBar.h"

#include "imgui.h"

static std::string strCIMMenuBarOpenFileDialog(char* filter, HWND owner) {
    std::wstring src;
    const std::wstring title = L"Select a File";
    std::wstring filename(MAX_PATH, L'\0');

    OPENFILENAMEW ofn = { };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = owner; //Put NULL
    ofn.lpstrFilter = L"Textures\0*.png*\0All\0*.*\0";
    ofn.lpstrFile = &filename[0];  // use the std::wstring buffer directly
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = title.c_str();
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameW(&ofn))
    {
        src = filename;    //<----------Save filepath in global variable 
    }
    
    std::string converted_string_src(src.begin(), src.end());
    return converted_string_src;
}

//Test menubar + file explorer
void CIMMenuBar::CIMMenuBarInterfaceModule(CEngine& engine, CEngineInterface& ui) {
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Menu")) {
        if (ImGui::MenuItem("Open file", "Ctrl+O")) {
            std::string pathFile = strCIMMenuBarOpenFileDialog((char*)"All Files (*.*)\0*.*\0", NULL);
            std::cout << "path file : " << pathFile << std::endl;
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Project")) {
        if (ImGui::MenuItem("Add")) {
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Window")) {
        if (ImGui::MenuItem("Script Editor")) {
            ui.bEGIScriptEditorON = !ui.bEGIScriptEditorON;
        }
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}
