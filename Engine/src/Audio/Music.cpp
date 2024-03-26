#include "Audio/Music.hpp"

namespace eng {

Music_::Music_(Mix_Music* music)
: Asset(AssetType::Music), m_music(music)
{}

Music_::~Music_() {
    Mix_FreeMusic(m_music);
}

void Music_::play(int32_t loop) const {
    Mix_PlayMusic(m_music, loop);
}
void Music_::play_fade(int32_t time, int32_t loop) const{
    Mix_FadeInMusic(m_music, loop, time);
}

void Music_::volume(float volume) {
    Mix_VolumeMusic(volume*128);
}
void Music_::pause() {
    Mix_PauseMusic();
}
bool Music_::is_playing() {
    return Mix_PlayingMusic();
}
void Music_::resume() {
    Mix_ResumeMusic();
}
void Music_::stop() {
    Mix_HaltMusic();
}
void Music_::stop_fade(int32_t time) {
    Mix_FadeOutMusic(time);
}

}