#pragma once
#include <memory>
#include "spdlog/spdlog.h"

namespace Core {

class ComponentManager {
private:
    spdlog::logger componentLogger;

public:
    ComponentManager();
    ~ComponentManager();
};

}
