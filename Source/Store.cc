#include "Store.h"

#include <iostream>

namespace GemTracker {

Store::Store(const std::vector<std::string> gems) : gems(gems) {
    saveDailies();
}

void Store::saveDailies() {
    // Placeholder untill some database is setup
    for (auto gem : gems) {
        
    }
}

} // namespace GemTracker

