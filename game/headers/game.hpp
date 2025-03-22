#pragma once
#include <chrono>
#include "sdl_wrapper.hpp"
#include <vulkan/vulkan.h>

namespace Game {
class Game {
private:
    bool isRunning;
    SDLWrapper::SDL sdl;
    VkInstance vulkanInstance;
    VkSurfaceKHR vulkanSurface;
    
public:
    Game();
    ~Game();

    void run();
    void processInput();
    void render();
    void vulkanInit();
};

}
