#pragma once

#include <SFML/Network.hpp>
#include "Http/Response.h"
#include "Http/Request.h"
#include <functional>
#include <vector>

namespace GemTracker {

class RouteManager {
public:
    RouteManager();

private:
    sf::TcpListener listener;

    Http::Request getRequest(sf::TcpSocket* client);

    struct Route {
        typedef std::function<void(const Http::Request& request,
                                         Http::Response* response)> Handler;
        Route(const std::string location, const Handler handler)
                : location(location), handler(handler) {}
        const std::string location;
        const Handler handler;
    };
    const std::vector<Route> routes;

    inline void routeRequest(
        sf::TcpSocket* client, const Http::Request& request
    ) noexcept;
    static inline std::vector<Route> initRoutes() noexcept;
};

} // namespace GemTracker

