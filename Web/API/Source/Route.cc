#include "Route.h"

namespace GemTracker {

Route::Route(const Method method, const std::string location,
             const Handler handler)
        : method(method), location(toRegex(location)),
        handler(handler) {}

bool Route::isMatch(const std::string& methodString,
                    const std::string& location) const noexcept {
    Method method;
    if (methodString == "GET") {
        method = Get;
    } else if (methodString == "POST") {
        method = Post;
    }
    return isMatch(method, location);
}

bool Route::isMatch(const Method method,
                    const std::string& location) const noexcept {
    if (this->method == method &&
            std::regex_search(location, this->location)) {
        return true;
    } else {
        return false;
    }
}

std::regex Route::toRegex(std::string location) const {
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

} // namespace GemTracker

