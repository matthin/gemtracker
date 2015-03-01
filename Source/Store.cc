#include "Store.h"

#include <iostream>
#include <SQLiteCpp/Statement.h>

namespace GemTracker {

Store::Store(const std::vector<std::string> gems)
        : gems(gems), db("GemTracker.sqlite3",
        SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE) {
    db.exec(
        "CREATE TABLE IF NOT EXISTS gem("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL UNIQUE)"
    );
    db.exec(
        "CREATE TABLE IF NOT EXISTS daily("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "downloads INTEGER NOT NULL, "
        "date DATE DEFAULT(date('now')) NOT NULL)"
    );

    saveDailies();
}

void Store::saveDailies() {
    for (auto gem : gems) {
        // Save all gems which don't exist yet.
        // TODO - Batch into groups of 500 (SQLite's limit)
        db.exec("INSERT OR IGNORE INTO gem(name) VALUES('" + gem  + "')");
    }
}

} // namespace GemTracker

