#pragma once
#include <chrono>

namespace Game {
class Game {
private:
    bool isRunning;

public:
    Game();
    ~Game();

    void run();
    void processInput();
    void render();
};

}
