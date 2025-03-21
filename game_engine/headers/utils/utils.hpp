#pragma once
#include <spdlog/spdlog.h>

namespace Utils {

spdlog::logger initLogger(
    const std::string& loggerName, 
    const spdlog::level::level_enum severity
);

}
