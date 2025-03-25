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
    VkSwapchainKHR swapChain;
    VkRenderPass renderPass;
    VkInstance vulkanInstance;
    VkSurfaceKHR vulkanSurface;
    VkCommandBuffer commandBuffer;
    VkCommandPool commandPool;
    VkPipeline graphicsPipeline;
    VkFramebuffer framebuffer;
    std::vector<VkFramebuffer> framebuffers;
    std::vector<VkImageView> swapChainImageViews;
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    VkDebugUtilsMessengerEXT debugMessenger;

    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<const char*> extensions;
    std::vector<VkImage> swapChainImages;
    
    VkQueue graphicsQueue;
    VkQueue presentQueue;

public:
    Vulkan(SDLWrapper::SDL& sdl);
    Vulkan();
    ~Vulkan();
    void renderTriangle();

};
}
