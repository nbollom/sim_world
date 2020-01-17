//
// database.cpp
// Created by TheFatNinja 
// 16-01-2020
//

#include <stdexcept>
#include "database.h"

Database* Database::_shared_instance = nullptr;

Database::Database(const std::string& db_file) {
    _db = nullptr;
    int success = sqlite3_open(db_file.c_str(), &_db);
    if (success != SQLITE_OK) {
        throw std::runtime_error("Failed to open database");
    }

    ExecStatement("\
CREATE TABLE IF NOT EXISTS _Types_ ( \
Name TEXT, \
Version INTEGER \
);");

    // TODO: populate _type_registry map
    Query *query = PrepareQuery("SELECT Name, Version FROM _Types_");
    while (query->Next()) {
        
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

int Database::GetTypeVersion(const std::string& type_name) {
    return _type_registry[type_name];
}

void Database::UpdateTypeVersion(const std::string& type_name, int version) {
    _type_registry[type_name] = version;
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
