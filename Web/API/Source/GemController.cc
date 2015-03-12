#include "GemController.h"

#include <iostream>

namespace GemTracker {

void GemController::index(const Http::Request& request,
                                Http::Response* response) {
    std::cout << "hit" << std::endl;
}

} // namespace GemTracker

