//
// window.h
// Created by TheFatNinja 
// 22-01-2020
//

#ifndef SIMULATOR_WINDOW_H
#define SIMULATOR_WINDOW_H

class Window {

protected:
    bool _visible;

public:
    Window();
    void Show();
    void Hide();
    void ToggleVisibility();
    virtual void Draw(float width, float height) = 0;

};

#endif //SIMULATOR_WINDOW_H
