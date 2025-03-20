#pragma once
#include <string>
#include <memory>
#include "spdlog/spdlog.h"

namespace Core {

class ResourceManager {
private:
    ResourceManager();
    ~ResourceManager();

public:
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }
    // Delete copy and move constructors to enforce singleton behavior
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    void loadResource(const std::string& path);

};

}
