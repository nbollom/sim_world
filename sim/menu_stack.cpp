//
// Created by Nathan Bollom on 23/1/20.
//

#include "menu_stack.h"

MenuStack* MenuStack::_instance = nullptr;

Menu* MenuStack::Top() {
    if (!_menus.empty()) {
        Menu *menu = _menus.back();
        return menu;
    }
    return nullptr;
}

void MenuStack::Clear() {
    for (Menu *menu: _menus) {
        delete menu;
    }
    _menus.clear();
}

void MenuStack::PushMenu(Menu *menu) {
    Menu *last = Top();
    if (last) {
        last->Hide();
    }
    _menus.push_back(menu);
    menu->Show();
}

void MenuStack::PopMenu() {
    Menu *menu = Top();
    if (menu) {
        _menus.pop_back();
        delete menu;
    }
    menu = Top();
    if (menu) {
        menu->Show();
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
