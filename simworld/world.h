//
// world.h
// Created by TheFatNinja 
// 23-01-2020
//

#ifndef SIMULATOR_WORLD_H
#define SIMULATOR_WORLD_H

#include <string>
#include <cstdint>
#include "database.h"

class World {

private:
    uint32_t _id;
    std::string _name;
    uint32_t _width;
    uint32_t _height;

public:
    World();
    World(uint32_t id, std::string name, uint32_t width, uint32_t height);

    // Getters
    uint32_t ID();
    std::string Name();
    uint32_t Width();
    uint32_t Height();

    // Setters
    void setName(std::string name);
    void setWidth(uint32_t width);
    void setHeight(uint32_t height);

    // DB
    void Save(Database *db = nullptr);
    static World* Load(uint32_t id, Database *db = nullptr);
    void Delete(Database *db = nullptr);
    static std::string GetClassName();
    static int GetCurrentVersion();
    static void UpdateInDB(Database *db, int db_version);

};

#endif //SIMULATOR_WORLD_H
