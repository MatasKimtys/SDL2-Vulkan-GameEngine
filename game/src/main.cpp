#include <iostream>
#include <spdlog/spdlog.h>
#include "game_engine.hpp"
#include "../headers/game.hpp"


int main(int, char**){
    spdlog::set_level(spdlog::level::debug);

    Engine::GameEngine gameEngine;
    Game::Game game;
    game.run();
    return 0;
}
