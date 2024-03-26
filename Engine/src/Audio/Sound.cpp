#include "Audio/Sound.hpp"

namespace eng {

Sound_::Sound_(Mix_Chunk* sound)
: Asset(AssetType::Sound), m_sound(sound)
{}

Sound_::~Sound_() {
    Mix_FreeChunk(m_sound);
}

void Sound_::play(int channel, int loop) {
    Mix_PlayChannel(channel, m_sound, loop);
}

void Sound_::play_fade(int time, int channel, int loop) {
    Mix_FadeInChannel(channel, m_sound, loop, time);
}

void Sound_::volume(float volume) {
    Mix_VolumeChunk(m_sound, volume*128);
}

}