#include "Route.h"

namespace GemTracker {

Route::Route(const rokunet::Http::Request::Method method,
             const std::string location,
             const Handler handler)
        : method(method), location(toRegex(location)),
        handler(handler), params(initParams(location)) {}

bool Route::isMatch(const rokunet::Http::Request::Method method,
                    const std::string& location) const noexcept {
    if (this->method == method &&
            std::regex_search(location, this->location)) {
        return true;
    } else {
        return false;
    }
}

std::regex Route::toRegex(std::string location) const noexcept {
    replaceParams(&location);

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

void Route::replaceParams(std::string* location) const noexcept {
    for (const auto param : params) {
        const auto nextSlashPosition = location->find('/', param.startPosition);
        // A forward slash should always be found, but checking just in case.
        if (nextSlashPosition != std::string::npos) {
            const auto length = nextSlashPosition - param.startPosition;
            location->erase(param.startPosition, length);
            location->insert(param.startPosition, "[^/]+");
        }
    }
}

std::vector<Route::URLParameter>
Route::initParams(const std::string& location) const noexcept {
    std::vector<URLParameter> params;

    std::string::size_type nextSlashPosition = 0;
    while (true) {
        const auto idPosition = location.find(":", nextSlashPosition);
        if (idPosition != std::string::npos) {
            nextSlashPosition = location.find("/", idPosition);
            if (nextSlashPosition != std::string::npos) {
                const auto length = nextSlashPosition - idPosition - 1;

                // Have to add one so the : is skipped.
                const auto paramName = location.substr(
                    idPosition + 1, length
                );
                params.push_back(
                    URLParameter(paramName, idPosition)
                );
            }

            //std::cout << 't';
        } else {
            break;
        }
    }

    return params;
}

} // namespace GemTracker

