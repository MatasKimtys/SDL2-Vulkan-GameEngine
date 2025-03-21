#include "game_engine.hpp"
#include "utils/utils.hpp"

namespace Engine {

GameEngine::GameEngine() 
    : gameEngineLogger{Utils::initLogger("GameEngineLogger", spdlog::level::debug)
} {
    initialize();
    gameEngineLogger.debug("Game Engine Initialized");
}

GameEngine::~GameEngine() {
    shutdown();
    gameEngineLogger.debug("Game Engine Shutdown");

}

void GameEngine::shutdown() {
    systemManager.reset();
    entityManager.reset();
    componentManager.reset();
    sceneManager.reset();
    resourceManager.reset();
}

void GameEngine::initialize() {
    systemManager = std::move(std::make_unique<Core::SystemManager>());
    entityManager = std::move(std::make_unique<Core::EntityManager>());
    componentManager = std::move(std::make_unique<Core::ComponentManager>());
    sceneManager = std::move(std::make_unique<Core::SceneManager>());
    resourceManager = std::move(std::make_unique<Core::ResourceManager>());
}

}
