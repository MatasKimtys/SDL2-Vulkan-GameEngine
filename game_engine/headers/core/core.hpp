#pragma once
#include <memory>
#include "spdlog/spdlog.h"

namespace Core {

class Core {
private:
    spdlog::logger coreLogger;

public:
    Core();
    ~Core();
};

}
