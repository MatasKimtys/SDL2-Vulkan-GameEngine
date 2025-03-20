#include "utils/utils.hpp"
#include <spdlog/spdlog.h>

namespace Engine {

Utils::Utils() {
    spdlog::info("Utils Initialized");
}

Utils::~Utils() {
    spdlog::info("Utils Shutdown");
}

}
