#include "GemController.h"

namespace GemTracker {

void GemController::index(const Http::Request& request,
                                Http::Response* response) {
    response->headers["Content-Type"] = "application/json";
    response->headers["code"] = "200";
    response->headers["codeMessage"] = "OK";
    response->setMessage("Wut up bruv?");
}

} // namespace GemTracker

