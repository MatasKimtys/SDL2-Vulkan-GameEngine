#pragma once 
#include <memory>
#include "core/system_manager.hpp"
#include "core/component_manager.hpp"
#include "core/entity_manager.hpp"
#include "core/scene_manager.hpp"
#include "core/resource_manager.hpp"

namespace Engine {

class GameEngine {
private:
    Core::ResourceManager* resourceManager;
    std::unique_ptr<Core::SystemManager> systemManager;
    std::unique_ptr<Core::EntityManager> entityManager;
    std::unique_ptr<Core::ComponentManager> componentManager;
    std::unique_ptr<Core::SceneManager> sceneManager;
public:
    GameEngine();
    ~GameEngine();

    void initialize();
    void update(float deltaTime);
    void shutdown();
    
};

}
