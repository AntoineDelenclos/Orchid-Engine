#include "../../include/interface_modules/CIMTextures.h"

#include "imgui.h"

//Interface for textures
void CIMTextures::CIMTexturesInterfaceModule(CEngine& engine, CEngineInterface& ui) {
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2((float)engine.iENGScreenWidth, (float)engine.iENGScreenHeight));
    ImGui::SetNextWindowSize(ImVec2((float)ui.piEGITexturePanelSize[0], (float)ui.piEGITexturePanelSize[1]));
    ImGui::Begin("Textures");
    int nombre_texture_par_ligne = (int)(ImGui::GetWindowSize()[0]/SIZE_TEXTURE_INTERFACE);
    if (nombre_texture_par_ligne != 0) { //Cas où on est sur la fenêtre (on va alors freeze lors des ALT+TAB)
        ui.iEGINombreTexturesParLigne = nombre_texture_par_ligne; //Permet de resize l'interface de sélection de texture en fonction de ce que souhaite l'utilisateur
        ui.piEGITexturePanelSize[0] = (int)ImGui::GetWindowSize()[0]; //On veut stocker les valeurs de la fenêtre ImGui pour pouvoir avoir les bonnes dimensions lorsqu'on revient sur la fenêtre
        ui.piEGITexturePanelSize[1] = (int)ImGui::GetWindowSize()[1];
    }
    ImGui::BeginChild("Textures panel", ImVec2(0, 0), true);
    for (int boucle_tex = 0; boucle_tex < engine.uiENGNumberOfTexturesFile; boucle_tex++) {
        //On doit cast le numero de texture GLuint vers (void*)(intptr_t) car ImGui demande un ImTextureId et vu que c'est propre à chaque API
        //Il faut bien cast notre valeur (cela aurait été différent avec DX9 ou Vulkan)
        // Fonction pour charger l'affichage d'une image dans un module ImGui ci-dessous
        //ImGui::Image((void*)(intptr_t)textureImage.guiTEXGetNumeroTexture(), ImVec2(textureImage.iTEXGetTextureWidth() / 5, textureImage.iTEXGetTextureHeight() / 5));
        CTexture textureImage = engine.ptexENGAllTextures[boucle_tex];
        if (boucle_tex % ui.iEGINombreTexturesParLigne != 0) {
            ImGui::SameLine();
        }
        if (ImGui::ImageButton((void*)(intptr_t)textureImage.guiTEXGetNumeroTexture(), ImVec2(SIZE_TEXTURE_INTERFACE, SIZE_TEXTURE_INTERFACE))) {
            ui.iEGITextureNumber = boucle_tex;
            std::cout << "Valeur texture = " << ui.iEGITextureNumber << std::endl;
        }
    }
    ImGui::EndChild();
    ImGui::End();
}
