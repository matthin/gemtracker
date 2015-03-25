#pragma once

#include "Http/Response.h"
#include "Http/Request.h"
#include <functional>
#include <regex>
#include <string>
#include <vector>

namespace GemTracker {

/**
 * Attaches a specific method to a UPL pattern.
 * Example: GemController::index is attached to "/gem/index.json"
 */
class Route {
// Just for private structs.
private:
    struct URLParameter {
        URLParameter(const std::string name, const unsigned int startPosition)
            : name(name), startPosition(startPosition) {}
        const std::string name;
        const unsigned int startPosition;
    };

public:
    enum Method {
        Get, Post
    };

    typedef std::function<void(const Http::Request& request,
                               Http::Response* response)> Handler;

    Route(Method method, std::string location, Handler handler);

    const std::vector<URLParameter> params;
    const Method method;
    const std::regex location;
    const Handler handler;

    bool isMatch(const std::string& methodString,
                 const std::string& location) const noexcept;

    bool isMatch(const Method method,
                 const std::string& location) const noexcept;

private:
    std::regex toRegex(std::string location) const noexcept;

    /**
     * Replaces each URL parameter with the proper regex.
     * Each parameter must be within two forward slashes.
     * @param location String representation of URL.
     * @code replaceParams("/gem/:id/show.json")
     */
    void replaceParams(std::string* location) const noexcept;

    /**
     * Used in the initialization list to initialize params.
     * @return vector containing each parameter.
     */
    std::vector<URLParameter>
    initParams(const std::string& location) const noexcept;
};

} // namespace GemTracker

