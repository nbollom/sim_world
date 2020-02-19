//
// settings_menu.cpp
// Created by TheFatNinja 
// 20-02-2020
//

#include "settings_menu.h"
#include "imgui.h"
#include "menu_stack.h"

SettingsMenu::SettingsMenu(State *state) : Menu(state) {

}

void SettingsMenu::Draw() {
    if (_visible) {
        float width = _state->width;
        float height = _state->height;
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width - 20, height - 20), ImGuiCond_Always);
        if (ImGui::Begin("Settings", &_visible)) {
            // Add controls only if not minimised to save cpu cycles
            ImGui::PushItemWidth(width - 40);
            ImGui::SliderFloat("Font Scale", &_state->font_scale, 1.0f, 10.0f);
            ImGui::PopItemWidth();
        }
        ImGui::End();
    }
    else {
        MenuStack *menu_stack = MenuStack::Shared();
        menu_stack->PopMenu();
    }
}
