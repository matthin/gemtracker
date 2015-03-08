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
        "gem INTEGER NOT NULL, "
        "downloads INTEGER NOT NULL, "
        "date DATE DEFAULT(date('now')) NOT NULL, "
        "CONSTRAINT uniq UNIQUE(gem, date))"
    );

    saveDailies();
}

void Store::saveDailies() {
    for (auto gem : gems) {
        // Save all gems which don't exist yet.
        // TODO - Batch into groups of 500 (SQLite's limit)
        db.exec("INSERT OR IGNORE INTO gem(name) VALUES('" + gem  + "')");

        SQLite::Statement gemIDQuery(
            db,
            "SELECT id FROM gem WHERE name = ? LIMIT 1"
        );
        gemIDQuery.bind(1, gem);
        gemIDQuery.executeStep();
        const int gemID = gemIDQuery.getColumn(0);

        const auto downloads =
            client.getDownloads(gem, std::string("0.0.1")).total;
        SQLite::Statement dailyQuery(
            db,
            "Insert OR IGNORE INTO daily(gem, downloads) VALUES(?, ?)"
        );
        dailyQuery.bind(1, gemID);
        dailyQuery.bind(2, std::to_string(downloads));
        dailyQuery.executeStep();
    }
}

} // namespace GemTracker

