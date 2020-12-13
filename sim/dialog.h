//
// Created by Nathan Bollom on 11/12/20.
//

#ifndef SIMULATOR_DIALOG_H
#define SIMULATOR_DIALOG_H

#include <string>
#include <map>
#include <functional>
#include "state.h"

class Dialog {

private:
    State *_state;
    std::string _title;
    std::string _message;
    std::map<std::string, std::function<void()>> _buttons;

public:
    explicit Dialog(State *state, std::string title, std::string message);
    void AddButton(const std::string& text, std::function<void()> callback);
    void Draw();

};

#endif //SIMULATOR_DIALOG_H
