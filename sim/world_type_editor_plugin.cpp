//
// Created by Nathan Bollom on 14/12/20.
//

#include "world_type_editor_plugin.h"
#include <imgui.h>

WorldTypeEditorPlugin::WorldTypeEditorPlugin(std::shared_ptr<Dialog> *dialog, State *state): EditorPlugin(dialog, state) {
    strcpy(_name, "");
    strcpy(_description, "");
    _percent_land = 0;
    _avg_land_size = 0;
    _rivers = 0;
    _mountains = 0;
    std::vector<std::shared_ptr<WorldType>> world_types = WorldType::LoadAll();
    for (const auto& world_type: world_types) {
        _items[world_type->ID()] = world_type->Name();
    }
}

void WorldTypeEditorPlugin::DrawForm() {
    float label_size = 100.0f;
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Name");
    ImGui::SameLine(label_size);
    if (ImGui::InputText("##Name", _name, sizeof(_name))) {
        _changed = true;
    }
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Description");
    ImGui::SameLine(label_size);
    if (ImGui::InputTextMultiline("##Description", _description, sizeof(_description))) {
        _changed = true;
    }
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Land %%");
    ImGui::SameLine(label_size);
    if (ImGui::SliderInt("##PercentLand", &_percent_land, 1, 100)) {
        _changed = true;
    }
}

void WorldTypeEditorPlugin::Load(int64_t id) {
    if (id == -1) {
        _world_type = nullptr;
        strcpy(_name, "");
        strcpy(_description, "");
        _percent_land = 0;
        _avg_land_size = 0;
        _rivers = 0;
        _mountains = 0;
    } else {
        _world_type = WorldType::Load(id);
        strcpy(_name, _world_type->Name().c_str());
        strcpy(_description, _world_type->Description().c_str());
        _percent_land = _world_type->PercentLand();
        _avg_land_size = _world_type->AvgLandSize();
        _rivers = _world_type->Rivers();
        _mountains = _world_type->Mountains();
    }
}

void WorldTypeEditorPlugin::Save() {
    if (_changed) {
        if (_world_type == nullptr) {
            _world_type = std::make_shared<WorldType>();
        }
        _world_type->setName(_name);
        _world_type->setDescription(_description);
        _world_type->setPercentLand(_percent_land);
        _world_type->setAvgLandSize(_avg_land_size);
        _world_type->setRivers(_rivers);
        _world_type->setMountains(_mountains);
        _world_type->Save();
        _changed = false;
        if (_items.count(_world_type->ID()) == 0) {
            _items[_world_type->ID()] = _world_type->Name();
        }
    }
}

void WorldTypeEditorPlugin::Delete() {
    if (_world_type) {
        _items.erase(_world_type->ID());
        _world_type->Delete();
    }
}