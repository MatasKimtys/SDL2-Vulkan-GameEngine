
#include "spdlog/spdlog.h"
#include "vulkan_wrapper.hpp"
#include <algorithm>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

namespace {

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }
    /* If fails, try below
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
            for (const auto& availableFormat : availableFormats) {
                if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                    return availableFormat;
                }
            }
            return availableFormats[0];
        }
    */
}

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device) {
    SwapChainSupportDetails details;

    return details;
}

void createFramebuffers(
    VkDevice& device, 
    std::vector<VkFramebuffer>& framebuffers, 
    std::vector<VkImageView>& swapChainImageViews, 
    VkExtent2D& swapChainExtent, 
    VkRenderPass& renderPass
) {
    // Assume swapChainImageViews is a vector containing the swapchain's image views.
    // Also assume that swapChainExtent and renderPass have been defined.
    framebuffers.resize(swapChainImageViews.size());

    for (size_t i = 0; i < swapChainImageViews.size(); i++) {
        VkImageView attachments[] = {
            swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = renderPass,  // Use your previously defined renderPass.
            .attachmentCount = 1,
            .pAttachments = attachments,
            .width = swapChainExtent.width,
            .height = swapChainExtent.height,
            .layers = 1
        };

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create framebuffer!");
        }
    }
}

void createCommandPool(VkDevice& device, VkCommandPool& commandPool, uint32_t queueFamilyIndex) {
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queueFamilyIndex;  // Make sure this is the correct queue family supporting graphics operations
    poolInfo.flags = 0; // Optional: you can use VK_COMMAND_POOL_CREATE_TRANSIENT_BIT, etc. if needed

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create command pool!");
    }
}

VkSurfaceCapabilitiesKHR getSurfaceCapabilities(VkPhysicalDevice& device, VkSurfaceKHR& surface, SwapChainSupportDetails& swapChainSupportDetails) {
    auto& capabilities = swapChainSupportDetails.capabilities;
    if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities) != VK_SUCCESS) {
        throw std::runtime_error("Failed to get surface capabilities!");
    }
    return capabilities;
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, unsigned int width, unsigned int height) {
    // If the surface size is defined, return it.
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        // Potentially Missing Frame Buffer Size

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}


int findGraphicsQueueFamily(VkPhysicalDevice& device) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    for (int i = 0; i < queueFamilies.size(); i++) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            return i; // Found a graphics-capable queue
        }
    }

    return -1; // No suitable queue found
}

bool checkDeviceExtensionSupport(VkPhysicalDevice& device) {
    uint32_t extensionCount;
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    const std::vector<const char*> requiredExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    for (const char* required : requiredExtensions) {
        bool found = false;
        for (const auto& extension : availableExtensions) {
            if (strcmp(required, extension.extensionName) == 0) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }

    return true;
}

VkPhysicalDevice pickPhysicalDevice(std::vector<VkPhysicalDevice>& devices) {
    for (auto& device : devices) {
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceProperties(device, &properties);
        vkGetPhysicalDeviceFeatures(device, &features);

        int queueFamilyIndex = findGraphicsQueueFamily(device);
        bool swapchainSupported = checkDeviceExtensionSupport(device);

        if (queueFamilyIndex != -1 && swapchainSupported) {
            if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                spdlog::debug("Selected discrete GPU: {}", properties.deviceName);
                return device;
            }
        }
    }

    throw std::runtime_error("No suitable GPU found!");
}

void createLogicalDevice(VkPhysicalDevice& physicalDevice, VkDevice& device, VkQueue& graphicsQueue) {
    const std::vector<const char*> requiredExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = 0, // Assume the first queue supports graphics
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };

    VkDeviceCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCreateInfo,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size()),
        .ppEnabledExtensionNames = requiredExtensions.data(),
        .pEnabledFeatures = nullptr
    };

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical device!");
    }

    vkGetDeviceQueue(device, 0, 0, &graphicsQueue);
}

void createSwapChain(VkDevice& device, VkSurfaceKHR& surface, VkSwapchainKHR& swapChain, unsigned int windowWidth, unsigned int windowHeight) {
    VkSwapchainCreateInfoKHR createInfo{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = surface,
        .minImageCount = 2,
        .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,
        .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
        .imageExtent = {windowWidth, windowHeight},
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = VK_PRESENT_MODE_FIFO_KHR,
        .clipped = VK_TRUE
    };

    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create swapchain!");
    }
}

void createRenderPass(VkDevice& device, VkRenderPass& renderPass) {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = VK_FORMAT_B8G8R8A8_SRGB;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create render pass!");
    }
}

}

namespace VulkanWrapper {

Vulkan::Vulkan(SDLWrapper::SDL& sdl) {
    spdlog::info("VulkanWrapper::Vulkan constructor called");

    appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .pApplicationName = "Vulkan Game",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "MyGameEngine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_2
    };

    unsigned int extensionCount = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(sdl.getWindow(), &extensionCount, nullptr)) {
        throw std::runtime_error("Failed to get Vulkan instance extensions from SDL!");
    }
    std::vector<const char*> extensions(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(sdl.getWindow(), &extensionCount, extensions.data());

    createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
        .ppEnabledExtensionNames = extensions.data()
    };


    if (vkCreateInstance(&createInfo, nullptr, &vulkanInstance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create Vulkan instance!");
    }

    if (!SDL_Vulkan_CreateSurface(sdl.getWindow(), vulkanInstance, &vulkanSurface)) {
        throw std::runtime_error("Failed to create Vulkan surface!");
    }
    spdlog::debug("Vulkan initialized successfully!");

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("No Vulkan-compatible GPU found!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, devices.data());

    if(findGraphicsQueueFamily(devices[0]) < 0) {
        throw std::runtime_error("No graphics queue family found!");
    }
    physicalDevice = pickPhysicalDevice(devices);

    createLogicalDevice(physicalDevice, device, graphicsQueue);



    const auto [screenWidth, screenHeight] = sdl.getWindowSize();
    createSwapChain(device, vulkanSurface, swapChain, screenWidth, screenHeight);
    createRenderPass(device, renderPass);
    spdlog::debug("Vulkan device set up successfully!");


    auto swapChainSupportDetails = querySwapChainSupport(physicalDevice);
    auto capabilities = getSurfaceCapabilities(physicalDevice, vulkanSurface, swapChainSupportDetails);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
    swapChainExtent = chooseSwapExtent(capabilities, screenWidth, screenHeight);
    
    auto graphicsQueueFamilyIndex = findGraphicsQueueFamily(physicalDevice);
    createCommandPool(device, commandPool, graphicsQueueFamilyIndex);

    createFramebuffers(device, framebuffers, swapChainImageViews, swapChainExtent, renderPass);
    spdlog::debug("Vulkan swapchain and framebuffers created successfully!");
}

Vulkan::Vulkan() {
    spdlog::info("VulkanWrapper::Vulkan default constructor called");
}


Vulkan::~Vulkan() {
    spdlog::info("VulkanWrapper::Vulkan destructor called");
    vkDestroyDevice(device, nullptr);
    vkDestroySurfaceKHR(vulkanInstance, vulkanSurface, nullptr);
    vkDestroyInstance(vulkanInstance, nullptr);
}

void Vulkan::renderTriangle() {
    // 1. Allocate a command buffer from the command pool.
    VkCommandBufferAllocateInfo allocInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = nullptr,
        .commandPool = commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = 1
    };
    if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate command buffer for rendering triangle!");
    }

    // 2. Begin recording the command buffer.
    VkCommandBufferBeginInfo beginInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .pNext = nullptr,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
        .pInheritanceInfo = nullptr
    };
    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("Failed to begin recording command buffer!");
    }

    // 3. Prepare the render pass begin info.
    // Use a local clear value variable on the stack.
    VkClearValue clearValue{
        .color = {.float32 = {0.0f, 0.0f, 0.0f, 1.0f}}
    };
    VkRenderPassBeginInfo renderPassInfo{
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .pNext = nullptr,
        .renderPass = renderPass,
        .framebuffer = framebuffer, // 'framebuffer' must be valid (created during swapchain setup).
        .renderArea = {
            .offset = {0, 0},
            .extent = swapChainExtent
        },
        .clearValueCount = 1,
        .pClearValues = &clearValue
    };
    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // NOTE: Remove createFramebuffers() call here - framebuffers must be created during swapchain initialization.
    
    // 4. Set dynamic viewport and scissor (if your pipeline uses dynamic states)
    VkViewport viewport{
        .x = 0.0f,
        .y = 0.0f,
        .width = static_cast<float>(swapChainExtent.width),
        .height = static_cast<float>(swapChainExtent.height),
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    
    VkRect2D scissor{
        .offset = {0, 0},
        .extent = swapChainExtent
    };
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    // 5. Bind the graphics pipeline.
    // Your pipeline should include a vertex shader that generates a centered triangle
    // (for example, using gl_VertexIndex to select vertices) and a fragment shader that outputs red.
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    // 6. Issue a draw command to render a triangle (3 vertices, 1 instance).
    vkCmdDraw(commandBuffer, 3, 1, 0, 0);

    // 7. End the render pass.
    vkCmdEndRenderPass(commandBuffer);

    // 8. End recording the command buffer.
    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to record command buffer for triangle rendering!");
    }

    // 9. Submit the command buffer to the graphics queue.
    VkSubmitInfo submitInfo{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreCount = 0,
        .pWaitSemaphores = nullptr,
        .pWaitDstStageMask = nullptr,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffer,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = nullptr
    };
    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
        throw std::runtime_error("Failed to submit draw command buffer!");
    }

    vkQueueWaitIdle(graphicsQueue);

    // 10. Clean up the command buffer (consider reusing command buffers in production code).
    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);

    spdlog::debug("Triangle rendered successfully!");
}
} // namespace VulkanWrapper
