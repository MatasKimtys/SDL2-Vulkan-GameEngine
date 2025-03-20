#include "core/component_manager.hpp"
#include <spdlog/spdlog.h>

namespace Core {

ComponentManager::ComponentManager() {
    spdlog::info("Component Manager Initialized");
}

ComponentManager::~ComponentManager() {
    spdlog::info("Component Manager Shutdown");
}

}
