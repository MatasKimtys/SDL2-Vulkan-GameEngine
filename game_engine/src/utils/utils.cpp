#include "utils/utils.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

namespace Utils {

spdlog::logger initLogger(
    const std::string& loggerName, 
    const spdlog::level::level_enum severity = spdlog::level::info
) {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(severity);
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + loggerName + ".txt", true);
    file_sink->set_level(severity);
    auto logger = spdlog::logger(loggerName, spdlog::sinks_init_list{console_sink, file_sink});
    logger.set_level(severity);
    return logger;
}

}
