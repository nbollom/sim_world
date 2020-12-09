//
// Created by Nathan Bollom on 8/12/20.
//

#include "settings.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

template <class T>
inline void load_setting_value(nlohmann::json json, const char *key, T &variable) {
    try {
        variable = json[key];
    }
    catch (std::exception &exception) {
        printf("Failed to parse setting %s\nError: %s\n", key, exception.what());
    }
}

Settings* Settings::_instance = nullptr;

Settings::Settings() {
    ResetToDefault();  // used so default values are set if no saved settings or missing settings in json
    Load();
}

Settings * Settings::Shared() {
    if (_instance == nullptr) {
        _instance = new Settings();
    }
    return _instance;
}

void Settings::Save() {
    nlohmann::json json;
    // Graphics section
    nlohmann::json graphics;
    graphics["window_width"] = window_width;
    graphics["window_height"] = window_height;
    graphics["fullscreen"] = fullscreen;
    graphics["font_scale"] = font_scale;
    graphics["show_fps"] = show_fps;
    json["graphics"] = graphics;
    std::ofstream settings_file("settings.json", std::ios::out);
    settings_file << json.dump(4);
    settings_file.close();
}

void Settings::Load() {
    std::ifstream settings_file("settings.json", std::ios::in);
    if (settings_file.is_open()) {
        std::string file_contents;
        std::string line;
        while ( getline (settings_file, line) )
        {
            file_contents += line + '\n';
        }
        settings_file.close();
        nlohmann::json json = nlohmann::json::parse(file_contents);
        // Graphics section
        if (json.contains("graphics")) {
            nlohmann::json graphics = json["graphics"];
            load_setting_value(graphics, "window_width", window_width);
            load_setting_value(graphics, "window_height", window_height);
            load_setting_value(graphics, "fullscreen", fullscreen);
            load_setting_value(graphics, "font_scale", font_scale);
            load_setting_value(graphics, "show_fps", show_fps);
        }
    }
}

void Settings::ResetToDefault() {
    window_width = 1270;
    window_height = 720;
    fullscreen = false;
    font_scale = 1.0f;
    show_fps = false;
}
