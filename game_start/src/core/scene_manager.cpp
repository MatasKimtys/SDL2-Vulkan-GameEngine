#include "core/scene_manager.hpp"
#include <spdlog/spdlog.h>

namespace Core {

SceneManager::SceneManager() {
    spdlog::info("Scene Manager Initialized");
}

SceneManager::~SceneManager() {
    spdlog::info("Scene Manager Shutdown");
}

}
