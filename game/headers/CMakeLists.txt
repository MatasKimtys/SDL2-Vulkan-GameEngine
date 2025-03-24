add_library(GameHeaders INTERFACE)

target_sources(
    GameHeaders 
    PUBLIC 
    game.hpp
    sdl_wrapper.hpp
    vulkan_wrapper.hpp
)

target_include_directories(GameHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
