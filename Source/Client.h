#pragma once

#include <string>
#include <unordered_map>
#include <SFML/Network.hpp>
#include "json/json.h"

class Client {
public:
    Client();

    std::unordered_map<std::string, unsigned int> getDownloads(
        const char* gemName, const char* gemVersion
    );
    std::unordered_map<std::string, unsigned int> getDownloads(
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

