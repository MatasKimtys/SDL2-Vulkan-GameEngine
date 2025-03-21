#include "math/math.hpp"
#include <spdlog/spdlog.h>

namespace Engine {

Math::Math() {
    spdlog::info("Math Initialized");
}

Math::~Math() {
    spdlog::info("Math Shutdown");
}

}
