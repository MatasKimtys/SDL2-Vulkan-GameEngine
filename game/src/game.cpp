#include "../headers/game.hpp"
#include <chrono>
#include <thread>
#include <iostream>

namespace Game {

Game::Game() 
    : isRunning{true} {
}

Game::~Game() {}

void Game::run() {
    using clock = std::chrono::high_resolution_clock;
    auto previousTime = clock::now();
    const unsigned int FPS = 165;
    // Calculate frame delay in microseconds (1 second == 1,000,000 microseconds)
    const auto frameDelay = std::chrono::microseconds(1000000 / FPS);
    
    while (isRunning) {
        // Mark the start of loop work
        auto loopStart = clock::now();
        
        // Calculate elapsed time since last frame in microseconds
        auto currentTime = clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime);
        previousTime = currentTime;
        
        // processInput();
        // update(elapsedTime);  // Pass microseconds directly to update
        // render();
        
        // Calculate how long the loop work took
        auto workTime = std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - loopStart);
        
        // If the work completed faster than the frame delay, sleep for the remaining time
        if (workTime < frameDelay) {
            std::this_thread::sleep_for(frameDelay - workTime);
        }
        // print fps
        std::cout << "FPS: " << 1000000 / std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - loopStart).count() << std::endl;
    }
}

}
