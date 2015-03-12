#pragma once

#include <unordered_map>
#include <string>

namespace GemTracker {
namespace Http {

class Response {
public:
    std::unordered_map<std::string, std::string> headers; 
    std::string asString() const noexcept;

    void setMessage(std::string message) noexcept;

private:
    std::string message;
};

} // namespace Http
} // namespace GemTracker

