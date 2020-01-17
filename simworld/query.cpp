//
// query.cpp
// Created by TheFatNinja 
// 16-01-2020
//

#include "query.h"
#include <stdexcept>
#include <thread>
#include <chrono>

Query::Query(sqlite3_stmt *statement) : _statement(statement), _done(false) {

}

Query::~Query() {
    sqlite3_finalize(_statement);
}

bool Query::Next() {
    if (_done) {
        throw std::runtime_error("Query exhausted");
    }
    // TODO: sqlite step logic
    int result = sqlite3_step(_statement);
    while (result == SQLITE_BUSY) {
        // Should not be needed, but in case of a db lock...
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
        result = sqlite3_step(_statement);
    }
    if (result == SQLITE_ERROR || result == SQLITE_MISUSE) {
        sqlite3 *db = sqlite3_db_handle(_statement);
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    _done = (result == SQLITE_DONE);
    return !_done;
}

bool Query::IsDone() {
    return _done;
}

void Query::Reset() {
    sqlite3_reset(_statement);
    _done = false;
}

int Query::GetInt(int column) {
    return sqlite3_column_int(_statement, column);
}
