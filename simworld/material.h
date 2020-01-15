//
// Created by Nathan Bollom on 15/1/20.
//

#ifndef SIMULATOR_MATERIAL_H
#define SIMULATOR_MATERIAL_H

#include <cstdint>
#include <string>

class Material {

private:
    uint32_t _id;
    std::string _name;
    std::string _description;

    static bool db_checked;

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
    void Save();
    static Material* Load(uint32_t id);

private:
    static void CheckAndUpdateDBTable();

};

#endif //SIMULATOR_MATERIAL_H
