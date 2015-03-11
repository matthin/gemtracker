#include "RouteManager.h"

#include <iostream>
#include <string>
#include "GemController.h"

namespace GemTracker {

RouteManager::RouteManager() : routes(initRoutes()) {
    listener.listen(8080);
    while (true) {
        sf::TcpSocket client;
        listener.accept(client);

        std::string message;
        while (true) {
            char buffer[1024];
            std::size_t received;
            client.receive(buffer, sizeof(buffer), received);
            message.append(buffer, received);
            if (received < sizeof(buffer)) {
                break;
            }
        }
        routeRequest(Http::Request(message));
        // Only serve one request before cloesing, just for testing.
        break;
    }
}

void RouteManager::routeRequest(const Http::Request& request) noexcept {
    for (const Route route : routes) {
        if (request.headers.at("location").find(route.location) != std::string::npos) {
            route.handler();
        }
    }
}

std::vector<RouteManager::Route> RouteManager::initRoutes() noexcept {
    return std::vector<Route> {{
        {Route("/gems/index.json", GemController::index)}
    }};
}

} // namespace GemTracker

