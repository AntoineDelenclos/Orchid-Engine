#include "../../include/interface_modules/CIMEngine.h"

#include "imgui.h"
#include "implot.h"

//Interface module related to engine settings
void CIMEngine::CIMEngineInterfaceModule(CEngine& engine, CEngineInterface& ui) {
    ImGui::Begin("Engine Settings");
    ImGui::Checkbox("Fullscreen", &ui.bEGIFullscreen);
    ImGui::Text("Width");
    ImGui::SameLine();
    ImGui::SliderInt("w", &ui.iEGIWidth, 640, 1920);
    ImGui::Text("Height");
    ImGui::SameLine();
    ImGui::SliderInt("h", &ui.iEGIHeight, 480, 1080);
    if (ImGui::SmallButton("Apply new resolution")) {
        engine.ENGChangeResolution((GLuint)ui.iEGIWidth, (GLuint)ui.iEGIHeight);
    }
    std::string FPS = std::to_string(engine.gfENGFpsCounter);
    std::string ms = std::to_string(engine.gfENGFrameDelayMS);
    std::string FPS_MS_TEXT = "Frame " + std::to_string(engine.iENGFrameNumber) + "\nFPS : " + std::to_string(engine.gfENGFpsCounter) + " / FrameTime : " + std::to_string(engine.gfENGFrameDelayMS) + " ms";
    ImGui::Text(FPS_MS_TEXT.c_str());
    ImGui::Text("Frame Limite");
    ImGui::SameLine();
    ImGui::SliderInt("##", &ui.iEGIFpsLimiter, 1, 400); //"##" <=> label vide
    ImGui::Checkbox("FPS Plot display", &ui.bEGIFPSPlotChecked);
    
    //Frame Stats Plot
    if (ui.bEGIFPSPlotChecked == true) {
        if (ImPlot::BeginPlot("FPS Plot")) {
            ImPlot::SetupAxes("t(s)", "FPS");
            ImPlot::PlotLine("FPS", engine.pgfENGFrameDelayMSBuffer, engine.pgfENGFpsCounterBuffer, 1001);
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
            ImPlot::EndPlot();
        }
    }
    ImGui::ColorEdit4("Background color", engine.pgfENGBackgroundColor);
    ImGui::Checkbox("Wireframe display", &ui.bEGIWireframeChecked);
    ImGui::End();
}
