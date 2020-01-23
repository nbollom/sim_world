//
// Created by Nathan Bollom on 22/1/20.
//

#include <imgui.h>
#include "main_menu.h"

MainMenu::MainMenu() {

}

void MainMenu::CreateNewWorld() {

}

void MainMenu::Draw(float width, float height) {
    if (_visible) {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
        if (ImGui::Begin("##MainMenu", &_visible,
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground)) {
            // Add controls only if not minimised to save cpu cycles
            float spacing = ImGui::GetStyle().ItemSpacing.y;
            float buttons = 1;
            float button_height = height / 20;
            float button_width = width / 8;
            float top_padding = (height / 3) - (((button_height * buttons) + (spacing * (buttons - 1))) / 2) - spacing;
            ImGui::Dummy(ImVec2(1, top_padding));
            ImGui::SetNextItemWidth(width);
            char text[50] = "The quick brown fox jumps over the lazy dog";
            float text_width = ImGui::CalcTextSize(text).x;
            ImGui::SetCursorPosX((width / 2) - (text_width / 2));
            ImGui::Text("%s", text);
            ImGui::Indent((width / 2) - (button_width / 2));
            if (ImGui::Button("New World", ImVec2(button_width, button_height))) {
                CreateNewWorld();
            }
            if (!_has_world) {
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }
            if (ImGui::Button("New Game", ImVec2(button_width, button_height))) {

            }
            if (ImGui::Button("Load Game", ImVec2(button_width, button_height))) {

            }
            if (!_has_world) {
                ImGui::PopStyleVar();
            }
            if (ImGui::Button("Settings", ImVec2(button_width, button_height))) {

            }
            if (ImGui::Button("Exit", ImVec2(button_width, button_height))) {
                // TODO: pass quit event back to main
            }
            ImGui::Indent(0);

        }
        ImGui::End();
    }
}
