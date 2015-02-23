#pragma once

#include <vector>
#include <string>
#include "Client.h"

namespace GemTracker {

class Store {
public:
    Store(const std::vector<std::string> gems);

private:
    const std::vector<std::string> gems;
    Client client;
    void saveDailies();
};

} // namespace GemTracker

