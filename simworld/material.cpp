//
// Created by Nathan Bollom on 15/1/20.
//

#include "material.h"

#include <utility>

Material::Material() {
    _id = 0;
}

Material::Material(uint32_t id, std::string name, std::string description) : _id(id), _name(std::move(name)), _description(std::move(description)) {

}

uint32_t Material::ID() {
    return _id;
}

std::string Material::Name() {
    return _name;
}

std::string Material::Description() {
    return _description;
}

void Material::setName(std::string name) {
    _name = std::move(name);
}

void Material::setDescription(std::string description) {
    _description = std::move(description);
}

void Material::Save(Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    std::shared_ptr<Query> query;
    if (_id == 0) {
        query = db->PrepareQuery("INSERT INTO Material (Name, Description) VALUES (?, ?);");
        query->BindString(1, _name);
        query->BindString(2, _description);
    }
    else {
        query = db->PrepareQuery("UPDATE Material SET Name = ?, Description = ? WHERE ID = ?;");
        query->BindString(1, _name);
        query->BindString(2, _description);
        query->BindInt(3, _id);
    }
    query->Next();
    if (_id == 0) {
        query = db->PrepareQuery("SELECT last_insert_rowid();");
        query->Next();
        _id = query->GetInt(0);
    }
}

void Material::Delete(Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    std::shared_ptr<Query> query = db->PrepareQuery("DELETE FROM Material WHERE ID = ?;");
    query->BindInt(1, _id);
    query->Next();
}

std::shared_ptr<Material> Material::Load(uint32_t id, Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    std::shared_ptr<Query> query = db->PrepareQuery("SELECT Name, Description FROM Material WHERE ID = ?;");
    query->BindInt(1, id);
    query->Next();
    std::string name = query->GetString(0);
    std::string description = query->GetString(1);
    return std::make_shared<Material>(id, name, description);
}

std::vector<std::shared_ptr<Material>> Material::LoadAll(Database *db) {
    if (db == nullptr) {
        db = Database::Shared();
    }
    std::vector<std::shared_ptr<Material>> materials;
    std::shared_ptr<Query> query = db->PrepareQuery("SELECT ID, Name, Description FROM Material;");
    while (query->Next()) {
        int id = query->GetInt(0);
        std::string name = query->GetString(1);
        std::string description = query->GetString(2);
        std::shared_ptr<Material> material = std::make_shared<Material>(id, name, description);
        materials.push_back(material);
    }
    return materials;
}

std::string Material::GetClassName() {
    return "Material";
}

int Material::GetCurrentVersion() {
    return 1;
}

void Material::UpdateInDB(Database *db, int db_version) {
    if (db_version < 1) {
        db->ExecStatement("CREATE TABLE IF NOT EXISTS Material ("
                          "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "Name TEXT, "
                          "Description TEXT);"
                          );
    }
}
