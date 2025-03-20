#include "core/core.hpp"
#include <spdlog/spdlog.h>

namespace Engine {

Core::Core() {
    spdlog::info("Core Initialized");
}

Core::~Core() {
    spdlog::info("Core Shutdown");
}

}
