#include "../headers/game.hpp"
#include <chrono>
#include <thread>
#include <iostream>

namespace {

void update(std::chrono::steady_clock::duration elapsedTime) {
    // Update game logic - physics, AI, game state transitions
}
}

namespace Game {

Game::Game() 
    : isRunning{true} {
}

Game::~Game() {}

void Game::processInput() {
    // Handle user input - keyboard, mouse, events, etc.
}

void Game::render() {
    // Render game here
}

void Game::run() {
    constexpr unsigned int FPS = 144;
    // fixedTimeStep is derived from steady_clock's duration (assumed to be in microseconds)
    constexpr std::chrono::steady_clock::duration fixedTimeStep = std::chrono::steady_clock::duration(100000) / FPS;
    std::chrono::steady_clock::duration accumulator {0};
    auto currentTime = std::chrono::steady_clock::now();

    // FPS Counter variables
    unsigned int frameCount = 0;
    auto lastFpsTime = currentTime;

    while (isRunning) {
        auto newTime = std::chrono::steady_clock::now();
        auto frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;
        frameCount++; // Increment frame counter

        while (accumulator >= fixedTimeStep) {
            processInput();
            update(fixedTimeStep);
            accumulator -= fixedTimeStep;
        }
        render();

        // Check if one second has elapsed and print the FPS
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - lastFpsTime);
        if (elapsedTime.count() >= 1000) {
            std::cout << "FPS: " << frameCount << std::endl;
            frameCount = 0;
            lastFpsTime = newTime;
        }

        // Optional: add a small sleep to avoid maxing out CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

}
