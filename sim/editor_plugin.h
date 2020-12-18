//
// Created by Nathan Bollom on 11/12/20.
//

#ifndef SIMULATOR_EDITOR_PLUGIN_H
#define SIMULATOR_EDITOR_PLUGIN_H

#include <map>
#include <string>
#include <memory>
#include "dialog.h"

class EditorPlugin {

protected:
    std::map<uint32_t, std::string> _items;
    int64_t _current_id;
    bool _changed;
    std::shared_ptr<Dialog> *_dialog;
    State *_state;

    virtual void DrawForm() = 0;
    virtual void Load(int64_t id) = 0;
    virtual void Save() = 0;
    virtual void Delete() = 0;

public:
    EditorPlugin(std::shared_ptr<Dialog> *dialog, State *state);
    void Draw();
    bool HasChanges();
    void AskSave(const std::function<void ()>& on_complete);
};

#endif //SIMULATOR_EDITOR_PLUGIN_H
