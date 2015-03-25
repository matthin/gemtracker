#include "Router.h"

#include <algorithm>
#include <string>
#include <memory>
#include "GemController.h"

namespace GemTracker {

Router::Router() : routes(initRoutes()) {
    sf::TcpListener listener;
    listener.listen(8080);
    while (true) {
        std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);
        listener.accept(*client);

        auto request = getRequest(client.get());
        routeRequest(client.get(), &request);

        // Only serve one request before closing, just for testing.
        break;
    }
}

Http::Request Router::getRequest(sf::TcpSocket* client) {
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

void Router::routeRequest(sf::TcpSocket* client,
                                Http::Request* request) noexcept {
    const auto it = std::find_if(routes.begin(), routes.end(),
                                [request](const Route& route) -> bool {
        return route.isMatch(request->headers.at("method"),
                             request->headers.at("location"));
    });
    if (it != routes.end()) {
        auto route = *it;

        request->setRoute(&route);
 
        std::unique_ptr<Http::Response> response(new Http::Response);
        route.handler(*request, response.get());

        const auto responseString = response->asString();
        client->send(responseString.c_str(), responseString.size());
    }

    client->disconnect();
}

std::vector<Route> Router::initRoutes() noexcept {
    return std::vector<Route> {{
        {Route(Route::Get, "^/gems/index.json$", GemController::index)},
        {Route(Route::Get, "^/gem/:id/show.json$", GemController::show)}
    }};
}

} // namespace GemTracker

