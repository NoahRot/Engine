#pragma once

#include <memory>

#include "Log/Logger.hpp"
#include "Window/Window.hpp"
#include "Engine/Configuration.hpp"
#include "Engine/Timer.hpp"
#include "Event/Event.hpp"
#include "Audio/AudioManager.hpp"
#include "Graphic/Shader.hpp"

namespace ora {

struct OrangeEngine {
    OrangeEngine(const Configuration& init);

    ~OrangeEngine();

    const Logger& logger;
    Window window;
    Event event;
    Timer timer;
    AudioManager audio_manager;
    ShaderManager shader_manager;
};

}