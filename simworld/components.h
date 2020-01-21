//
// Created by Nathan Bollom on 13/1/20.
//

#ifndef SIMULATOR_COMPONENTS_H
#define SIMULATOR_COMPONENTS_H

#include <cstdint>

struct MaterialComponent {
    uint32_t type;
    explicit MaterialComponent(uint32_t type = 0) : type(type) {}
};

struct StackableComponent {
    uint32_t count;
    uint32_t max_count;
    explicit StackableComponent(uint32_t count, uint32_t max_count) : count(count), max_count(max_count) {}
};

struct BlockComponent {
    uint32_t type;
    uint32_t gives_material;
    explicit BlockComponent(uint32_t type, uint32_t gives_material) : type(type), gives_material(gives_material) {}
};

struct PositionComponent {
    float x, y;
    explicit PositionComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};

#endif //SIMULATOR_COMPONENTS_H
