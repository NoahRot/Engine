#pragma once

#include <string>
#include <External/SDL2/SDL_mixer.h>

#include "Logger/Logger.hpp"

namespace eng::_intern_ {

class Music {
public:
    Music();

    ~Music();

    bool Load(const std::string& path);

    bool IsValid() const;

    Mix_Music* GetMusic() const;

private:
    Mix_Music* m_music;
};

}