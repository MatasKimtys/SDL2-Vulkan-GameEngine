#include "core/entity_manager.hpp"
#include <spdlog/spdlog.h>

namespace Core {

EntityManager::EntityManager() {
    spdlog::info("Entity Manager Initialized");
}

EntityManager::~EntityManager() {
    spdlog::info("Entity Manager Shutdown");
}

}
