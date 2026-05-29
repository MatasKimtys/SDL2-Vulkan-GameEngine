#include "../headers/server_world.hpp"

#include <glm/glm.hpp>

#include <stdexcept>

namespace Game {

PlayerId ServerWorld::createPlayer(const glm::vec3& spawnPosition) {
    PlayerId playerId = nextPlayerId++;
    Player player;
    player.transform.position = spawnPosition;

    players.emplace(playerId, player);
    pendingInputs.emplace(playerId, PendingPlayerInput{});
    return playerId;
}

void ServerWorld::submitInput(const PlayerInputCommand& command) {
    PendingPlayerInput& pendingInput = pendingInputs.at(command.playerId);
    if (command.clientTick >= pendingInput.lastClientTick) {
        pendingInput.pendingInput = command.input;
        pendingInput.lastClientTick = command.clientTick;
    }
}

void ServerWorld::tick(float deltaTime) {
    for (const auto& [playerId, _] : players) {
        updatePlayer(playerId, deltaTime);
    }
    currentTick++;
}

const Player& ServerWorld::getPlayer(PlayerId playerId) const {
    return players.at(playerId);
}

WorldSnapshot ServerWorld::createSnapshot() const {
    WorldSnapshot snapshot;
    snapshot.serverTick = currentTick;
    snapshot.players.reserve(players.size());

    for (const auto& [playerId, player] : players) {
        snapshot.players.push_back({
            .playerId = playerId,
            .transform = player.transform
        });
    }

    return snapshot;
}

uint64_t ServerWorld::getCurrentTick() const {
    return currentTick;
}

void ServerWorld::updatePlayer(PlayerId playerId, float deltaTime) {
    glm::vec2 movement {0.0f, 0.0f};
    const InputState& input = pendingInputs.at(playerId).pendingInput;
    Player& player = players.at(playerId);

    if (input.moveUp) {
        movement.y += 1.0f;
    }
    if (input.moveDown) {
        movement.y -= 1.0f;
    }
    if (input.moveLeft) {
        movement.x -= 1.0f;
    }
    if (input.moveRight) {
        movement.x += 1.0f;
    }

    if (movement.x != 0.0f || movement.y != 0.0f) {
        glm::vec2 frameMovement = glm::normalize(movement) * player.moveSpeed * deltaTime;
        player.transform.position += glm::vec3(frameMovement, 0.0f);
    }
}

}
