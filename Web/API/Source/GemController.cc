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
    SQLite::Statement query(db, "SELECT id, name FROM gem");

    Json::Value root;
    while (query.executeStep()) {
        Json::Value entry;
        entry["id"] = query.getColumn(0).getInt();
        entry["name"] = query.getColumn(1).getText();
        root.append(entry);
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
    query.bind(1, request.getParams().at("id"));

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

