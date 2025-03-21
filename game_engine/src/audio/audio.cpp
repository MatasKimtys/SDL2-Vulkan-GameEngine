#include "audio/audio.hpp"
#include <spdlog/spdlog.h>

namespace Engine {

Audio::Audio() {
    spdlog::info("Audio Initialized");
}

Audio::~Audio() {
    spdlog::info("Audio Shutdown");
}

}
