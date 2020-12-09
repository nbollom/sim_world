//
// editor.cpp
// Created by TheFatNinja 
// 21-01-2020
//

#include "editor_menu.h"
#include "imgui.h"

EditorMenu::EditorMenu(State *state) : Menu(state) {
    _editor_types = {
            "Materials",
            "WorldTypes"
    };
    _editor_current_item = 0;
}

void EditorMenu::Draw() {
    if (_visible) {
        float width = _state->width;
        float height = _state->height;
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width - 20, height - 20), ImGuiCond_Always);
        if (ImGui::Begin("Data Editors", &_visible, ImGuiWindowFlags_NoResize)) {
            // Add controls only if not minimised to save cpu cycles
            ImGui::PushItemWidth(200);
            ImGui::ListBox(
                    "##Editors",
                    &_editor_current_item,
                    [](void *data, int index, const char **out_text){
                        std::vector<std::string> list = *static_cast<std::vector<std::string>*>(data);
                        *out_text = list[index].c_str();
                        return true;
                    },
                    &_editor_types,
                    _editor_types.size(),
                    15
            );
            ImGui::PopItemWidth();
        }
        ImGui::End();
    }
}
