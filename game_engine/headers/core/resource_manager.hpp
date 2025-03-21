#pragma once
#include <string>
#include <memory>
#include "spdlog/spdlog.h"

namespace Core {

class ResourceManager {
private:
    spdlog::logger resourceLogger;

public:
    ResourceManager();
    ~ResourceManager();
    void loadResource(const std::string& path);

};

}
