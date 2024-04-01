#include "Core/Core.hpp"

namespace eng {

namespace _intern_ {

_Core::_Core()
: m_isConfigure(false), m_isRunning(true)
{
    std::cout << "DEBUG : Core created" << std::endl;
}

_Core::~_Core() {
    // Quit FreeType
    FT_Done_FreeType(eng::Font_::s_ft_lib);

    // Quit MIX
    Mix_CloseAudio();
    Mix_Quit();

    // Quit SDL
    SDL_Quit();

    std::cout << "DEBUG : Core destroyed" << std::endl;
}

_Core& _Core::instance() {
    static _Core s_instance;
    return s_instance;
}

void _Core::configure(const Configuration& config) {
    
    // Check if the configuration has already been made
    if (!m_isConfigure) {
        // Set configuration
        m_config = config;
        m_isConfigure = true;
    }else{
        eng::log::Logger::instance().error("Core", "Configuration already set. The engine can't be configure twice.");
        return;
    }
    
    eng::log::Logger& logger = eng::log::Logger::instance();

    // === Configure the engine ===

    // Init SDL
    if (SDL_Init(config.sdl_sdlFlags) != 0) {
        SDL_Quit();
        logger.fatal("Core", "Can't initialize SDL");
        exit(EXIT_FAILURE);
    }
    logger.debug("Core", "SDL initialize");

    // Init MIX
    if (Mix_Init(config.mix_flags) != config.mix_flags) {
        Mix_Quit();
        SDL_Quit();
        logger.fatal("Core", "Can't initialize MIX");
        exit(EXIT_FAILURE);
    }
    if (Mix_OpenAudio(config.mix_frequency, config.mix_format, config.mix_channels, config.mix_chunksize) < 0) {
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        logger.fatal("Core", "Can't open audio audio");
        exit(EXIT_FAILURE);
    }

    // Set Attribute for OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // Disable old functions
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true); // Set double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Init the freetype
    if (FT_Init_FreeType(&eng::Font_::s_ft_lib) != 0) {
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        logger.fatal("Core", "Can't initialize");
        exit(EXIT_FAILURE);
    }

    // Create the instance of the window to be sure that the OpenGL Context has been created
    eng::Window::instance();
}

void _Core::quit() {
    m_isRunning = false;
}

Configuration _Core::get_configuration() const {
    return m_config;
}

bool _Core::is_configure() const {
    return m_isConfigure;
}

bool _Core::is_running() const {
    return m_isRunning;
}

}


}