#pragma once

#include <SFML/Network.hpp>
#include "Http/Request.h"
#include "Route.h"
#include <vector>

namespace GemTracker {

class RouteManager {
public:
    RouteManager();

private:
    Http::Request getRequest(sf::TcpSocket* client);
 
    const std::vector<Route> routes;

    inline void routeRequest(
        sf::TcpSocket* client, Http::Request* request
    ) noexcept;
    static inline std::vector<Route> initRoutes() noexcept;
};

} // namespace GemTracker

