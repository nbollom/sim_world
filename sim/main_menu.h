//
// Created by Nathan Bollom on 22/1/20.
//

#ifndef SIMULATOR_MAIN_MENU_H
#define SIMULATOR_MAIN_MENU_H

#include "window.h"

class MainMenu : public Window {

private:
    bool _has_world;

    void CreateNewWorld();

public:
    MainMenu();
    void Draw(float width, float height) override;

};

#endif //SIMULATOR_MAIN_MENU_H
