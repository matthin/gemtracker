#include "Client.h"

namespace GemTracker {

constexpr char Client::baseURL[];

Client::Client() {
    
}

GemInfo
Client::getGemInfo(const std::string& gemName) {
    sf::Http http(baseURL);
    const sf::Http::Request request(
        "/api/v1/gems/" + gemName + ".json"
    );
    const auto response = http.sendRequest(request);
    const auto root = initRoot(response);

    std::unordered_map<std::string,
                       std::vector<GemInfo::Dependency>> dependencies;
    dependencies["development"] = parseDependencies(
        root["dependencies"]["development"]
    );
    dependencies["runtime"] = parseDependencies(
        root["dependencies"]["runtime"]
    );

    return GemInfo(
        root["name"].asString(),
        root["downloads"].asInt(),
        root["version"].asString(),
        root["versionDownloads"].asInt(),
        root["authors"].asString(),
        root["info"].asString(),
        root["projectURI"].asString(),
        root["gemURI"].asString(),
        root["homepageURI"].asString(),
        root["wikiURI"].asString(),
        root["documentationURI"].asString(),
        root["sourceCodeURI"].asString(),
        root["bugtrackerURI"].asString(),
        dependencies
    );
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

std::vector<GemInfo::Dependency>
Client::parseDependencies(const Json::Value& dependencies) {
    std::vector<GemInfo::Dependency> parsedDependencies;
    for (const auto dependency : dependencies) {
        parsedDependencies.push_back(
            GemInfo::Dependency(dependency["name"].asString(),
                                dependency["requirements"].asString())
        );
    }
    return parsedDependencies;
}

} // namespace GemTracker

