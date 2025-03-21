#include "core/scene_manager.hpp"
#include <spdlog/spdlog.h>
#include "utils/utils.hpp"

namespace Core {

SceneManager::SceneManager()
    : sceneLogger{Utils::initLogger("SceneLogger", spdlog::level::debug)} {
    sceneLogger.debug("Scene Manager Initialized");
}

SceneManager::~SceneManager() {
    sceneLogger.debug("Scene Manager Shutdown");
}

}
