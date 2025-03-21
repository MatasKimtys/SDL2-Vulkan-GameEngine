#pragma once 
#include <memory>
#include "core/system_manager.hpp"
#include "core/component_manager.hpp"
#include "core/entity_manager.hpp"
#include "core/scene_manager.hpp"
#include "core/resource_manager.hpp"
#include "core/core.hpp"
#include "spdlog/spdlog.h"

namespace Engine {

class GameEngine {
private:
    spdlog::logger gameEngineLogger;

    std::unique_ptr<Core::ResourceManager> resourceManager;
    std::unique_ptr<Core::SystemManager> systemManager;
    std::unique_ptr<Core::EntityManager> entityManager;
    std::unique_ptr<Core::ComponentManager> componentManager;
    std::unique_ptr<Core::SceneManager> sceneManager;
    std::unique_ptr<Core::Core> coreSystems;

public:
    GameEngine();
    ~GameEngine();

    void initialize();
    void update(float deltaTime);
    void shutdown();
    
};

}
