#pragma once

#include <rokunet/Http/Request.h>

#include <string>
#include <unordered_map>

#include <iostream>

namespace GemTracker {

/**
 * Forward declarations.
 */
class Route;

namespace Http {

class Request : public rokunet::Http::Request {
public:
    class Factory;

    /**
     * Needs to exist for overriden factory;
     */
    Request(
        std::string body,
        std::unordered_map<std::string, std::string> headers,
        std::string host,
        std::string location,
        Method method,
        rokunet::Http::Version version
    );

    /**
     * Setter for route.
     */
    void setRoute(Route* route) noexcept {
        createParams(route);
    }

    /**
     * Getter for params.
     */
    const std::unordered_map<std::string, std::string>&
    getParams() const noexcept {
        return params;
    }

private:
    void createParams(Route* route);

    std::unordered_map<std::string, std::string> params;
};

class Request::Factory : public rokunet::Http::Request::Factory {
public:
    // Not calling parent constructor.
    using rokunet::Http::Request::Factory::Factory;

    Request build() const {
        return Request(body, headers, host, location, method, *version);
    }
};

} // namespace Http
} // namespace GemTracker

