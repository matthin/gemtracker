#pragma once

#include "Controller.h"
#include <rokunet/Http/Response.h>
#include "Http/Request.h"

namespace GemTracker {

class GemController : public Controller {
public:        
    static void index(
        const Http::Request& request,
        rokunet::Http::Response::Builder* response
    );
    static void show(
        const Http::Request& request,
        rokunet::Http::Response::Builder* response
    );
};

} // namespace GemTracker

