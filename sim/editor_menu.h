//
// editor.h
// Created by TheFatNinja 
// 21-01-2020
//

#ifndef SIMULATOR_EDITOR_MENU_H
#define SIMULATOR_EDITOR_MENU_H

#include <vector>
#include <string>
#include "menu.h"

class EditorMenu : public Menu {

private:
    std::vector<std::string> _editor_types;
    int _editor_current_item;

public:
    explicit EditorMenu(State *state);
    void Draw() override;

};

#endif //SIMULATOR_EDITOR_MENU_H
