#include "core/system_manager.hpp"
#include <spdlog/spdlog.h>

namespace Core {

SystemManager::SystemManager() {
    spdlog::info("System Manager Initialized");
}

SystemManager::~SystemManager() {
    spdlog::info("System Manager Shutdown");
}

}
