#pragma once

#include "Logger/Log.hpp"

#include <External/SDL2/SDL.h>

namespace eng {

bool init(Logger* logger) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Quit();
        logger->log(eng::ERROR, "Can not initialize SDL");
        return false;
    }

    // Set Attribute for OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); // Use version 4.1 of OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // Disable old functions
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true); // Set double buffering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    return true;
}

void quit() {
    SDL_Quit();
}

}