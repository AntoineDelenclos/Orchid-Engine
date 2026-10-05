#include "../../include/interface_modules/CIMCamera.h"

#include "imgui.h"

void CIMCamera::CIMCameraInterfaceModule(CCamera &camera) {
    ImGui::Begin("Camera");
    ImGui::SliderFloat("Camera speed", &camera.fCAMCameraSpeedMovement, 0.0f, 20.0f);
    ImGui::SliderFloat("Sensitivity", &camera.fCAMCameraSensitivity, 0.0f, 1.0f);
    ImGui::Text("Camera position: (%.3f, %.3f, %.3f)", camera.vec3CAMCameraPosition.x, camera.vec3CAMCameraPosition.y, camera.vec3CAMCameraPosition.z);
    ImGui::End();
}
