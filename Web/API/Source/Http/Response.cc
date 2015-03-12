#include "Response.h"

#include <iostream>

namespace GemTracker {
namespace Http {

std::string Response::asString() const noexcept {
    std::string stringForm(
        protocol + ' ' + std::to_string(code) + ' ' + codeMessage + "\r\n"
    );
    for (const auto pair : headers) {
        stringForm.append(pair.first + ": " + pair.second + "\r\n");
    }
    if (!message.empty()) {
        stringForm.append("\r\n" + message);
    }
    return stringForm;
}

void Response::setMessage(std::string message) noexcept {
    this->message = message;
    headers["Content-Length"] = message.size();
}

} // namespace Http
} // namespace GemTracker

