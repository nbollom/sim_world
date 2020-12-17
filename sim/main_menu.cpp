//
// Created by Nathan Bollom on 22/1/20.
//

#include <imgui.h>
#include "main_menu.h"
#include "settings_menu.h"
#include "menu_stack.h"
#include <simworld/simworld.h>

MainMenu::MainMenu(State *state) : Menu(state) {
    _has_saves = false;
}

void MainMenu::Draw() {
    if (_visible) {
        auto width = static_cast<float>(_state->width);
        auto height = static_cast<float>(_state->height);
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
        if (ImGui::Begin("##MainMenu", &_visible,
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
            // Add controls only if not minimised to save cpu cycles
            float spacing = ImGui::GetStyle().ItemSpacing.y;
            float buttons = 1;
            float button_height = MAX(height / 20.0f, 50.0f);
            float button_width = MAX(width / 8.0f, 100.0f);
            float top_padding = (height / 3.0f) - (((button_height * buttons) + (spacing * (buttons - 1))) / 2.0f) - spacing;
            ImGui::Dummy(ImVec2(1, top_padding));
            char text[50] = "Simulator";
            float text_width = ImGui::CalcTextSize(text).x;
            ImGui::SetNextItemWidth(text_width);
            ImGui::SetCursorPosX((width / 2.0f) - (text_width / 2.0f));
            ImGui::Text("%s", text);
            ImGui::SetCursorPosX((width / 2.0f) - (button_width / 2.0f));
            if (ImGui::Button("New Game", ImVec2(button_width, button_height))) {

            }
            if (!_has_saves) {
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.2f);
            }
            ImGui::SetCursorPosX((width / 2.0f) - (button_width / 2.0f));
            if (ImGui::Button("Load Game", ImVec2(button_width, button_height))) {
                if (_has_saves) {
                    // TODO: Show load game screen
                }
            }
            if (!_has_saves) {
                ImGui::PopStyleVar();
            }
            ImGui::SetCursorPosX((width / 2.0f) - (button_width / 2.0f));
            if (ImGui::Button("Settings", ImVec2(button_width, button_height))) {
                // TODO: Show settings screen
                auto *settings_menu = new SettingsMenu(_state);
                MenuStack *menu_stack = MenuStack::Shared();
                menu_stack->PushMenu(settings_menu);
            }
            ImGui::SetCursorPosX((width / 2.0f) - (button_width / 2.0f));
            if (ImGui::Button("Exit", ImVec2(button_width, button_height))) {
                _state->should_quit = true;
            }

        }
        ImGui::End();
    }
}
