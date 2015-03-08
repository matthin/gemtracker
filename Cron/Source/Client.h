#pragma once

#include <string>
#include <SFML/Network.hpp>
#include <unordered_map>
#include <vector>
#include "json/json.h"

namespace GemTracker {

struct GemInfo{
    struct Dependency {
        Dependency(const std::string name, const std::string requirements)
                : name(name), requirements(requirements) {}
        const std::string name;
        const std::string requirements;
    };

    GemInfo(const std::string name, const int downloads,
            const std::string version, const int versionDownloads,
            const std::string authors, const std::string info,
            const std::string projectURI, const std::string gemURI,
            const std::string homepageURI, const std::string wikiURI,
            const std::string documentationURI,
            const std::string sourceCodeURI,
            const std::string bugTrackerURI,
            const std::unordered_map<std::string,
                                     std::vector<Dependency>> dependencies)
            : name(name), downloads(downloads), version(version),
            versionDownloads(versionDownloads), authors(authors), info(info),
            projectURI(projectURI), gemURI(gemURI), homepageURI(homepageURI),
            wikiURI(wikiURI), documentationURI(documentationURI),
            sourceCodeURI(sourceCodeURI), bugTrackerURI(bugTrackerURI),
            dependencies(dependencies) {}
    const std::string name;
    const int downloads;
    const std::string version;
    const int versionDownloads;
    const std::string authors;
    const std::string info;
    const std::string projectURI;
    const std::string gemURI;
    const std::string homepageURI;
    const std::string wikiURI;
    const std::string documentationURI;
    const std::string sourceCodeURI;
    const std::string bugTrackerURI;
    const std::unordered_map<std::string,
                             std::vector<Dependency>> dependencies;
};

struct Downloads {
    Downloads(const int version, const int total)
            : version(version), total(total) {}
    const int version;
    const int total;
};

class Client {
public:
    Client();

    GemInfo getGemInfo(const std::string& gemName);

    Downloads getDownloads(
        const char* gemName, const char* gemVersion
    );
    Downloads getDownloads(
        const std::string& gemName, const std::string& gemVersion
    );

private:
    static Json::Value initRoot(sf::Http::Response response) {
        Json::Value root;
        Json::Reader reader;
        reader.parse(response.getBody(), root);
        return root;
    }

    static constexpr char baseURL[] = "http://rubygems.org/";

    std::vector<GemInfo::Dependency>
    parseDependencies(const Json::Value& dependencies);
};

} // namespace GemTracker

