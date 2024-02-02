#include "Core/Core.hpp"

namespace eng {

namespace _intern_ {

_Core::_Core()
: m_isConfigure(false), m_isRunning(true)
{
    std::cout << "DEBUG : Core created" << std::endl;
}

_Core::~_Core() {
    // Quit MIX
    Mix_CloseAudio();
    Mix_Quit();

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

    // Init MIX
    if (Mix_Init(config.mix_flags) != config.mix_flags) {
        Mix_Quit();
        SDL_Quit();
        logger.Fatal("Core", "Can't initialize MIX");
        exit(EXIT_FAILURE);
    }
    if (Mix_OpenAudio(config.mix_frequency, config.mix_format, config.mix_channels, config.mix_chunksize) < 0) {
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        logger.Fatal("Core", "Can't open audio audio");
        exit(EXIT_FAILURE);
    }

    // Set Attribute for OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // Disable old functions
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true); // Set double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create the instance of the window to be sure that the OpenGL Context has been created
    eng::Window::Instance();
}

void _Core::Quit() {
    m_isRunning = false;
}

Configuration _Core::GetConfiguration() const {
    return m_config;
}

bool _Core::IsConfigure() const {
    return m_isConfigure;
}

bool _Core::IsRunning() const {
    return m_isRunning;
}

}


}