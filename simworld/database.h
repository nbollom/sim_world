//
// database.h
// Created by TheFatNinja 
// 16-01-2020
//

#ifndef SIMULATOR_DATABASE_H
#define SIMULATOR_DATABASE_H

#include <sqlite3.h>
#include <map>
#include <string>
#include <memory>
#include "query.h"

class Database {

private:
    static Database* _shared_instance;
    sqlite3 *_db;
    std::map<std::string, int> _type_registry;

public:
    explicit Database(const std::string& db_file);
    static Database *Shared();
    void Close();

    void InitializeDatabase();
    template <typename T>
    void CheckUpdateType();

private:
    void UpdateTypeVersion(const std::string& type_name, int version);

public:
    std::shared_ptr<Query> PrepareQuery(const std::string &sql);
    int ExecStatement(const std::string &sql);
};

#endif //SIMULATOR_DATABASE_H
