#include "core/resource_manager.hpp"
#include <spdlog/spdlog.h>

namespace Core {

ResourceManager::ResourceManager() {
    spdlog::info("ResourceManager Created");
}

ResourceManager::~ResourceManager() {
    spdlog::info("ResourceManager Destroyed");
}

}
