//
// Created by Nathan Bollom on 14/12/20.
//

#ifndef SIMULATOR_WORLD_TYPE_EDITOR_PLUGIN_H
#define SIMULATOR_WORLD_TYPE_EDITOR_PLUGIN_H

#include "editor_plugin.h"
#include <simworld/simworld.h>

class WorldTypeEditorPlugin : public EditorPlugin {

private:
    std::shared_ptr<WorldType> _world_type;
    char _name[256]{};
    char _description[65536]{};
    int _percent_land;
    int _avg_land_size;
    int _rivers;
    int _mountains;

public:
    explicit WorldTypeEditorPlugin(std::shared_ptr<Dialog> *dialog, State *state);

    void DrawForm() override;
    void Load(int64_t id) override;
    void Save() override;
    void Delete() override;
};

#endif //SIMULATOR_WORLD_TYPE_EDITOR_PLUGIN_H
