//
// world.cpp
// Created by TheFatNinja 
// 23-01-2020
//

#include "world.h"

#include <utility>

World::World() {
    _id = 0;
    _width = 0;
    _height = 0;
}

World::World(uint32_t id, std::string name, uint32_t width, uint32_t height) : _id(id), _name(std::move(name)), _width(width), _height(height) {

}

uint32_t World::ID() {
    return _id;
}

std::string World::Name() {
    return _name;
}

uint32_t World::Width() {
    return _width;
}

uint32_t World::Height() {
    return _height;
}

void World::setName(std::string name) {
    _name = std::move(name);
}

void World::setWidth(uint32_t width) {
    _width = width;
}

void World::setHeight(uint32_t height) {
    _height = height;
}

// TODO: HERE!!!!!!!
