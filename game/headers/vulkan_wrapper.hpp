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
    VkCommandBuffer commandBuffer;
    VkCommandPool commandPool;
    VkPipeline graphicsPipeline;
    VkFramebuffer framebuffer;
    std::vector<VkFramebuffer> framebuffers;
    std::vector<VkImageView> swapChainImageViews;
    VkExtent2D swapChainExtent;

public:
    Vulkan(SDLWrapper::SDL& sdl);
    Vulkan();
    ~Vulkan();
    void renderTriangle();

};
}
