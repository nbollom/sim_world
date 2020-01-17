//
// query.h
// Created by TheFatNinja 
// 16-01-2020
//

#ifndef SIMULATOR_QUERY_H
#define SIMULATOR_QUERY_H

#include <sqlite3.h>

class Query {

private:
    sqlite3_stmt *_statement;
    bool _done;

public:
    explicit Query(sqlite3_stmt *statement);
    ~Query();

    // TODO: Bind methods

    bool Next();
    bool IsDone();
    void Reset();

    int GetInt(int column);
};

#endif //SIMULATOR_QUERY_H
