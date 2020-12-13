//
// Created by Nathan Bollom on 11/12/20.
//

#include "material_editor_plugin.h"
#include <imgui.h>

MaterialEditorPlugin::MaterialEditorPlugin(std::shared_ptr<Dialog> *dialog, State *state): EditorPlugin(dialog, state) {
    strcpy(_name, "");
    strcpy(_description, "");
    std::vector<std::shared_ptr<Material>> materials = Material::LoadAll();
    for (const auto& material: materials) {
        _items[material->ID()] = material->Name();
    }
}

void MaterialEditorPlugin::DrawForm() {
    float label_size = 100;
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
}

void MaterialEditorPlugin::Load(int64_t id) {
    if (id == -1) {
        _material = nullptr;
        strcpy(_name, "");
        strcpy(_description, "");
    } else {
        _material = Material::Load(id);
        strcpy(_name, _material->Name().c_str());
        strcpy(_description, _material->Description().c_str());
    }
}

void MaterialEditorPlugin::Save() {
    if (_changed) {
        if (_material == nullptr) {
            _material = std::make_shared<Material>();
        }
        _material->setName(_name);
        _material->setDescription(_description);
        _material->Save();
        _changed = false;
        if (_items.count(_material->ID()) == 0) {
            _items[_material->ID()] = _material->Name();
        }
    }
}

void MaterialEditorPlugin::Delete() {
    if (_material) {
        _items.erase(_material->ID());
        _material->Delete();
    }
}
