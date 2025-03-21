#include "core/system_manager.hpp"
#include <spdlog/spdlog.h>
#include "utils/utils.hpp"

namespace Core {

SystemManager::SystemManager()
    : systemLogger{Utils::initLogger("SystemLogger", spdlog::level::debug)} {
        systemLogger.debug("System Manager Initialized");
}

SystemManager::~SystemManager() {
    systemLogger.debug("System Manager Shutdown");
}

}
