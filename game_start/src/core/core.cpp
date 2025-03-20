#include "core/core.hpp"
#include <spdlog/spdlog.h>

namespace Core {

Core::Core() {
    spdlog::info("Core Initialized");
}

Core::~Core() {
    spdlog::info("Core Shutdown");
}

}
