#pragma once
#include <memory>
#include "spdlog/spdlog.h"

namespace Core {

class SceneManager {
private:
    spdlog::logger sceneLogger;

public:
    SceneManager();
    ~SceneManager();
};

}
