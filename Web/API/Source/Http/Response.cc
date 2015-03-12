#include "Response.h"

#include <iostream>

namespace GemTracker {
namespace Http {

std::string Response::asString() const noexcept {
    std::string stringForm;
    try {
        stringForm.append(headers.at("protocol") + ' ')
                  .append(headers.at("code") + ' ')
                  .append(headers.at("codeMessage") + "\r\n");
        for (const auto pair : headers) {
            const auto key = pair.first;
            const auto value = pair.second;
            if (key != "protocol" && key != "code" && key != "codeMessage") {
                stringForm.append(key + ": " + value + "\r\n");
            }
        }
        if (!message.empty()) {
            stringForm.append("\r\n" + message);
        }
    } catch (std::out_of_range e) {
        std::cout << "Yes m8" << std::endl;
    }
    return stringForm;
}

void Response::setMessage(std::string message) noexcept {
    this->message = message;
    headers["Content-Length"] = message.size();
}

} // namespace Http
} // namespace GemTracker

