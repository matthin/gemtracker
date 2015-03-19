#pragma once

#include <SFML/Network.hpp>
#include "Http/Response.h"
#include "Http/Request.h"
#include <functional>
#include <regex>
#include <vector>

namespace GemTracker {

class RouteManager {
public:
    RouteManager();

private:
    sf::TcpListener listener;

    Http::Request getRequest(sf::TcpSocket* client);

    struct Route {
        enum Method {
            Get, Post
        };
        typedef std::function<void(const Http::Request& request,
                                         Http::Response* response)> Handler;
        Route(const Method method, const std::string location,
              const Handler handler)
                : method(method), location(toRegex(location)),
                handler(handler) {}
        const Method method;
        const std::regex location;
        const Handler handler;

        bool isMatch(const std::string& methodString,
                     const std::string& location) const noexcept {
            Method method;
            if (methodString == "GET") {
                method = Get;
            } else if (methodString == "POST") {
                method = Post;
            }
            return isMatch(method, location);
        }

        bool isMatch(const Method method,
                     const std::string& location) const noexcept {
            if (this->method == method &&
                    std::regex_search(location, this->location)) {
                return true;
            } else {
                return false;
            }
        }

    private:
        std::regex toRegex(std::string location) {
            std::string::size_type position = -2;
            while (true) {
                position = location.find("/", position + 2);
                if (position != std::string::npos) {
                    location.insert(position, "\\");
                } else {
                    break;
                }
            }
            return std::regex(location);
        }
    };
    const std::vector<Route> routes;

    inline void routeRequest(
        sf::TcpSocket* client, const Http::Request& request
    ) noexcept;
    static inline std::vector<Route> initRoutes() noexcept;
};

} // namespace GemTracker

