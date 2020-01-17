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

void Query::BindDouble(int index, double value) {
    if (sqlite3_bind_double(_statement, index, value) != SQLITE_OK) {
        throw std::runtime_error("Error binding double");
    }
}

void Query::BindInt(int index, int value) {
    if (sqlite3_bind_int(_statement, index, value) != SQLITE_OK) {
        throw std::runtime_error("Error binding integer");
    }
}

void Query::BindInt64(int index, long long value) {
    if (sqlite3_bind_int64(_statement, index, value) != SQLITE_OK) {
        throw std::runtime_error("Error binding 64 bit integer");
    }
}

void Query::BindNull(int index) {
    if (sqlite3_bind_null(_statement, index) != SQLITE_OK) {
        throw std::runtime_error("Error binding NULL");
    }
}

void Query::BindString(int index, const std::string& value) {
    if (sqlite3_bind_text(_statement, index, value.c_str(), value.length(), SQLITE_TRANSIENT) != SQLITE_OK) {
        throw std::runtime_error("Error binding string");
    }
}

void Query::BindBlob(int index, const void *data, size_t size) {
    if (sqlite3_bind_blob(_statement, index, data, size, SQLITE_TRANSIENT) != SQLITE_OK) {
        throw std::runtime_error("Error binding blob");
    }
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

double Query::GetDouble(int column) {
    return sqlite3_column_double(_statement, column);
}

int Query::GetInt(int column) {
    return sqlite3_column_int(_statement, column);
}

long long int Query::GetInt64(int column) {
    return sqlite3_column_int64(_statement, column);
}

std::string Query::GetString(int column) {
    const char *text = reinterpret_cast<const char*>(sqlite3_column_text(_statement, column));
    return std::string(text);
}

void Query::GetBlob(int column, void **data_ptr, size_t *length) {
    const void *data = sqlite3_column_blob(_statement, column);
    *length = sqlite3_column_bytes(_statement, column);
    *data_ptr = malloc(*length);
    memcpy(*data_ptr, data, *length);
}
