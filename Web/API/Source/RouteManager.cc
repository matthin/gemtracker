#include "RouteManager.h"

#include <string>
#include <memory>
#include <regex>
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
    for (const Route route : routes) {
        if (std::regex_search(request.headers.at("location"),
                              std::regex(route.location))) {
            auto response = new Http::Response;
            route.handler(request, response);

            auto responseString = response->asString();
            client->send(responseString.c_str(), responseString.size());
            client->disconnect();

            delete response;
        }
    }
}

std::vector<RouteManager::Route> RouteManager::initRoutes() noexcept {
    return std::vector<Route> {{
        {Route("\\/gems\\/index.json", GemController::index)},
        {Route("^\\/gem\\/[0-9]+\\/show.json$", GemController::show)}
    }};
}

} // namespace GemTracker

