//
// window.h
// Created by TheFatNinja 
// 22-01-2020
//

#ifndef SIMULATOR_MENU_H
#define SIMULATOR_MENU_H

#include "state.h"

class Menu {

protected:
    bool _visible;
    State *_state;

public:
    explicit Menu(State *state);
    virtual ~Menu() = default;
    void Show();
    void Hide();
    void ToggleVisibility();
    virtual void Draw() = 0;

};

#endif //SIMULATOR_MENU_H
