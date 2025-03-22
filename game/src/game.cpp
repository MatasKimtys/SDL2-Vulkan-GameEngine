#include "../headers/game.hpp"
#include <chrono>
#include <thread>
#include <iostream>

namespace {

void update(float elapsedTime) {
    // Update game logic - physics, AI, game state transitions
}
}

namespace Game {

Game::Game() 
    : isRunning{true},
      sdl{SDLWrapper::SDL(800, 600)} {
    vulkanInit();   
}

Game::~Game() {}

void Game::vulkanInit() {
    // Vulkan initialisation
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Game";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "MyGameEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;
    
    VkInstanceCreateInfo createInfo{};
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

    // Step 2: Create Vulkan Surface
    if (!SDL_Vulkan_CreateSurface(sdl.getWindow(), vulkanInstance, &vulkanSurface)) {
        throw std::runtime_error("Failed to create Vulkan surface!");
    }

    std::cout << "Vulkan initialized successfully!" << std::endl;
}

void Game::processInput() {
    // Handle user input - keyboard, mouse, events, etc.
}


void Game::render() {
    // Acquire the next available image from the swapchain.
    uint32_t imageIndex;
    if (vkAcquireNextImageKHR(vulkanInstance, swapchain, UINT64_MAX,
                              imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex) != VK_SUCCESS) {
        throw std::runtime_error("Failed to acquire swapchain image!");
    }

    // Begin recording the command buffer.
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("Failed to begin recording command buffer!");
    }

    // Set up the render pass begin info.
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;             // Assume renderPass is set up elsewhere.
    renderPassInfo.framebuffer = framebuffers[imageIndex]; // Corresponding framebuffer for the image.
    renderPassInfo.renderArea.offset = {0, 0};
    // Specify clear color (here we clear to black).
    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    // Begin the render pass.
    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Bind the graphics pipeline.
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    // Bind the vertex buffer that contains the square's vertices.
    VkBuffer vertexBuffers[] = { vertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    // Record the draw command; drawing 4 vertices forming a square.
    vkCmdDraw(commandBuffer, 4, 1, 0, 0);

    // End the render pass.
    vkCmdEndRenderPass(commandBuffer);

    // End recording.
    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to record command buffer!");
    }

    // Submit the command buffer.
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    VkSemaphore waitSemaphores[] = { imageAvailableSemaphore };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
        throw std::runtime_error("Failed to submit draw command buffer!");
    }

    // Wait for the graphics queue to finish execution.
    vkQueueWaitIdle(graphicsQueue);

    // Present the rendered image.
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &swapchain;
    presentInfo.pImageIndices = &imageIndex;
    if (vkQueuePresentKHR(presentQueue, &presentInfo) != VK_SUCCESS) {
        throw std::runtime_error("Failed to present swapchain image!");
    }
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
