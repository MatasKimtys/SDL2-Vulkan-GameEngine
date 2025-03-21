#include "core/component_manager.hpp"
#include <spdlog/spdlog.h>
#include "utils/utils.hpp"

namespace Core {

ComponentManager::ComponentManager() 
    : componentLogger{Utils::initLogger("ComponentManager", spdlog::level::debug)} {
    componentLogger.debug("Component Manager Initialized");
}

ComponentManager::~ComponentManager() {
    componentLogger.debug("Component Manager Shutdown");
}

}
