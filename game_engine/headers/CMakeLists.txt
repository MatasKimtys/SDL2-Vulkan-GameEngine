add_library(GameEngineHeaders INTERFACE)

target_include_directories(GameEngineHeaders INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(audio)
add_subdirectory(core)
add_subdirectory(math)
add_subdirectory(physics)
add_subdirectory(rendering)
add_subdirectory(utils)
