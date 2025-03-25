#include <iostream>
#include <spdlog/spdlog.h>
#include "game_engine.hpp"
#include "../headers/game.hpp"


int main(int, char**){
    spdlog::set_level(spdlog::level::debug);
    try {
        Engine::GameEngine gameEngine;
        Game::Game game(1920, 1080);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
