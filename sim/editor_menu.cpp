//
// editor.cpp
// Created by TheFatNinja 
// 21-01-2020
//

#include "editor_menu.h"
#include "imgui.h"
#include "material_editor_plugin.h"
#include "world_type_editor_plugin.h"

EditorMenu::EditorMenu(State *state) : Menu(state) {
    _dialog = nullptr;
    _editors = {
            {"Materials", [&](){
                return new MaterialEditorPlugin(&_dialog, _state);
            }},
            {"WorldTypes", [&](){
                return new WorldTypeEditorPlugin(&_dialog, _state);
            }}
    };
    _awaiting_save = false;
    _current_editor_name = "";
    _current_editor_plugin = nullptr;
}

void EditorMenu::Draw() {
    if (_visible) {
        if (_dialog != nullptr) {
            _dialog->Draw();
        }
        auto width = static_cast<float>(_state->width);
        auto height = static_cast<float>(_state->height);
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width - 20, height - 20), ImGuiCond_Always);
        if (ImGui::Begin("Data Editors", &_visible, ImGuiWindowFlags_NoResize)) {
            // Add controls only if not minimised to save cpu cycles
            if (ImGui::BeginTabBar("##Editors")) {
                for (const auto& editor: _editors) {
                    if (ImGui::BeginTabItem(editor.first.c_str())) {
                        if (_current_editor_name != editor.first and !_awaiting_save) {
                            if (_current_editor_plugin != nullptr && _current_editor_plugin->HasChanges()) {
                                _awaiting_save = true;
                                std::string new_name = editor.first;
                                std::function<EditorPlugin*()> function = editor.second;
                                _current_editor_plugin->AskSave([&, new_name, function](){
                                    _current_editor_name = new_name;
                                    _current_editor_plugin = function();
                                    _awaiting_save = false;
                                });
                            } else {
                                _current_editor_name = editor.first;
                                _current_editor_plugin = editor.second();
                            }
                        }
                        _current_editor_plugin->Draw();
                        ImGui::EndTabItem();
                    }
                }
                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
}
