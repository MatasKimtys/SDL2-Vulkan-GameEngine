#pragma once

#include "game_state.hpp"

#include <unordered_map>

namespace Game {

class ServerWorld {
public:
    PlayerId createPlayer(const glm::vec3& spawnPosition = {0.0f, 0.0f, 0.0f});
    void submitInput(const PlayerInputCommand& command);
    void tick(float deltaTime);
    const Player& getPlayer(PlayerId playerId) const;
    WorldSnapshot createSnapshot() const;
    uint64_t getCurrentTick() const;

private:
    struct PendingPlayerInput {
        InputState pendingInput;
        uint64_t lastClientTick = 0;
    };

    PlayerId nextPlayerId = 1;
    uint64_t currentTick = 0;
    std::unordered_map<PlayerId, Player> players;
    std::unordered_map<PlayerId, PendingPlayerInput> pendingInputs;

    void updatePlayer(PlayerId playerId, float deltaTime);
};

}
