//
// Created by Nathan Bollom on 22/1/20.
//

#include <imgui.h>
#include "main_menu.h"
#include "settings_menu.h"
#include "menu_stack.h"

MainMenu::MainMenu(State *state) : Menu(state) {
    _has_saves = false;
}

void MainMenu::NewGame() {

}

void MainMenu::Draw() {
    if (_visible) {
        float width = (float)_state->width;
        float height = (float)_state->height;
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
            if (ImGui::Button("New Game", ImVec2(button_width, button_height))) {

            }
            if (!_has_saves) {
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.2f);
            }
            if (ImGui::Button("Load Game", ImVec2(button_width, button_height))) {
                if (_has_saves) {
                    // TODO: Show load game screen
                }
            }
            if (!_has_saves) {
                ImGui::PopStyleVar();
            }
            if (ImGui::Button("Settings", ImVec2(button_width, button_height))) {
                // TODO: Show settings screen
                SettingsMenu *settings_menu = new SettingsMenu(_state);
                settings_menu->Show();
                MenuStack *menu_stack = MenuStack::Shared();
                menu_stack->PushMenu(settings_menu);
            }
            if (ImGui::Button("Exit", ImVec2(button_width, button_height))) {
                _state->should_quit = true;
            }
            ImGui::Indent(0);

        }
        ImGui::End();
    }
}
