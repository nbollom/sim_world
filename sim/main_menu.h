//
// Created by Nathan Bollom on 22/1/20.
//

#ifndef SIMULATOR_MAIN_MENU_H
#define SIMULATOR_MAIN_MENU_H

#include "menu.h"

class MainMenu : public Menu {

private:
    bool _has_saves;

public:
    explicit MainMenu(State *state);
    void Draw() override;

};

#endif //SIMULATOR_MAIN_MENU_H
