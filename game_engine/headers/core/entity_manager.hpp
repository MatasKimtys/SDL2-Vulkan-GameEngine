#pragma once
#include <memory>
#include <vector>
#include "spdlog/spdlog.h"
#include <immintrin.h>

namespace Core {

struct Entity {
    uint32_t id;
    uint32_t generation;
};

class EntityManager {
private:
    spdlog::logger entityLogger;
    std::vector<Entity> entities;
    std::vector<float> positionX;
    std::vector<float> positionY;
    std::vector<float> positionZ;
    std::vector<float> velocityX;
    std::vector<float> velocityY;
    std::vector<float> velocityZ;
    std::vector<float> accelerationX;
    std::vector<float> accelerationY;
    std::vector<float> accelerationZ;
    std::vector<float> rotationX;
    std::vector<float> rotationY;
    std::vector<float> rotationZ;
    uint32_t nextEntityID = 1;

public:
    EntityManager();
    ~EntityManager();

    void addEntity(const Entity& entity);
    void removeEntity(unsigned int id);
    void updateEntities(float deltaTime);
    const std::vector<Entity>& getEntities() const;
    Entity& getEntity(unsigned int id);
};

}
