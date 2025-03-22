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


void EntityManager::addEntity(const Entity& entity) {
    entities.emplace_back(entity);
}

void EntityManager::removeEntity(unsigned int id) {
    entities.erase(entities.begin() + id);
}

void EntityManager::updateEntities(float deltaTime){
    for (auto& entity : entities) {
        entity.positionX += entity.velocityX * deltaTime;
        entity.positionY += entity.velocityY * deltaTime;
        entity.positionZ += entity.velocityZ * deltaTime;
    }
}

const std::vector<Entity>& EntityManager::getEntities() const {
    return entities;
}

Entity& EntityManager::getEntity(unsigned int id) {
    return entities[id];
}

}
