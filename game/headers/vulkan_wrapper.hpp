#include <SDL2/SDL.h>
#include <memory>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include "sdl_wrapper.hpp"

namespace VulkanWrapper {
class Vulkan {
private:
    VkApplicationInfo appInfo;
    VkInstanceCreateInfo createInfo;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkSwapchainKHR swapChain;
    VkRenderPass renderPass;
    VkInstance vulkanInstance;
    VkSurfaceKHR vulkanSurface;

public:
    Vulkan(SDLWrapper::SDL& sdl);
    Vulkan();
    ~Vulkan();

};
}
