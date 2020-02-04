//
// database.cpp
// Created by TheFatNinja 
// 16-01-2020
//

#include <stdexcept>
#include "database.h"

// Database Class Imports
#include "material.h"
#include "world_type.h"

Database* Database::_shared_instance = nullptr;

Database::Database(const std::string& db_file) {
    _db = nullptr;
    int success = sqlite3_open(db_file.c_str(), &_db);
    if (success != SQLITE_OK) {
        throw std::runtime_error("Failed to open database");
    }

    ExecStatement("CREATE TABLE IF NOT EXISTS _Types_ ("
                  "Name TEXT PRIMARY KEY, "
                  "Version INTEGER);");

    Query *query = PrepareQuery("SELECT Name, Version FROM _Types_");
    while (query->Next()) {
        std::string name = query->GetString(0);
        int version = query->GetInt(1);
        _type_registry[name] = version;
    }
    delete query;
}

Database * Database::Shared() {
    if (_shared_instance == nullptr) {
        _shared_instance = new Database("sim.data");
    }
    return _shared_instance;
}

void Database::Close() {
    sqlite3_close(_db);
}

void Database::InitializeDatabase() {
    std::string type_name;
    int current_version;
    int db_version;

    // Run all updates in a transaction
    ExecStatement("BEGIN TRANSACTION;");

    try {
        // Material
        type_name = Material::GetClassName();
        current_version = Material::GetCurrentVersion();
        db_version = _type_registry[type_name];
        if (current_version != db_version) {
            Material::UpdateInDB(this, db_version);
            UpdateTypeVersion(type_name, current_version);
        }

        // WorldType
        type_name = WorldType::GetClassName();
        current_version = Material::GetCurrentVersion();
        db_version = _type_registry[type_name];
        if (current_version != db_version) {
            WorldType::UpdateInDB(this, db_version);
            UpdateTypeVersion(type_name, current_version);
        }
    }
    catch (std::exception &error) {
        // If there was an error then rollback the updates and rethrow exception
        ExecStatement("ROLLBACK TRANSACTION;");
        throw;
    }
    // all went well so commit the transaction
    ExecStatement("COMMIT TRANSACTION;");
}

void Database::UpdateTypeVersion(const std::string& type_name, int version) {
    int old_version = _type_registry[type_name];
    _type_registry[type_name] = version;
    Query *query;
    if (old_version == 0) {
        query = PrepareQuery("INSERT INTO _Types_ (Name, Version) VALUES(?, ?);");
    }
    else {
        query = PrepareQuery("UPDATE _Types_ SET Version = ? WHERE Name = ?");
    }
    query->BindString(1, type_name);
    query->BindInt(2, version);
    query->Next();
    delete query;
}

Query * Database::PrepareQuery(const std::string &sql) {
    sqlite3_stmt *statement;
    sqlite3_prepare(_db, sql.c_str(), sql.length(), &statement, nullptr);
    Query *query = new Query(statement);
    return query;
}

int Database::ExecStatement(const std::string &sql) {
    Query *query = PrepareQuery(sql);
    query->Next();
    int result = query->GetInt(0);
    delete query;
    return result;
}
