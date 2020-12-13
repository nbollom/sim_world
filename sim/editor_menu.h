//
// editor.h
// Created by TheFatNinja 
// 21-01-2020
//

#ifndef SIMULATOR_EDITOR_MENU_H
#define SIMULATOR_EDITOR_MENU_H

#include <map>
#include <string>
#include <functional>
#include "menu.h"
#include "editor_plugin.h"
#include "dialog.h"

class EditorMenu : public Menu {

private:
    std::map<std::string, std::function<EditorPlugin*()>> _editors;
    bool _awaiting_save;
    std::string _current_editor_name;
    EditorPlugin *_current_editor_plugin;
    std::shared_ptr<Dialog> _dialog = nullptr;

public:
    explicit EditorMenu(State *state);
    void Draw() override;

};

#endif //SIMULATOR_EDITOR_MENU_H
