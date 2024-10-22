#include <iostream>
#include <bitset>

#include "Log/Logger.hpp"
#include "Engine/Engine.hpp"
#include "Window/Window.hpp"

int main(int argc, char** args) {
    std::cout << "Hello World" << std::endl;

    ora::InitializationList init;
    init.log_file_name = "../orange.log";
    init.win_width = 640;
    init.win_height = 360;
    init.win_title = "Orange - DEMO";

    ora::OrangeEngine eng(init);

    while(!eng.event.is_quitting()) {
        eng.event.manage();

        if (eng.event.keyboard().key_down(SDL_SCANCODE_ESCAPE)) {
            eng.event.quit();
        }

        eng.timer.loop();
    }

    return 0;
}