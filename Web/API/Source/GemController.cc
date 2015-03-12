#include "GemController.h"

namespace GemTracker {

void GemController::index(const Http::Request& request,
                                Http::Response* response) {
    response->headers["Content-Type"] = "application/json";
    response->code = 200;
    response->codeMessage = "OK";
    response->setMessage("Wut up bruv?");
}

} // namespace GemTracker

