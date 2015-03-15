#include "GemController.h"

#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/Database.h>
#include <json/json.h>
#include <string>

namespace GemTracker {

void GemController::index(const Http::Request& request,
                                Http::Response* response) {
    response->headers["Content-Type"] = "application/json";
    response->code = 200;
    response->codeMessage = "OK";

    SQLite::Database db("GemTracker.sqlite3", SQLITE_OPEN_READWRITE);
    SQLite::Statement query(db, "SELECT id FROM gem");

    Json::Value root;
    while (query.executeStep()) {
        root.append(Json::Value(query.getColumn(0).getInt()));
    }
    response->setMessage(root.toStyledString());
}

void GemController::show(const Http::Request& request,
                               Http::Response* response) {
    response->headers["Content-Type"] = "application/json";
    response->code = 200;
    response->codeMessage = "OK";

    SQLite::Database db("GemTracker.sqlite3", SQLITE_OPEN_READWRITE);

    SQLite::Statement query(
        db, "SELECT downloads, date FROM daily WHERE gem = ?"
    );
    // Gem ID is hardcoded in.
    query.bind(1, 1);

    Json::Value root;
    while (query.executeStep()) {
        Json::Value entry;
        entry["downloads"] = query.getColumn(0).getInt();
        entry["date"] = query.getColumn(1).getText();
        root.append(entry);
    }
    response->setMessage(root.toStyledString());
}

} // namespace GemTracker

