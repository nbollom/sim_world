//
// world.h
// Created by TheFatNinja 
// 23-01-2020
//

#ifndef SIMULATOR_WORLD_H
#define SIMULATOR_WORLD_H

#include <string>
#include "database.h"

class World {

private:
    int _id;
    std::string _name;
    int _width;
    int _height;
    int _type;

public:
    World();
    World(int id, std::string name, int width, int height, int type);

};

#endif //SIMULATOR_WORLD_H
