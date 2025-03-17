#include "Audio/AudioManager.hpp"
#include "Engine/Configuration.hpp"
#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Time/Timer.hpp"

int main(int argc, char* argv[]) {

    // Configuration
    ora::Configuration config;
    config.win_title = "Audio test";
    config.win_width = 800;
    config.win_height = 600;
    config.log_file_name = "test/log/Log_audio.log";
    config.tim_fps = 120;

    ora::save_config_xml(config, "test/log/config.xml");

    // Init logger
    ora::_init_logger(config.log_state, config.log_file_name);
    ora::Logger& logger = ora::Logger::instance();

    // Window
    ora::Window window(config.win_width, config.win_height, config.win_title, config.win_sdl_flags, config.win_win_flags);

    // Event
    ora::EventManager event_manager(&window);
    const ora::Keyboard& keyboard = event_manager.keyboard();
    const ora::Mouse& mouse = event_manager.mouse();

    // Timer
    ora::Timer timer(config.tim_fps);

    // Audio manager
    ora::AudioManager audio(config.aud_mix_flags, config.aud_frequency, config.aud_format, config.aud_channels, config.aud_chunksize);

    int32_t music_id = audio.load_music("test/asset/Sky Corsair.mp3");
    if (music_id < 0) {
        logger.log(ora::Fatal, "Can not load music");
        exit(EXIT_FAILURE);
    }
    ora::Music* music = audio.get_music(music_id);

    int32_t sound_id = audio.load_sound("test/asset/but.wav");
    if (sound_id < 0) {
        logger.log(ora::Fatal, "Can not load sound");
        exit(EXIT_FAILURE);
    }
    ora::Sound* sound = audio.get_sound(sound_id);

    while (!event_manager.is_quitting())
    {
        event_manager.manage();

        if (keyboard.key_down(ora::KEY_CODE_SPACE)) {
            if (music->is_playing()) {
                if (music->is_paused()) {
                    music->resume();
                }else{
                    music->pause();
                }
            }else{
                music->play();
            }
        }

        if (keyboard.key_down(ora::KEY_CODE_RETURN)) {
            if (music->is_playing()) {
                music->stop();
            }
        }

        if (keyboard.key_down(ora::KEY_CODE_S)) {
            sound->play();
        }

        if (keyboard.key_press(ora::KEY_CODE_UP)) {
            float current_vol = music->get_volume();
            music->volume(current_vol + 0.05);
        }
        if (keyboard.key_press(ora::KEY_CODE_DOWN)) {
            float current_vol = music->get_volume();
            music->volume(current_vol - 0.05);
        }

        window.present();
        timer.wait();
    }
    

    return 0;
}