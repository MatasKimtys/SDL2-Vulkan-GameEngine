target_link_libraries(Game
    PRIVATE
    spdlog::spdlog
    GameEngineHeaders
    GameEngine
    GameHeaders
)

target_sources(
    Game 
    PUBLIC 
    game.cpp
    main.cpp
    sdl_wrapper.cpp
    vulkan_wrapper.cpp
)

