#pragma once
#include <memory>
#include "spdlog/spdlog.h"

namespace Core {

class EntityManager {
private:
    spdlog::logger entityLogger;

public:
    EntityManager();
    ~EntityManager();
};

}
