//
// query.h
// Created by TheFatNinja 
// 16-01-2020
//

#ifndef SIMULATOR_QUERY_H
#define SIMULATOR_QUERY_H

#include <sqlite3.h>
#include <string>

class Query {

private:
    sqlite3_stmt *_statement;
    bool _done;

public:
    explicit Query(sqlite3_stmt *statement);
    ~Query();

    void BindDouble(int index, double value);
    void BindInt(int index, int value);
    void BindInt64(int index, long long int value);
    void BindNull(int index);
    void BindString(int index, const std::string& value);
    void BindBlob(int index, const void *data, size_t size);

    bool Next();
    bool IsDone();
    void Reset();

    double GetDouble(int column);
    int GetInt(int column);
    long long int GetInt64(int column);
    std::string GetString(int column);
    void GetBlob(int column, void **data_ptr, size_t *length);
};

#endif //SIMULATOR_QUERY_H
