#pragma once

#include <rokunet/Socket.h>
#include "Http/Request.h"
#include "Route.h"
#include <vector>

namespace GemTracker {

class Router {
public:
    Router();

private:
    Http::Request getRequest(rokunet::Socket* client);
 
    const std::vector<Route> routes;

    inline void routeRequest(
        rokunet::Socket* client, Http::Request* request
    ) noexcept;
    static inline std::vector<Route> initRoutes() noexcept;
};

} // namespace GemTracker

