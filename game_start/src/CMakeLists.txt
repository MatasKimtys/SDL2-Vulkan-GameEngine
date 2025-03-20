include(FetchContent)


FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.14.1
    SYSTEM
)
FetchContent_MakeAvailable(spdlog)

target_sources(Game
    PUBLIC
    main.cpp
    game_engine.cpp
)

target_link_libraries(Game
    PRIVATE
    spdlog::spdlog
    Headers
)

add_subdirectory(audio)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(rendering)
add_subdirectory(utils)
add_subdirectory(core)
