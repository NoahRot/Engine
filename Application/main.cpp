#include <iostream>

#include "Engine.hpp"

int main(int argc, char** args) {

    eng::Configuration config;
    config.log_displayTXT = true;
    config.log_displayTXTName = "../Engine.log";
    config.win_name = "Engine DEMO";

    eng::Configure(config);

    eng::log::Logger& logger = eng::log::Logger::Instance();

    logger.Info("Main", "Program started");

    eng::Window& window = eng::GetWindow();

    eng::Event& event = eng::GetEvent();
    eng::Keyboard& keyboard = eng::GetKeyboard();
    eng::Mouse& mouse = eng::GetMouse();
    eng::Timer& timer = eng::GetTimer();

    while(!event.IsQuitting()) {
        event.Manage();

        if(keyboard.KeyDown(SDL_SCANCODE_ESCAPE)) {
            event.Quit();
        }

        if(keyboard.KeyDown(SDL_SCANCODE_D)) {
            logger.Info("Main", "D DOWN");
        }
        if(keyboard.KeyUp(SDL_SCANCODE_U)) {
            logger.Info("Main", "U UP");
        }
        if(keyboard.KeyPress(SDL_SCANCODE_P)) {
            logger.Info("Main", "P PRESS");
        }

        if(mouse.MouseDown(eng::MouseButton::MouseLeft)) {
            int32_t x,y;
            mouse.MousePosition(x,y);
            logger.Info("Main", "Mouse position, x : " + std::to_string(x) + ", y : " + std::to_string(y));
        }

        timer.Loop();
    }

    logger.Info("Main", "Program ended");

    return 0;
}