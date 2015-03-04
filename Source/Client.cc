#include "Client.h"

namespace GemTracker {

constexpr char Client::baseURL[];

Client::Client() {
    
}

Downloads
Client::getDownloads(const char* gemName, const char* gemVersion) {
    return getDownloads(std::string(gemName), std::string(gemVersion));
}

Downloads
Client::getDownloads(const std::string& gemName,
                     const std::string& gemVersion) {
    sf::Http http(baseURL);
    const sf::Http::Request request(
        "/api/v1/downloads/" + gemName + "-" + gemVersion + ".json"
    );
    const auto response = http.sendRequest(request);
    const auto root = initRoot(response);
    return Downloads(
        root["version_downloads"].asInt(),
        root["total_downloads"].asInt()
    );
}

} // namespace GemTracker

