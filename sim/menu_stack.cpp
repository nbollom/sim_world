//
// Created by Nathan Bollom on 23/1/20.
//

#include "menu_stack.h"

MenuStack* MenuStack::_instance = nullptr;

void MenuStack::Clear() {
    for (Menu *menu: _menus) {
        delete menu;
    }
    _menus.clear();
}

void MenuStack::PushMenu(Menu *menu) {
    _menus.push_back(menu);
}

void MenuStack::PopMenu() {
    if (!_menus.empty()) {
        Menu *menu = _menus.back();
        _menus.pop_back();
        delete menu;
    }
}

void MenuStack::Draw() {
    for (Menu *menu: _menus) {
        menu->Draw();
    }
}

MenuStack * MenuStack::Shared() {
    if (_instance == nullptr) {
        _instance = new MenuStack();
    }
    return _instance;
}
