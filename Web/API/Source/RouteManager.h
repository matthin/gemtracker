#pragma once

#include <SFML/Network.hpp>
#include <vector>
#include "Controller.h"

namespace GemTracker {

class RouteManager {
public:
    RouteManager();

private:
    sf::TcpListener listener;
    std::vector<Controller> controllers;
};

} // namespace GemTracker

