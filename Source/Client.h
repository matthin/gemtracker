#pragma once

#include <string>
#include <SFML/Network.hpp>
#include "json/json.h"

namespace GemTracker {

struct Downloads {
    Downloads(const int version, const int total)
            : version(version), total(total) {}
    const int version;
    const int total;
};

class Client {
public:
    Client();

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
};

} // namespace GemTracker

