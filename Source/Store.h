#pragma once

#include <vector>
#include <string>
#include <SQLiteCpp/Database.h>
#include "Client.h"

namespace GemTracker {

class Store {
public:
    Store(const std::vector<std::string> gems);

private:
    const std::vector<std::string> gems;
    Client client;
    SQLite::Database db;
    void saveDailies();
};

} // namespace GemTracker

