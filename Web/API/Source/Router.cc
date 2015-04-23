#include "Router.h"

#include <rokunet/Listener.h>
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>
#include "GemController.h"

namespace GemTracker {

Router::Router() : routes(initRoutes()) {
    rokunet::Listener listener;
    listener.listen(8080);
    while (true) {
        std::unique_ptr<rokunet::Socket> client(new rokunet::Socket);
        listener.accept(client.get());

        auto request = getRequest(client.get());
        routeRequest(client.get(), &request);
    }
}

Http::Request Router::getRequest(rokunet::Socket* client) {
    std::ostringstream rawRequest;
    for (int i = 1; i < 11; ++i) {
        rawRequest << client->receive(1024);
        if (rawRequest.str().size() / i != 1024) {
            break;
        }
    }

    return Http::Request::Factory(rawRequest.str()).build();
}

void Router::routeRequest(rokunet::Socket* client,
                          Http::Request* request) noexcept {
    const auto it = std::find_if(routes.begin(), routes.end(),
                                [request](const Route& route) -> bool {
        return route.isMatch(request->method, request->location);
    });
    if (it != routes.end()) {
        auto route = *it;

        request->setRoute(&route);
 
        std::unique_ptr<rokunet::Http::Response::Builder> responseBuilder(
            new rokunet::Http::Response::Builder
        );
        route.handler(*request, responseBuilder.get());

        // Enable CORS for every domain.
        //response->headers["Access-Control-Allow-Origin"] = "*";

        client->send(responseBuilder->build().prepare());
    }

    client->disconnect();
}

std::vector<Route> Router::initRoutes() noexcept {
    return std::vector<Route> {{
        {Route(
            rokunet::Http::Request::Method::Get,
            "^/gems/index.json$",
            GemController::index
        )},
        {Route(
            rokunet::Http::Request::Method::Get,
            "^/gem/:id/show.json$",
            GemController::show
        )}
    }};
}

} // namespace GemTracker

