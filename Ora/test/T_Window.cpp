#include "Window/Window.hpp"
#include "Engine/Configuration.hpp"

int main(int argc, char* argv[]) {
    
    ora::Configuration config;
    config.win_width = 800;
    config.win_height = 600;
    ora::_init_logger(config.log_state, "test/Log_T_Window.log");

    config.win_title = "Test Window";
    ora::Window window(config.win_width, config.win_height, config.win_title, config.win_sdl_flags, config.win_win_flags);
    window.present();

    SDL_Delay(1000);
    
    return 0;
}