#include "Audio/AudioManager.hpp"
#include "Engine/Configuration.hpp"
#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Time/Timer.hpp"

#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"

#include "Graphic/Shader.hpp"
#include "Graphic/Texture.hpp"

#include "Text/Font.hpp"
#include "Text/Text.hpp"

int main(int argc, char* argv[]) {

    // Configuration
    ora::Configuration config;
    config.win_title = "Buffer test";
    config.win_width = 800;
    config.win_height = 600;
    config.log_file_name = "test/log/Log_texture.log";
    config.tim_fps = 120;

    // Init logger
    ora::_init_logger(config.log_state, config.log_file_name);
    ora::Logger& logger = ora::Logger::instance();

    // Window
    ora::Window window(config.win_width, config.win_height, config.win_title, config.win_sdl_flags, config.win_win_flags);

    // Event
    ora::EventManager event_manager(&window);
    const ora::Keyboard& keyboard = event_manager.keyboard();
    //const ora::Mouse& mouse = event_manager.mouse();

    // Timer
    ora::Timer timer(config.tim_fps);

    // Texture
    ora::TextureManager texture_manager(true);
    int32_t texture_id = texture_manager.load_texture("test/asset/Feather.png");
    if (texture_id < 0) {
        logger.log(ora::Fatal, "Can not load texture");
        exit(EXIT_FAILURE);
    }
    ora::Texture* texture = texture_manager.get_texture(texture_id);

    // Shader
    ora::ShaderManager shader_manager;
    int32_t shader_id = shader_manager.load_shader("test/asset/Text.vert", "test/asset/Text.frag");
    if (shader_id < 0) {
        logger.log(ora::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }
    ora::Shader* shader = shader_manager.get_shader(shader_id);

    // Font
    ora::FontManager font_manager(texture_manager);
    int32_t font_id = font_manager.load_font("test/asset/OpenSans.ttf", 32);
    if (font_id < 0) {
        logger.log(ora::Fatal, "Can not load font");
        exit(EXIT_FAILURE);
    }
    ora::Font* font = font_manager.get_font(font_id);

    logger.log(ora::Debug, "Size of vertex text structure : " + std::to_string(sizeof(ora::VertexText)));

    ora::TextRenderer text_renderer(font, shader, 6);
    text_renderer.submit_text("Hello World", mat::Vec2f{100.0f, 100.0f}, 255, 255, 255);
    text_renderer.submit_text("FreeType", mat::Vec2f{300.0f, 400.0f}, 255, 0, 255);
    text_renderer.flush();

    // Create a rectangle

    mat::Mat4f mvp = mat::orthographic3<float>(0.0f, window.get_width(), 0.0f, window.get_height(), 1.0f, -1.0f);

    glClearColor(0.0f, 0.1f, 0.2f, 1.0f);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    glEnable(GL_BLEND);

    while (!event_manager.is_quitting())
    {
        event_manager.manage();
        glClear(GL_COLOR_BUFFER_BIT);

        if (keyboard.key_down(ora::KEY_CODE_SPACE)) {
            text_renderer.reset();
            text_renderer.submit_text("SPACE !", mat::Vec2f{200.0f, 50.0f}, 0, 255, 150);
            text_renderer.flush();
        }

        ora::Shader* shader_text = text_renderer.get_shader();
        shader_text->use_shader();
        shader_text->set_mat4f("u_mvp", mvp);
        text_renderer.draw();

        window.present();
        timer.wait();
    }
    

    return 0;
}