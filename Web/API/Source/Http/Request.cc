#include "Request.h"

#include <Route.h>

namespace GemTracker {
namespace Http {

Request::Request(const std::string body,
                 const std::unordered_map<std::string, std::string> headers,
                 const std::string host,
                 const std::string location,
                 const Method method,
                 const rokunet::Http::Version version)
        : rokunet::Http::Request(body, headers, host, location, method, version) {}

void Request::createParams(Route* route) {
    for (const auto param : route->params) {
        auto nextSlashPosition = location
                                .find('/', param.startPosition);
        if (nextSlashPosition != std::string::npos) {
            auto length = nextSlashPosition - param.startPosition + 1;
            auto content = location.substr(
                param.startPosition -1, length
            );
            params[param.name] = content;
        }
    }
}

} // namespace Http
} // namespace GemTracker

