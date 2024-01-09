#include "Core/Core.hpp"

namespace eng {

void Configure(const Configuration& config) {
    eng::_intern_::_Core::Instance().Configure(config);
}

namespace _intern_ {

_Core::_Core() {
    std::cout << "DEBUG : Core created" << std::endl;
}

_Core::~_Core() {
    // Quit SDL
    SDL_Quit();
    std::cout << "DEBUG : Core destroyed" << std::endl;
}

_Core& _Core::Instance() {
    static _Core s_instance;
    return s_instance;
}

void _Core::Configure(const Configuration& config) {
    
    // Check if the configuration has already been made
    if (!m_isConfigure) {
        // Set configuration
        m_config = config;
        m_isConfigure = true;
    }else{
        eng::log::Logger::Instance().Error("Core", "Configuration already set. The engine can't be configure twice.");
        return;
    }
    
    eng::log::Logger& logger = eng::log::Logger::Instance();

    // === Configure the engine ===

    // Init SDL
    if (SDL_Init(config.sdl_sdlFlags) != 0) {
        SDL_Quit();
        logger.Fatal("Core", "Can't initialize SDL");
        exit(EXIT_FAILURE);
    }
    logger.Debug("Core", "SDL initialize");
}

Configuration _Core::GetConfiguration() const {
    return m_config;
}

bool _Core::IsConfigure() const {
    return m_isConfigure;
}

}


}