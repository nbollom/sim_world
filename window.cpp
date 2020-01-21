//
// window.cpp
// Created by TheFatNinja 
// 22-01-2020
//

#include "window.h"

Window::Window() {
    _visible = false;
}

void Window::Show() {
    _visible = true;
}

void Window::Hide() {
    _visible = false;
}

void Window::ToggleVisibility() {
    _visible = !_visible;
}
