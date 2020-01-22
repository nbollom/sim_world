//
// Created by Nathan Bollom on 22/1/20.
//

#include <imgui.h>
#include "main_menu.h"

MainMenu::MainMenu() {

}

void MainMenu::Draw(float width, float height) {
    if (_visible) {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
        if (ImGui::Begin("##MainMenu", &_visible,
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground)) {
            // Add controls only if not minimised to save cpu cycles
            ImGui::Indent((width / 2) - 100);
            if (ImGui::Button("New World", ImVec2(200, 50))) {

            }
            ImGui::Indent(0);

        }
        ImGui::End();
    }
}
