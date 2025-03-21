#include "core/entity_manager.hpp"
#include <spdlog/spdlog.h>
#include "utils/utils.hpp"

namespace Core {

EntityManager::EntityManager() 
    : entityLogger{Utils::initLogger("Entity", spdlog::level::debug)} {
    entityLogger.debug("Entity Manager Initialized");
}

EntityManager::~EntityManager() {
    entityLogger.debug("Entity Manager Shutdown");
}

}
