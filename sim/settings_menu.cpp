//
// settings_menu.cpp
// Created by TheFatNinja 
// 20-02-2020
//

#include "settings_menu.h"
#include "imgui.h"
#include "menu_stack.h"
#include "settings.h"
#include <simworld/simworld.h>

SettingsMenu::SettingsMenu(State *state) : Menu(state) {

}

void SettingsMenu::Draw() {
    if (_visible) {
        float width = _state->width;
        float height = _state->height;
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width - 20, height - 20), ImGuiCond_Always);
        if (ImGui::Begin("Settings", &_visible, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground)) {
            Settings *settings = Settings::Shared();
            // Add controls only if not minimised to save cpu cycles
            ImGui::PushItemWidth(MIN(width - 100, 500));
            ImGui::SliderFloat("Font Scale", &settings->font_scale, 1.0f, 2.0f);
            ImGui::PopItemWidth();
            ImGui::Checkbox("Show FPS", &settings->show_fps);
            float button_height = MAX(height / 20, 50);
            float button_width = MAX(width / 8, 100);
            ImGui::SetCursorPosY(height - button_height - 20 - ImGui::GetStyle().ItemSpacing.y);
            if (ImGui::Button("Cancel", ImVec2(button_width, button_height))) {
                settings->Load();
                MenuStack::Shared()->PopMenu();
            }
            ImGui::SetCursorPosX(width - button_width - 20 - ImGui::GetStyle().ItemSpacing.x);
            if (ImGui::Button("Save", ImVec2(button_width, button_height))) {
                settings->Save();
                MenuStack::Shared()->PopMenu();
            }
        }
        ImGui::End();
    }
}
