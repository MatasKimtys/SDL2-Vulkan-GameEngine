#include "core/core.hpp"
#include <spdlog/spdlog.h>
#include "utils/utils.hpp"

namespace Core {

Core::Core() 
    : coreLogger{Utils::initLogger("Core", spdlog::level::debug)} {
    coreLogger.debug("Core Initialized");
}

Core::~Core() {
    coreLogger.debug("Core Shutdown");
}

}
