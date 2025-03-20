#include <iostream>
#include <spdlog/spdlog.h>
#include "game_engine.hpp"

int main(int, char**){
    spdlog::set_level(spdlog::level::debug);

    Engine::GameEngine game;
    game.initialize();
    return 0;
}
