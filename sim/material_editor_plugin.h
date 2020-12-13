//
// Created by Nathan Bollom on 11/12/20.
//

#ifndef SIMULATOR_MATERIAL_EDITOR_PLUGIN_H
#define SIMULATOR_MATERIAL_EDITOR_PLUGIN_H

#include "editor_plugin.h"
#include <simworld/simworld.h>

class MaterialEditorPlugin : public EditorPlugin {

private:
    std::shared_ptr<Material> _material;
    char _name[256]{};
    char _description[65536]{};

public:
    explicit MaterialEditorPlugin(std::shared_ptr<Dialog> *dialog, State *state);

    void DrawForm() override;
    void Load(int64_t id) override;
    void Save() override;
    void Delete() override;
};

#endif //SIMULATOR_MATERIAL_EDITOR_PLUGIN_H
