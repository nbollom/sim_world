//
// world_type.cpp
// Created by TheFatNinja 
// 24-01-2020
//

#include "world_type.h"

#include <utility>

WorldType::WorldType() {
    _id = 0;
    _percent_land = 0;
    _avg_land_size = 0;
    _rivers = 0;
    _mountains = 0;
}

WorldType::WorldType(uint32_t id, std::string name, std::string description, uint8_t percent_land, uint8_t avg_land_size, uint8_t rivers, uint8_t mountains) :
    _id(id), _name(std::move(name)), _description(std::move(description)), _percent_land(percent_land), _avg_land_size(avg_land_size), _rivers(rivers), _mountains(mountains) {
}

uint32_t WorldType::ID() {
    return _id;
}

std::string WorldType::Name() {
    return _name;
}

std::string WorldType::Description() {
    return _description;
}

uint8_t WorldType::PercentLand() {
    return _percent_land;
}

uint8_t WorldType::AvgLandSize() {
    return _avg_land_size;
}

uint8_t WorldType::Rivers() {
    return _rivers;
}

uint8_t WorldType::Mountains() {
    return _mountains;
}

void WorldType::setName(std::string name) {
    _name = std::move(name);
}

void WorldType::setDescription(std::string description) {
    _description = std::move(description);
}

void WorldType::setPercentLand(uint8_t percent_land) {
    _percent_land = percent_land;
}

void WorldType::setAvgLandSize(uint8_t avg_land_size) {
    _avg_land_size = avg_land_size;
}

void WorldType::setRivers(uint8_t rivers) {
    _rivers = rivers;
}

void WorldType::setMountains(uint8_t mountains) {
    _mountains = mountains;
}

void WorldType::Save(Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    std::shared_ptr<Query> query;
    if (_id == 0) {
        query = db->PrepareQuery("INSERT INTO WorldType (Name, Description, PercentLand, AvgLandSize, Rivers, Mountains) VALUES (?, ?, ?, ?, ?, ?);");
        query->BindString(1, _name);
        query->BindString(2, _description);
        query->BindInt(3, _percent_land);
        query->BindInt(4, _avg_land_size);
        query->BindInt(5, _rivers);
        query->BindInt(6, _mountains);
    }
    else {
        query = db->PrepareQuery("UPDATE WorldType SET Name = ?, Description = ?, PercentLand = ?, AvgLandSize = ?, Rivers = ?, Mountains = ? WHERE ID = ?;");
        query->BindString(1, _name);
        query->BindString(2, _description);
        query->BindInt(3, _percent_land);
        query->BindInt(4, _avg_land_size);
        query->BindInt(5, _rivers);
        query->BindInt(6, _mountains);
        query->BindInt(7, _id);
    }
    query->Next();
}

void WorldType::Delete(Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    std::shared_ptr<Query> query = db->PrepareQuery("DELETE FROM WorldType WHERE ID = ?;");
    query->BindInt(1, _id);
    query->Next();
}

std::shared_ptr<WorldType> WorldType::Load(uint32_t id, Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    std::shared_ptr<Query> query = db->PrepareQuery("SELECT Name, Description, PercentLand, AvgLandSize, Rivers, Mountains FROM WorldType WHERE ID = ?;");
    query->BindInt(1, id);
    query->Next();
    std::string name = query->GetString(0);
    std::string description = query->GetString(1);
    uint8_t percent_land = query->GetInt(2);
    uint8_t avg_land_size = query->GetInt(3);
    uint8_t rivers = query->GetInt(4);
    uint8_t mountains = query->GetInt(5);
    return std::make_shared<WorldType>(id, name, description, percent_land, avg_land_size, rivers, mountains);
}

std::vector<std::shared_ptr<WorldType>> WorldType::LoadAll(Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    std::vector<std::shared_ptr<WorldType>> types;
    std::shared_ptr<Query> query = db->PrepareQuery("SELECT ID, Name, Description, PercentLand, AvgLandSize, Rivers, Mountains FROM WorldType;");
    while (query->Next()) {
        int id = query->GetInt(0);
        std::string name = query->GetString(1);
        std::string description = query->GetString(2);
        uint8_t percent_land = query->GetInt(3);
        uint8_t avg_land_size = query->GetInt(4);
        uint8_t rivers = query->GetInt(5);
        uint8_t mountains = query->GetInt(6);
        std::shared_ptr<WorldType> type = std::make_shared<WorldType>(id, name, description, percent_land, avg_land_size, rivers, mountains);
        types.push_back(type);
    }
    return types;
}

std::string WorldType::GetClassName() {
    return "WorldType";
}

int WorldType::GetCurrentVersion() {
    return 1;
}

void WorldType::UpdateInDB(Database *db, int db_version) {
    if (db_version < 1) {
        db->ExecStatement("CREATE TABLE IF NOT EXISTS WorldType ("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "Name TEXT, "
                          "Description TEXT, "
                          "PercentLand INTEGER, "
                          "AvgLandSize INTEGER, "
                          "Rivers INTEGER, "
                          "Mountains INTEGER);"
                          );
    }
}
