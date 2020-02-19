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

void World::Save(Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    Query *query;
    if (_id == 0) {
        query = db->PrepareQuery("INSERT INTO World (Name, Width, Height) VALUES (?, ?, ?);");
        query->BindString(1, _name);
        query->BindInt(2, _width);
        query->BindInt(3, _height);
    }
    else {
        query = db->PrepareQuery("UPDATE World SET Name = ?, Width = ?, Height = ? WHERE ID = ?;");
        query->BindString(1, _name);
        query->BindInt(2, _width);
        query->BindInt(3, _height);
        query->BindInt(4, _id);
    }
    query->Next();
    delete query;
}

World * World::Load(uint32_t id, Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    Query *query = db->PrepareQuery("SELECT Name, Width, Height FROM World WHERE ID = ?;");
    query->BindInt(1, id);
    query->Next();
    std::string name = query->GetString(0);
    uint32_t width = query->GetInt(1);
    uint32_t height = query->GetInt(2);
    delete query;
    return new World(id, name, width, height);
}

void World::Delete(Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    Query *query = db->PrepareQuery("DELETE FROM World WHERE ID = ?;");
    query->BindInt(1, _id);
    query->Next();
    delete query;
}

std::string World::GetClassName() {
    return "World";
}

int World::GetCurrentVersion() {
    return 1;
}

void World::UpdateInDB(Database *db, int db_version) {
    if (db_version < 1) {
        db->ExecStatement("CREATE TABLE IF NOT EXISTS World ("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "Name TEXT, "
                          "Width INTEGER, "
                          "Height INTEGER);"
        );
    }
}
