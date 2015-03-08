#include "Store.h"
#include <vector>

int main(int argc, char *argv[]) {
    GemTracker::Store store(std::vector<std::string> {
        {argv[1]}
    });
    return 0;
}

