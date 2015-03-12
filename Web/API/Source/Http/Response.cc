#include "Response.h"

namespace GemTracker {
namespace Http {

std::string Response::asString() const {
    std::string stringForm;
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
    return stringForm;
}

} // namespace Http
} // namespace GemTracker

