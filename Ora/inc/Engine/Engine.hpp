#pragma once

#include "Log/Logger.hpp"
#include "Window/Window.hpp"
#include "Engine/Initialization.hpp"
#include "Engine/Timer.hpp"
#include "Event/Event.hpp"

namespace ora {

struct OrangeEngine {
    OrangeEngine(const InitializationList& init)
    :   logger(init.log_state, init.log_file_name), 
        window(init.win_width, init.win_height, init.win_title, init.win_sdl_flags, init.win_win_flags, &logger),
        event(&logger),
        timer(init.tim_fps)
    {
        logger.log(ora::Info, "Engine created");
    }

    ~OrangeEngine() {
        logger.log(ora::Info, "Engine destroyed");
    }

    Logger logger;
    Window window;
    Event event;
    Timer timer;
};

}