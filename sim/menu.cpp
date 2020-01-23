//
// window.cpp
// Created by TheFatNinja 
// 22-01-2020
//

#include "menu.h"

Menu::Menu(State *state) : _state(state) {
    _visible = false;
}

void Menu::Show() {
    _visible = true;
}

void Menu::Hide() {
    _visible = false;
}

void Menu::ToggleVisibility() {
    _visible = !_visible;
}
