//
// settings_menu.h
// Created by TheFatNinja 
// 20-02-2020
//

#ifndef SIMULATOR_SETTINGS_MENU_H
#define SIMULATOR_SETTINGS_MENU_H

#include "menu.h"

class SettingsMenu : public Menu {

private:

public:
    explicit SettingsMenu(State *state);
    void Draw() override;

};

#endif //SIMULATOR_SETTINGS_MENU_H
