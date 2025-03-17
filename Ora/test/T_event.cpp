#include "Log/Logger.hpp"
#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Time/Timer.hpp"
#include "Engine/Configuration.hpp"

int main(int argc, char* argv[]) {
    
    // Configuration
    ora::Configuration config;
    config.win_title = "Event and timer test";
    config.win_width = 800;
    config.win_height = 600;
    config.log_file_name = "test/log/Log_event_time.log";
    config.tim_fps = 120;

    ora::save_config_xml(config, "test/config.xml");

    // Init logger
    ora::_init_logger(config.log_state, "test/Log_T_Window.log");
    ora::Logger& logger = ora::Logger::instance();

    // Window
    ora::Window window(config.win_width, config.win_height, config.win_title, config.win_sdl_flags, config.win_win_flags);

    // Event
    ora::EventManager event_manager(&window);
    const ora::Keyboard& keyboard = event_manager.keyboard();
    const ora::Mouse& mouse = event_manager.mouse();

    // Timer
    ora::Timer timer(config.tim_fps);

    while(!event_manager.is_quitting()) {
        event_manager.manage();

        if (keyboard.key_down(ora::KEY_CODE_ESCAPE)) {
            event_manager.quit();
        }

        if (keyboard.key_down(ora::KEY_CODE_D)) {
            logger.log(ora::Info, "D down");
        }
        if (keyboard.key_press(ora::KEY_CODE_P)) {
            logger.log(ora::Info, "P press");
        }
        if (keyboard.key_up(ora::KEY_CODE_U)) {
            logger.log(ora::Info, "U up");
        }

        if (mouse.button_down(ora::MOUSE_LEFT)) {
            int x,y;
            mouse.mouse_position(x, y);
            logger.log(ora::Info, "Mouse position : " + std::to_string(x) + ", " + std::to_string(y));
        }
        if (mouse.button_press(ora::MOUSE_EXTRA_1)) {
            logger.log(ora::Info, "Mouse extra 1 press");
        }
        if (mouse.button_up(ora::MOUSE_RIGHT)) {
            logger.log(ora::Info, "Mouse right up");
        }

        window.present();
        timer.wait();
    }
    
    return 0;
}