#include "Client.h"
#include <iostream>

int main() {
    Client client;
    std::cout << client.getDownloads("rails_admin", "0.0.0")
                       .at("totalDownloads") << std::endl;
    return 0;
}

