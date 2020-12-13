//
// Created by Nathan Bollom on 15/1/20.
//

#ifndef SIMULATOR_MATERIAL_H
#define SIMULATOR_MATERIAL_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include "database.h"

class Material {

private:
    uint32_t _id;
    std::string _name;
    std::string _description;

public:
    Material();
    Material(uint32_t id, std::string name, std::string description);

    // Getters
    uint32_t ID();
    std::string Name();
    std::string Description();

    // Setters
    void setName(std::string name);
    void setDescription(std::string description);

    // DB
    void Save(Database *db = nullptr);
    void Delete(Database *db = nullptr);
    static std::shared_ptr<Material> Load(uint32_t id, Database *db = nullptr);
    static std::vector<std::shared_ptr<Material>> LoadAll(Database *db = nullptr);
    static std::string GetClassName();
    static int GetCurrentVersion();
    static void UpdateInDB(Database *db, int db_version);

};

#endif //SIMULATOR_MATERIAL_H
