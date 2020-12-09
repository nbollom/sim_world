//
// Created by Nathan Bollom on 8/12/20.
//

#ifndef SIMULATOR_SETTINGS_H
#define SIMULATOR_SETTINGS_H

class Settings {

private:
    static Settings *_instance;

public:
    Settings();
    static Settings* Shared();

    void Save();
    void Load();
    void ResetToDefault();

    int window_width;
    int window_height;
    bool fullscreen;
    float font_scale;
    bool show_fps;

};

#endif //SIMULATOR_SETTINGS_H
