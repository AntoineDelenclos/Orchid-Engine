#include "../include/CEngineInterface.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "interface_modules/CIMCamera.h"
#include "interface_modules/CIMEngine.h"
#include "interface_modules/CIMTextures.h"
#include "interface_modules/CIMNewEntity.h"
#include "interface_modules/CIMEntitiesLists.h"
#include "interface_modules/CIMSelectedEntity.h"
#include "interface_modules/CIMDocking.h"
#include "interface_modules/CIMMenuBar.h"
#include "interface_modules/CIMModels.h"


CEngineInterface::CEngineInterface(CEngine &engine) {
    bEGIFullscreenPrev = false;
    bEGIFullscreen = false;
    bEGIWireframeChecked = false;
    bEGIFPSPlotChecked = false;
    bEGIScriptEditorON = false;
    iEGIFpsLimiter = engine.iENGFpsLimiter;
    iEGIWidth = engine.uiENGWidth;
    iEGIHeight = engine.uiENGHeight;
    piEGITexturePanelSize[0] = 32; //Taille minimum d'une fenêtre ImGui.
    piEGITexturePanelSize[1] = 32;
    iEGINombreTexturesParLigne = 1;
    //New entity values
    pgfEGINewEntityXYZPos = new GLfloat[3];
    pgfEGINewEntityXYZPos[0] = 0.f;
    pgfEGINewEntityXYZPos[1] = 0.f;
    pgfEGINewEntityXYZPos[2] = 0.f;
    uiEGINewEntityGlobalID = 0;
    uiEGINewEntityTypeID = 0;
    gfEGINewEntityScaleRatio = 1.f;
    //New entity material values
    vec3EGINewEntityAmbient = glm::vec3(1.0f, 1.0f, 1.0f);
    vec3EGINewEntityDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    vec3EGINewEntitySpecular = glm::vec3(1.0f, 1.0f, 1.0f);
    fEGINewEntityShininess = 1.0f;
    fEGINewEntityTransparency = 1.0f;
    //New entity light
    pgfEGINewLightColor[0] = 1.f; pgfEGINewLightColor[1] = 1.f; pgfEGINewLightColor[2] = 1.f;
    gfEGINewLightAmbientIntensity = 0.5f;
    gfEGINewLightDiffuseStrength = 0.5f;
    gfEGINewLightSpecularStrength = 1.f;
    gfEGINewLightDirectionX = 1.f; gfEGINewLightDirectionY = 1.f; gfEGINewLightDirectionZ = 1.f;
    fEGINewLightKC = 1.0f; fEGINewLightKL = 0.09f; fEGINewLightKQ = 0.032f;
    fEGINewLightInnerCutOff = 0.91f; fEGINewLightOuterCutOff = 0.82f;


    //Entity modifications via interface
    fEGINewX = 0.f; fEGINewY = 0.f; fEGINewZ = 0.f;
    gfEGINewRatio = 1.f;
    gfEGINewCubeLength = 1.f; gfEGINewCubeHeight = 1.f; gfEGINewCubeDepth = 1.f;
    fEGINewDirectionX = 1.0f; fEGINewDirectionY = 1.0f; fEGINewDirectionZ = 1.0f;
    fEGINewKC = 1.0f; fEGINewKL = 0.09f; fEGINewKQ = 0.032f;
    //Selected entity in the lists
    siEGISelectedEntity_cube = -1; siEGISelectedEntity_dir_light = -1; siEGISelectedEntity_point_light = -1;
    siEGISelectedEntity_spot_light = -1; siEGISelectedType = -1;

    iEGITextureNumber = 0;
    //3D models
    siEGISelectedModel = -1;
    strcpy_s(pcEGINewModelPath, sizeof(pcEGINewModelPath), "../data/assets/models/backpack/backpack.obj");
    rdrEGIRender = CRender();

    //Launch commands for ImGui and ImPlot
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; //Va permettre de mettre le docking en place 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(engine.pwindowENGWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

CEngineInterface::~CEngineInterface() {
    //EXIT IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
}

void CEngineInterface::EGIWireframeUpdate() {
    if (bEGIWireframeChecked == false) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if (bEGIWireframeChecked == true) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

//Check if the render mode should be windowed or fullscreen
void CEngineInterface::EGIFullscreenUpdate(CEngine &engine) {
    if (bEGIFullscreen == bEGIFullscreenPrev) {
        return;
    }

    if (bEGIFullscreen == false) {
        int monitorXPos; int monitorYPos; int monitorWidth; int monitorHeight;
        glfwGetMonitorWorkarea(engine.pmonitorENGMonitor, &monitorXPos, &monitorYPos, &monitorWidth, &monitorHeight);
        glfwSetWindowMonitor(engine.pwindowENGWindow, NULL, 20, 20, monitorWidth, monitorHeight, 0);
    }
    else {
        glfwSetWindowMonitor(engine.pwindowENGWindow, engine.pmonitorENGMonitor, 0, 0, engine.uiENGWidth, engine.uiENGHeight, 0);
        glfwSwapInterval(0); //Désactive le VSync
    }

    bEGIFullscreenPrev = bEGIFullscreen;
}

//Fonction à compléter notamment avec les wireframe et le fullscreen car les laisser dans l'interface est moins logique
void CEngineInterface::EGIInterfaceToEngine(CEngine &engine) {
    engine.ENGSetFpsLimit(iEGIFpsLimiter);
}

//Do the pre-update process
void CEngineInterface::EGIPreUpdate(CEngine& engine) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void CEngineInterface::EGIPostUpdate(CEngine& engine) {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//Update the display of the interface at each frame time
void CEngineInterface::EGIUpdate(CEngine &engine) {
    //Interface Modules rendering methods
    CIMDocking::CIMDockingInterfaceModule(engine, *this);
    CIMEngine::CIMEngineInterfaceModule(engine, *this);
    CIMCamera::CIMCameraInterfaceModule(engine.inpENGInputs.camINPChosenCamera);
    CIMTextures::CIMTexturesInterfaceModule(engine, *this);
    CIMEntitiesLists::CIMEntitiesListsInterfaceModule(engine, *this);
    CIMSelectedEntity::CIMSelectedEntityInterfaceModule(engine, *this);
    CIMNewEntity::CIMNewEntityInterfaceModule(engine, *this);
    CIMModels::CIMModelsInterfaceModule(engine, *this);

    CIMMenuBar::CIMMenuBarInterfaceModule(engine, *this);

    EGIWireframeUpdate();
    EGIFullscreenUpdate(engine);

    EGIInterfaceToEngine(engine);
}

//Framebuffer window module
void CEngineInterface::EGIFramebufferModule(CEngine& engine, GLuint texture) {
    ImGui::Begin("Framebuffer window"); {
        //ImGui::BeginChild("Framebuffer child"); //Using a child will auto fill the window
        ImVec2 wSize = ImGui::GetWindowSize();
        //ImGui::Text("test");
        ImGui::Image((ImTextureID)texture, ImVec2(engine.iENGScreenWidth, engine.iENGScreenHeight), ImVec2(0, 1), ImVec2(1, 0));
        //ImGui::EndChild();
    }
    ImGui::End();
}

