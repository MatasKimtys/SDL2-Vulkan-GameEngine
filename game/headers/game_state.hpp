#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdint>
#include <vector>

namespace Game {

using PlayerId = uint32_t;

struct InputState {
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;
    int mouseDeltaX = 0;
    int mouseDeltaY = 0;
};

struct Transform {
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 rotation {0.0f, 0.0f, 0.0f};
    glm::vec3 scale {1.0f, 1.0f, 1.0f};
};

struct Player {
    Transform transform;
    float moveSpeed = 1.5f;
};

struct Camera {
    float yaw = glm::radians(45.0f);
    float pitch = glm::radians(35.0f);
    float distance = 4.0f;
    float mouseSensitivity = 0.0025f;
};

struct PlayerInputCommand {
    PlayerId playerId = 0;
    uint64_t clientTick = 0;
    InputState input;
};

struct PlayerSnapshot {
    PlayerId playerId = 0;
    Transform transform;
};

struct WorldSnapshot {
    uint64_t serverTick = 0;
    std::vector<PlayerSnapshot> players;
};

struct ClientPlayerView {
    PlayerId playerId = 0;
    Transform previousTransform;
    Transform currentTransform;
};

struct ClientWorldView {
    uint64_t latestServerTick = 0;
    std::vector<ClientPlayerView> players;
};

}
