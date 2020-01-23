//
// world.cpp
// Created by TheFatNinja 
// 23-01-2020
//

#include "world.h"

#include <utility>

World::World() {

}

World::World(int id, std::string name, int width, int height, int type) : _id(id), _name(std::move(name)), _width(width), _height(height), _type(type) {

}
