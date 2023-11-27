#include "Game.h"
#include <iostream>

int main() {
    try {
        WorldExtender::Game worldExtender(1920, 1080, "World Extender");
        worldExtender.run();
    }
    catch(const std::exception &e) {
        std::cerr << "Unhandled Exception: " << e.what() << std::endl;
    }
    return 0;
}
