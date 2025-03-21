target_sources(GameEngine
    PUBLIC
    game_engine.cpp
)

target_link_libraries(GameEngine
    PRIVATE
    spdlog::spdlog
    GameEngineHeaders
)

add_subdirectory(audio)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(rendering)
add_subdirectory(utils)
add_subdirectory(core)
