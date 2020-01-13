//
// Created by Nathan Bollom on 13/1/20.
//

#ifndef SIMULATOR_COMPONENTS_H
#define SIMULATOR_COMPONENTS_H

#include <cstdint>

struct Material {
    uint32_t type;
    explicit Material(uint32_t type = 0) : type(type) {}
};

struct Stackable {
    uint32_t count;
    uint32_t max_count;
    explicit Stackable(uint32_t count, uint32_t max_count) : count(count), max_count(max_count) {}
};

struct Block {
    uint32_t type;
    uint32_t gives_material;
    explicit Block(uint32_t type, uint32_t gives_material) : type(type), gives_material(gives_material) {}
};

struct Position {
    float x, y;
    explicit Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

#endif //SIMULATOR_COMPONENTS_H
