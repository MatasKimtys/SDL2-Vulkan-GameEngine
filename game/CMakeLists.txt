include(FetchContent)

FetchContent_Declare(
     SDL2
     GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
     GIT_TAG SDL2
 )
 FetchContent_MakeAvailable(SDL2)

 if(NOT DEFINED ENV{VULKAN_SDK})
     set(ENV{VULKAN_SDK} "C:/VulkanSDK/1.4.309.0")
 endif()
 message(STATUS "VULKAN_SDK is set to: $ENV{VULKAN_SDK}")
 
 set(Vulkan_LIBRARY "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib" CACHE FILEPATH "Path to Vulkan library")
 set(Vulkan_INCLUDE_DIR "$ENV{VULKAN_SDK}/Include" CACHE PATH "Path to Vulkan include directory")
 
 find_package(Vulkan REQUIRED)

 target_link_libraries(Game PRIVATE SDL2::SDL2main SDL2::SDL2 Vulkan::Vulkan)

add_subdirectory(headers)
add_subdirectory(src)
