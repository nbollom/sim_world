//
// Created by Nathan Bollom on 11/12/20.
//

#include "editor_plugin.h"
#include <imgui.h>

#include <utility>

EditorPlugin::EditorPlugin(std::shared_ptr<Dialog> *dialog, State *state): _dialog(dialog), _state(state) {
    _current_id = -1;
    _changed = false;
}

void EditorPlugin::Draw() {
    ImGui::BeginGroup();
    ImGui::PushItemWidth(200.0f);
    if (ImGui::Button("New")) {
        if (_changed) {
            AskSave([&](){
                _changed = false;
                _current_id = -1;
                Load(_current_id);
            });
        } else {
            _current_id = -1;
            Load(_current_id);
        }
    }
    if (ImGui::ListBoxHeader("##Items", _items.size(), 30)) {
        for (const auto& item: _items) {
            bool selected = _current_id == item.first;
            if (ImGui::Selectable(item.second.c_str(), selected)) {
                if (_current_id != item.first) {
                    if (_changed) {
                        int64_t new_id = item.first;
                        AskSave([&, new_id]() {
                            _changed = false;
                            _current_id = new_id;
                            Load(new_id);
                        });
                    } else {
                        _current_id = item.first;
                        Load(_current_id);
                    }
                }
            }
        }
        ImGui::ListBoxFooter();
    }
    ImGui::PopItemWidth();
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::BeginGroup();
    DrawForm();
    if (ImGui::Button("Save")) {
        Save();
        _changed = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Revert")) {
        Load(_current_id);
        _changed = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete")) {
        Delete();
        _current_id = -1;
        Load(_current_id);
    }
    ImGui::EndGroup();
}

bool EditorPlugin::HasChanges() {
    return _changed;
}

void EditorPlugin::AskSave(const std::function<void ()>& on_complete) {
    *_dialog = std::make_shared<Dialog>(_state, "Changes Detected", "Do you want to save your changes?", 100, 20);
    (*_dialog)->AddButton("No", [&, on_complete]() {
        on_complete();
        *_dialog = nullptr;
    });
    (*_dialog)->AddButton("Yes", [&, on_complete]() {
        Save();
        on_complete();
        *_dialog = nullptr;
    });
}
