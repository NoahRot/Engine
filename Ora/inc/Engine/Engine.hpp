#pragma once

#include <memory>

#include "Log/Logger.hpp"

#include "Engine/Configuration.hpp"
#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Time/Timer.hpp"
#include "Audio/AudioManager.hpp"
#include "Graphic/Shader.hpp"

namespace ora {

struct OrangeEngine {
    OrangeEngine(const Configuration& init);

    ~OrangeEngine();

    Logger& logger;
    Window window;
    EventManager event_manager;
    const Keyboard& keyboard;
    const Mouse& mouse;
    Timer timer;
    
    AudioManager audio_manager;
    ShaderManager shader_manager;
    //TextureManager texture_manager;
    //FontManager font_manager;
};

}