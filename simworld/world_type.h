//
// world_type.h
// Created by TheFatNinja 
// 24-01-2020
//

#ifndef SIMULATOR_WORLD_TYPE_H
#define SIMULATOR_WORLD_TYPE_H

#include <string>
#include <vector>
#include "database.h"

class WorldType {

private:
    uint32_t _id;
    std::string _name;
    std::string _description;
    uint8_t _percent_land; // global land amount (1-100)
    uint8_t _avg_land_size; // how big the land masses are by average(1-10)
    uint8_t _rivers; // number of rivers on the land
    uint8_t _mountains; // number of maintain ranges

public:
    WorldType();
    WorldType(uint32_t id, std::string name, std::string description, uint8_t percent_land, uint8_t avg_land_size, uint8_t rivers, uint8_t mountains);

    // Getters
    uint32_t ID();
    std::string Name();
    std::string Description();
    uint8_t PercentLand();
    uint8_t AvgLandSize();
    uint8_t Rivers();
    uint8_t Mountains();

    // Setters
    void setName(std::string name);
    void setDescription(std::string description);
    void setPercentLand(uint8_t percent_land);
    void setAvgLandSize(uint8_t avg_land_size);
    void setRivers(uint8_t rivers);
    void setMountains(uint8_t mountains);

    // DB
    void Save(Database *db = nullptr);
    static WorldType* Load(uint32_t id, Database *db = nullptr);
    static std::vector<WorldType*> LoadAll(Database *db = nullptr);
    static std::string GetClassName();
    static int GetCurrentVersion();
    static void UpdateInDB(Database *db, int db_version);

};

#endif //SIMULATOR_WORLD_TYPE_H
