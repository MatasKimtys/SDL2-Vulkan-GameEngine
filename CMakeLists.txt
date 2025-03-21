cmake_minimum_required(VERSION 3.5.0)
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0079 NEW)

set(ENGINE_WERROR ON CACHE BOOL "Use '-Werror'")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Game)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "13")
        message(FATAL_ERROR "GCC version must be at least 13!")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "CLANG")
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "14")
        message(FATAL_ERROR "Clang version must be at least 14!")
    endif()
endif()

add_executable(Game)

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
    version.hpp
)

add_subdirectory(game_engine)
add_subdirectory(game)
