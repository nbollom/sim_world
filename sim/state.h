//
// Created by Nathan Bollom on 23/1/20.
//

#ifndef SIMULATOR_STATE_H
#define SIMULATOR_STATE_H

struct State {
    int width = 1270;
    int height = 720;
    double previousTime = 0;
    int frameCount = 0;
    int fps = 0;
    bool should_quit = false;
};

#endif //SIMULATOR_STATE_H
