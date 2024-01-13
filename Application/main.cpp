#include <iostream>

#include "Engine.hpp"

int main(int argc, char** args) {

    eng::Configuration config;
    config.log_displayTXT = false;
    config.log_displayTXTName = "../Engine.log";
    config.win_name = "Engine DEMO";

    eng::Configure(config);

    eng::log::Logger& logger = eng::GetLogger();

    logger.Info("Main", "Program started");

    eng::Window& window = eng::GetWindow();

    eng::Event& event = eng::GetEvent();
    eng::Keyboard& keyboard = eng::GetKeyboard();
    eng::Mouse& mouse = eng::GetMouse();
    eng::Timer& timer = eng::GetTimer();
    eng::Renderer& renderer = eng::GetRenderer();

    logger.Info("Main", "Delta time in ms : " + std::to_string(timer.GetDeltaTime()));

    logger.Info("OpenGL", "Version : " + eng::InfoVersion());
    logger.Info("OpenGL", "Renderer : " + eng::InfoRenderer());
    logger.Info("OpenGL", "Shading language : " + eng::InfoShadingLanguage());
    logger.Info("OpenGL", "Vendor : " + eng::InfoVendor());
    logger.Info("OpenGL", "Number of texture slots : " + std::to_string(eng::GetMaxTextureSlots()));
    logger.Info("OpenGL", "Maximum number of attributes of a vertex : " + std::to_string(eng::GetMaxVertexAttributes()));

    renderer.SetClearColor(0.1f, 0.25f, 0.5f);

    eng::Shader shader("../shader/triangle.vert", "../shader/triangle.frag");
    if (!shader.IsValid()) {
        logger.Error("Main", "Shader unvalid");
    }

    while(eng::IsRunning()) {
        renderer.Clear();

        event.Manage();

        if(keyboard.KeyDown(SDL_SCANCODE_ESCAPE)) {
            eng::Quit();
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

        window.Present();
        timer.Loop();
    }

    logger.Info("Main", "Program ended");

    return 0;
}