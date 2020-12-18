//
// settings_menu.h
// Created by TheFatNinja 
// 20-02-2020
//

#ifndef SIMULATOR_SETTINGS_MENU_H
#define SIMULATOR_SETTINGS_MENU_H

#include "menu.h"
#include <vector>
#include <string>

class SettingsMenu : public Menu {

private:
    std::vector<std::tuple<int, int, int, std::string>> _resolutions;
    std::string _selected_resolution;
    bool _need_resize_window;
    bool _was_fullscreen;

public:
    explicit SettingsMenu(State *state);
    void Draw() override;

};

#endif //SIMULATOR_SETTINGS_MENU_H
