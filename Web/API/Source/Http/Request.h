#pragma once

#include <string>
#include <unordered_map>

namespace GemTracker {

/**
 * Forward declarations.
 */
class Route;

namespace Http {

class Request {
public:
    Request(const std::string& headersString);
    std::unordered_map<std::string, std::string> headers;

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
    inline void parse_headers(const std::string& headers_string);
    void createParams(Route* route);

    std::unordered_map<std::string, std::string> params;
};

} // namespace Http
} // namespace GemTracker

