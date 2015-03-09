#pragma once

#include <string>
#include <unordered_map>

namespace GemTracker {
namespace Http {

class Request {
public:
    Request(const std::string& headersString);
    std::unordered_map<std::string, std::string> headers;

private:
    inline void parse_headers(const std::string& headers_string);
};

} // namespace Http
} // namespace GemTracker

