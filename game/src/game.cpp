#include "../headers/game.hpp"
#include <chrono>
#include <thread>
#include <iostream>

namespace Game {

Game::Game(const unsigned int screenWidth, const unsigned int screenHeight) 
    : isRunning{true},
      sdl{SDLWrapper::SDL(screenWidth, screenHeight)} {
    vulkan = VulkanWrapper::Vulkan(sdl);
}

Game::~Game() {}

void Game::processInput() {
    // Handle user input - keyboard, mouse, events, etc.
}

void Game::render() {
    vulkan.renderTriangle();
}

void Game::update(float elapsedTime) {
    // Update game logic - physics, AI, game state transitions
}

void Game::run() {
    constexpr float targetFPS = 144.0;
    auto lastTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0;
    const float frameTime = 1.0f / targetFPS;

    while (isRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime += std::chrono::duration(currentTime - lastTime).count();
        lastTime = currentTime;

        while (deltaTime >= frameTime) {
            processInput();
            update(frameTime);
            deltaTime -= frameTime;
        }
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

}
