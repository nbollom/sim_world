//
// Created by Nathan Bollom on 11/12/20.
//

#ifndef SIMULATOR_DIALOG_H
#define SIMULATOR_DIALOG_H

#include <string>
#include <vector>
#include <functional>
#include "state.h"

class Dialog {

private:
    State *_state;
    std::string _title;
    std::string _message;
    float _button_width;
    float _button_height;
    std::vector<std::pair<std::string, std::function<void()>>> _buttons;
    std::function<void()> _button_method;

public:
    explicit Dialog(State *state, std::string title, std::string message);
    explicit Dialog(State *state, std::string title, std::string message, float button_witdth, float button_height);
    void AddButton(const std::string& text, std::function<void()> callback);
    void Draw();

};

#endif //SIMULATOR_DIALOG_H
