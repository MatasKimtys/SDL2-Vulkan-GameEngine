#include "renderer/renderer.hpp"
#include <spdlog/spdlog.h>

namespace Engine {

Renderer::Renderer() {
    spdlog::info("Renderer Initialized");
}

Renderer::~Renderer() {
    spdlog::info("Renderer Shutdown");
}

}
