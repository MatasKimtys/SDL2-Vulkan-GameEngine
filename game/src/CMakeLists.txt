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

set(SHADER_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")
set(VERT_SHADER_SPV "${SHADER_OUTPUT_DIR}/vert1.spv")
set(FRAG_SHADER_SPV "${SHADER_OUTPUT_DIR}/frag1.spv")

add_custom_command(
    OUTPUT "${VERT_SHADER_SPV}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_OUTPUT_DIR}"
    COMMAND ${Vulkan_GLSLC_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_vertexbuffer.vert" -o "${VERT_SHADER_SPV}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_vertexbuffer.vert"
    COMMENT "Compiling vertex shader"
    VERBATIM
)

add_custom_command(
    OUTPUT "${FRAG_SHADER_SPV}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_OUTPUT_DIR}"
    COMMAND ${Vulkan_GLSLC_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_vertexbuffer.frag" -o "${FRAG_SHADER_SPV}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_vertexbuffer.frag"
    COMMENT "Compiling fragment shader"
    VERBATIM
)

add_custom_target(GameShaders DEPENDS "${VERT_SHADER_SPV}" "${FRAG_SHADER_SPV}")
add_dependencies(Game GameShaders)
