#include "core/resource_manager.hpp"
#include <spdlog/spdlog.h>
#include "utils/utils.hpp"

namespace Core {

ResourceManager::ResourceManager()
    : resourceLogger{Utils::initLogger("ResourceLogger", spdlog::level::debug)} {
    resourceLogger.debug("ResourceManager Created");
}

ResourceManager::~ResourceManager() {
    resourceLogger.debug("ResourceManager Destroyed");
}

}
