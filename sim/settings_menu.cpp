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
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);
    Settings *settings = Settings::Shared();
    _need_resize_window = false;
    _was_fullscreen = settings->fullscreen;
    for (int i = 0; i < count; i++) {
        int width = modes[i].width;
        int height = modes[i].height;
        int refresh = modes[i].refreshRate;
        std::string summary = std::to_string(width) + "x" + std::to_string(height) + " " + std::to_string(refresh) + "Hz";
        if (width == settings->window_width && height == settings->window_height && refresh == settings->refresh_rate) {
            _selected_resolution = summary;
        }
        _resolutions.emplace_back(width, height, refresh, summary);
    }

    if (_selected_resolution.empty()) {
        _selected_resolution = std::get<3>(_resolutions.front());
        _need_resize_window = true;
    }
}

void SettingsMenu::Draw() {
    if (_visible) {
        auto width = static_cast<float>(_state->width);
        auto height = static_cast<float>(_state->height);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width - 20, height - 20), ImGuiCond_Always);
        if (ImGui::Begin("Settings", &_visible, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
            // Add controls only if not minimised to save cpu cycles
            float label_size = 150;
            Settings *settings = Settings::Shared();
            if (ImGui::BeginTabBar("##SettingsTabs")) {
                if (ImGui::BeginTabItem("Graphics")) {
                    ImGui::PushItemWidth(MIN(width - 100, 500));
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Resolution");
                    ImGui::SameLine(label_size);
                    if (ImGui::BeginCombo("##Resolution", _selected_resolution.c_str())) {
                        for (auto res: _resolutions) {
                            std::string val = std::get<3>(res);
                            bool is_selected = (val == _selected_resolution);
                            if (ImGui::Selectable(val.c_str(), is_selected)) {
                                _selected_resolution = val;
                                settings->window_width = std::get<0>(res);
                                settings->window_height = std::get<1>(res);
                                settings->refresh_rate = std::get<2>(res);
                                _need_resize_window = true;
                            }
                            if (is_selected) {
                                ImGui::SetItemDefaultFocus();
                            }
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Fullscreen");
                    ImGui::SameLine(label_size);
                    ImGui::Checkbox("##Fullscreen", &settings->fullscreen);
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Font Scale");
                    ImGui::SameLine(label_size);
                    ImGui::PushItemWidth(MIN(width - 100, 500));
                    ImGui::SliderFloat("##FontScale", &settings->font_scale, 1.0f, 2.0f);
                    ImGui::PopItemWidth();
                    ImGui::Text("Show FPS");
                    ImGui::SameLine(label_size);
                    ImGui::Checkbox("##ShowFPS", &settings->show_fps);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Other")) {
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            float button_height = MAX(height / 20, 50);
            float button_width = MAX(width / 8, 100);
            ImGui::SetCursorPosY(height - button_height - 20 - ImGui::GetStyle().WindowPadding.y);
            if (ImGui::Button("Cancel", ImVec2(button_width, button_height))) {
                settings->Load(); // Undo any changes
                MenuStack::Shared()->PopMenu();
            }
            ImGui::SameLine(width - button_width - 20 - ImGui::GetStyle().WindowPadding.x);
            if (ImGui::Button("Save", ImVec2(button_width, button_height))) {
                settings->Save(); // Persist any changes
                if (_was_fullscreen != settings->fullscreen || _need_resize_window) {
                    GLFWmonitor *monitor = settings->fullscreen ? glfwGetPrimaryMonitor() : nullptr;
                    glfwSetWindowMonitor(_state->window, monitor, 0, 0, settings->window_width, settings->window_height, settings->refresh_rate);
                    glfwSetWindowPos(_state->window, 0, 0);
                }
                MenuStack::Shared()->PopMenu();
            }
        }
        ImGui::End();
    }
}
