#include "Client.h"

constexpr char Client::baseURL[];

Client::Client() {
    
}

std::unordered_map<std::string, unsigned int>
Client::getDownloads(const char* gemName, const char* gemVersion) {
    return getDownloads(std::string(gemName), std::string(gemVersion));
}

std::unordered_map<std::string, unsigned int>
Client::getDownloads(const std::string& gemName,
                     const std::string& gemVersion) {
    sf::Http http(baseURL);
    const sf::Http::Request request(
        "/api/v1/downloads/" + gemName + "-" + gemVersion + ".json"
    );
    const auto response = http.sendRequest(request);
    const auto root = initRoot(response);
    return std::unordered_map<std::string, unsigned int> {
        {"versionDownloads", root["version_downloads"].asInt()},
        {"totalDownloads", root["total_downloads"].asInt()}
    };
}

