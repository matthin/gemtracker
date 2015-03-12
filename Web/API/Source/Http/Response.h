#pragma once


#include <unordered_map>
#include <string>

namespace GemTracker {
namespace Http {

class Response {
public:
    std::unordered_map<std::string, std::string> headers;
    std::string message;
    std::string asString() const;
};

} // namespace Http
} // namespace GemTracker

