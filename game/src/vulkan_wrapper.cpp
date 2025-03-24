
#include "spdlog/spdlog.h"
#include "vulkan_wrapper.hpp"

namespace {

int findGraphicsQueueFamily(VkPhysicalDevice device) {
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

bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

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

VkPhysicalDevice pickPhysicalDevice(const std::vector<VkPhysicalDevice>& devices) {
    for (const auto& device : devices) {
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
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = 0; // Assume the first queue supports graphics
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    createInfo.pQueueCreateInfos = &queueCreateInfo;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create logical device!");
    }

    vkGetDeviceQueue(device, 0, 0, &graphicsQueue);
}

void createSwapChain(VkDevice& device, VkSurfaceKHR& surface, VkSwapchainKHR& swapChain, unsigned int windowWidth, unsigned int windowHeight) {
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = 2;
    createInfo.imageFormat = VK_FORMAT_B8G8R8A8_SRGB;
    createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    createInfo.imageExtent = {windowWidth, windowHeight};
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    createInfo.clipped = VK_TRUE;

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

    appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Game";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "MyGameEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;
    
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    unsigned int extensionCount = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(sdl.getWindow(), &extensionCount, nullptr)) {
        throw std::runtime_error("Failed to get Vulkan instance extensions from SDL!");
    }
    std::vector<const char*> extensions(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(sdl.getWindow(), &extensionCount, extensions.data());
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

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
}

Vulkan::Vulkan() {
    spdlog::info("VulkanWrapper::Vulkan default constructor called");
}


Vulkan::~Vulkan() {
    spdlog::info("VulkanWrapper::Vulkan destructor called");
}

} // namespace VulkanWrapper
