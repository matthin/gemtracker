#include "RouteManager.h"

#include <algorithm>
#include <string>
#include <memory>
#include "GemController.h"

namespace GemTracker {

RouteManager::RouteManager() : routes(initRoutes()) {
    listener.listen(8080);
    while (true) {
        std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);
        listener.accept(*client);
        routeRequest(client.get(), getRequest(client.get()));
        // Only serve one request before cloesing, just for testing.
        break;
    }
}

Http::Request RouteManager::getRequest(sf::TcpSocket* client) {
    std::string message;
    while (true) {
        char buffer[1024];
        std::size_t received;
        client->receive(buffer, sizeof(buffer), received);
        message.append(buffer, received);
        if (received < sizeof(buffer)) {
            break;
        }
    }
    return Http::Request(message);
}

void RouteManager::routeRequest(sf::TcpSocket* client,
                                const Http::Request& request) noexcept {
    const auto it = std::find_if(routes.begin(), routes.end(),
                             [request](const Route& route) -> bool {
        return std::regex_search(request.headers.at("location"),
                                 route.location);
    });
    if (it != routes.end()) {
        const auto route = *it;
 
        std::unique_ptr<Http::Response> response(new Http::Response);
        route.handler(request, response.get());

        const auto responseString = response->asString();
        client->send(responseString.c_str(), responseString.size());
        client->disconnect();
    }
}

std::vector<RouteManager::Route> RouteManager::initRoutes() noexcept {
    return std::vector<Route> {{
        {Route("\\/gems\\/index.json", GemController::index)},
        {Route("^\\/gem\\/[0-9]+\\/show.json$", GemController::show)}
    }};
}

} // namespace GemTracker

