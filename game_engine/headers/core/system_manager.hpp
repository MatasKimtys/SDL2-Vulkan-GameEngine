#pragma once
#include <memory>
#include "spdlog/spdlog.h"

namespace Core {

class SystemManager {
private:
    spdlog::logger systemLogger;

public:
    SystemManager();
    ~SystemManager();
};

}
