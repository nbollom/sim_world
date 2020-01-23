//
// Created by Nathan Bollom on 23/1/20.
//

#ifndef SIMULATOR_MENU_STACK_H
#define SIMULATOR_MENU_STACK_H

#include <vector>
#include "menu.h"

class MenuStack {

private:
    static MenuStack *_instance;
    std::vector<Menu*> _menus;

public:
    void Clear();
    void PushMenu(Menu *menu);
    void PopMenu();

    void Draw();

    static MenuStack* Shared();
};

#endif //SIMULATOR_MENU_STACK_H
