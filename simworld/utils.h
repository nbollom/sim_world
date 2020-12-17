//
// Created by Nathan Bollom on 8/12/20.
//

#ifndef SIMULATOR_UTILS_H
#define SIMULATOR_UTILS_H

template <class T>
inline T MAX(T a, T b) {
    return a > b ? a : b;
}

template <class T>
inline T MIN(T a, T b) {
    return a < b ? a : b;
}

#endif //SIMULATOR_UTILS_H
