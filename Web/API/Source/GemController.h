#pragma once

#include "Controller.h"
#include "Http/Response.h"
#include "Http/Request.h"

namespace GemTracker {

class GemController : public Controller {
public:        
    static void index(const Http::Request& request, Http::Response* response);
};

} // namespace GemTracker

