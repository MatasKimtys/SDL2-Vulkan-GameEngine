#include "game_engine.hpp"

namespace Engine {

GameEngine::GameEngine() 
    : resourceManager(&Core::ResourceManager::getInstance()){
    initialize();
}

GameEngine::~GameEngine() {
    shutdown();
}

void GameEngine::shutdown() {
    systemManager.reset();
    entityManager.reset();
    componentManager.reset();
    sceneManager.reset();
}

void GameEngine::initialize() {
    systemManager = std::make_unique<Core::SystemManager>();
    entityManager = std::make_unique<Core::EntityManager>();
    componentManager = std::make_unique<Core::ComponentManager>();
    sceneManager = std::make_unique<Core::SceneManager>();
}
}