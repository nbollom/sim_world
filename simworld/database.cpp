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
#include "world.h"

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

    std::shared_ptr<Query> query = PrepareQuery("SELECT Name, Version FROM _Types_");
    while (query->Next()) {
        std::string name = query->GetString(0);
        int version = query->GetInt(1);
        _type_registry[name] = version;
    }
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
    // Run all updates in a transaction
    ExecStatement("BEGIN TRANSACTION;");

    try {
        CheckUpdateType<Material>();
        CheckUpdateType<WorldType>();
        CheckUpdateType<World>();
    }
    catch (std::exception &error) {
        // If there was an error then rollback the updates and rethrow exception
        ExecStatement("ROLLBACK TRANSACTION;");
        throw;
    }
    // all went well so commit the transaction
    ExecStatement("COMMIT TRANSACTION;");
}

template <typename T>
void Database::CheckUpdateType() {
    std::string type_name = T::GetClassName();
    int current_version = T::GetCurrentVersion();
    int db_version = _type_registry[type_name];
    if (current_version != db_version) {
        T::UpdateInDB(this, db_version);
        UpdateTypeVersion(type_name, current_version);
    }
}

void Database::UpdateTypeVersion(const std::string& type_name, int version) {
    int old_version = _type_registry[type_name];
    _type_registry[type_name] = version;
    std::shared_ptr<Query> query;
    if (old_version == 0) {
        query = PrepareQuery("INSERT INTO _Types_ (Name, Version) VALUES(?, ?);");
    }
    else {
        query = PrepareQuery("UPDATE _Types_ SET Version = ? WHERE Name = ?");
    }
    query->BindString(1, type_name);
    query->BindInt(2, version);
    query->Next();
}

std::shared_ptr<Query> Database::PrepareQuery(const std::string &sql) {
    sqlite3_stmt *statement;
    sqlite3_prepare(_db, sql.c_str(), sql.length(), &statement, nullptr);
    return std::make_shared<Query>(statement);
}

int Database::ExecStatement(const std::string &sql) {
    auto query = PrepareQuery(sql);
    query->Next();
    int result = query->GetInt(0);
    return result;
}
