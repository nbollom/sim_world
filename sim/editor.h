//
// editor.h
// Created by TheFatNinja 
// 21-01-2020
//

#ifndef SIMULATOR_EDITOR_H
#define SIMULATOR_EDITOR_H

#include <vector>
#include <string>
#include "window.h"

class Editor : public Window {

private:
    std::vector<std::string> _editor_types;
    int _editor_current_item;

public:
    Editor();
    void Draw(float width, float height) override;

};

#endif //SIMULATOR_EDITOR_H
