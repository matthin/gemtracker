#include "Client.h"
#include <iostream>

int main(int argc, char *argv[]) {
    GemTracker::Client client;
    std::cout << client.getDownloads(argv[1], argv[2])
                       .at("totalDownloads") << std::endl;
    return 0;
}

