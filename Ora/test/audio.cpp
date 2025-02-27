#include <iostream>

#include "program.hpp"

class TestAudio : public TestProgram {
public:
    TestAudio()
    :TestProgram("Audio"), m_keyboard(m_engine->event.keyboard())
    {
        m_music = m_engine->audio_manager.load_music("../Application/asset/music/Sky Corsair.mp3");
        if (m_music == ora::UNVALID_32) {
            m_engine->logger.log(ora::LogLevel::Fatal, "Can not load the music");
            exit(EXIT_FAILURE);
        }

    }

    virtual void event() override {
        if (m_keyboard.key_down(SDL_SCANCODE_SPACE)) {
            if (m_engine->audio_manager.is_paused_music()) {
                m_engine->audio_manager.resume_music();

            }else if(m_engine->audio_manager.is_playing_music()) {
                m_engine->audio_manager.pause_music();

            }else{
                m_engine->audio_manager.play_music(m_music);
            }
        }
    }

private:
    const ora::Keyboard& m_keyboard;

    uint32_t m_music;
};

int main(int argc, char* argv[]) {
    
    TestAudio test;

    test.run();

    return 0;
}