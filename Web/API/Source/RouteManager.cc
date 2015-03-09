#include "RouteManager.h"

#include <iostream>
#include <string>
#include "Http/Request.h"
#include "GemController.h"

namespace GemTracker {

RouteManager::RouteManager() {
    GemController gemController;
    controllers.push_back(gemController);

    listener.listen(8080);
    while (true) {
        sf::TcpSocket client;
        listener.accept(client);

        std::string response;
        while (true) {
            char buffer[1024];
            std::size_t received;
            client.receive(buffer, sizeof(buffer), received);
            response.append(buffer, received);
            if (received < sizeof(buffer)) {
                break;
            }
        }
        Http::Request request(response);
        if (request.headers["location"].find("/gems/") != std::string::npos) {
            std::cout << "test" << std::endl;
        }
    }
}

} // namespace GemTracker

