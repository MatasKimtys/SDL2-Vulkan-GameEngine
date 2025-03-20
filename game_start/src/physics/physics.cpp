#include "physics/physics.hpp"
#include <spdlog/spdlog.h>

namespace Engine {

Physics::Physics() {
    spdlog::info("Physics Initialized");
}

Physics::~Physics() {
    spdlog::info("Physics Shutdown");
}

}
