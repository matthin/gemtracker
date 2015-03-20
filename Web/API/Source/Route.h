#pragma once

#include "Http/Response.h"
#include "Http/Request.h"
#include <functional>
#include <regex>
#include <string>

namespace GemTracker {

class Route {
public:
    enum Method {
        Get, Post
    };
    typedef std::function<void(const Http::Request& request,
                               Http::Response* response)> Handler;
    Route(const Method method, const std::string location,
          const Handler handler);
    const Method method;
    const std::regex location;
    const Handler handler;

    bool isMatch(const std::string& methodString,
                 const std::string& location) const noexcept;

    bool isMatch(const Method method,
                 const std::string& location) const noexcept;

private:
    std::regex toRegex(std::string location) const;
};

} // namespace GemTracker

