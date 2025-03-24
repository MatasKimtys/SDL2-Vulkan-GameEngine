#pragma once
#include <chrono>
#include "vulkan_wrapper.hpp"

namespace Game {
class Game {
private:
    bool isRunning;
    SDLWrapper::SDL sdl;
    VulkanWrapper::Vulkan vulkan;
    
public:
    Game(const unsigned int screenWidth, const unsigned int screenHeight);
    ~Game();

    void run();
    void processInput();
    void render();
    void vulkanInit();
    void update(float elapsedTime);
};

}
