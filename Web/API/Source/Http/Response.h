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

    std::string protocol = "HTTP/1.1";
    int code;
    std::string codeMessage;

private:
    std::string message;
};

} // namespace Http
} // namespace GemTracker

