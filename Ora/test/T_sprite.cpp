#include "Engine/Configuration.hpp"
#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Time/Timer.hpp"
#include "Time/Chrono.hpp"
#include "Time/TimePoint.hpp"

#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"

#include "Graphic/Shader.hpp"
#include "Graphic/Texture.hpp"

#include "Graphic/Renderer.hpp"

#include "Sprite/Sprite.hpp"

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

    // Renderer
    ora::Renderer& renderer = ora::Renderer::instance();
    renderer.set_clear_color(5, 10, 20);
    renderer.set_blend(true);

    // Event
    ora::EventManager event_manager(&window);
    const ora::Keyboard& keyboard = event_manager.keyboard();
    const ora::Mouse& mouse = event_manager.mouse();

    // Timer
    ora::Timer timer(config.tim_fps);

    // Texture
    ora::TextureManager texture_manager(true);
    int32_t texture_id = texture_manager.load_texture("test/asset/fruit.png");
    if (texture_id < 0) {
        logger.log(ora::Fatal, "Can not load texture");
        exit(EXIT_FAILURE);
    }
    ora::Texture* texture = texture_manager.get_texture(texture_id);

    // Shader
    ora::ShaderManager shader_manager;
    int32_t shader_id = shader_manager.load_shader("test/asset/sprite.vert", "test/asset/sprite.frag");
    if (shader_id < 0) {
        logger.log(ora::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }
    ora::Shader* shader = shader_manager.get_shader(shader_id);

    int32_t shader_light_id = shader_manager.load_shader("test/asset/sprite_light.vert", "test/asset/sprite_light.frag");
    if (shader_light_id < 0) {
        logger.log(ora::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }
    ora::Shader* shader_light = shader_manager.get_shader(shader_light_id);

    // Sprites
    ora::SpriteBatch sprite_batch(texture, shader, 1024);

    ora::SpriteSheet sprite_sheet(texture, 16, 16);

    ora::SpriteAnimation animation(&sprite_sheet, 0, 1, 2, 1, 100);
    sprite_batch.flush();

    uint32_t normal_texture_id = texture_manager.load_texture("test/asset/normal_sphere.png");
    if (normal_texture_id < 0) {
        logger.log(ora::Fatal, "Can not load normal sphere");
        exit(EXIT_FAILURE);
    }
    ora::Texture* normal_texture = texture_manager.get_texture(normal_texture_id);
    ora::Sprite normal_sphere(normal_texture);
    ora::SpriteBatch normal_batch(normal_texture, normal_texture, shader_light, 8);

    // Create matrices
    ora::Camera2D camera(window.get_width(), window.get_height());

    // Create chrono
    ora::Chrono frame_chrono;
    frame_chrono.reset();

    while (!event_manager.is_quitting())
    {
        frame_chrono.start();

        event_manager.manage();

        renderer.clear();

        sprite_batch.reset();
        animation.update(timer.get_delta_time());
        animation.add_to_batch(&sprite_batch, mat::Vec2f{100.0f, 100.0f}, {64.0f, 64.0f});
        sprite_batch.flush();

        normal_batch.reset();
        normal_sphere.add_to_batch(&normal_batch, {300.0f, 100.0f}, {(float)normal_texture->get_width(), (float)normal_texture->get_height()});
        normal_batch.flush();

        if (keyboard.key_press(ora::KEY_CODE_W)) {
            camera.move_position(mat::Vec2f{0.0f, 5.0f});
        }
        if (keyboard.key_press(ora::KEY_CODE_S)) {
            camera.move_position(mat::Vec2f{0.0f, -5.0f});
        }
        if (keyboard.key_press(ora::KEY_CODE_A)) {
            camera.move_position(mat::Vec2f{-5.0f, 0.0f});
        }
        if (keyboard.key_press(ora::KEY_CODE_D)) {
            camera.move_position(mat::Vec2f{5.0f, 0.0f});
        }

        if (keyboard.key_press(ora::KEY_CODE_UP)) {
            camera.zoom(1.01f);
        }
        if (keyboard.key_press(ora::KEY_CODE_DOWN)) {
            camera.zoom(1.0f/1.01f);
        }
        camera.compute_matrix();

        mat::Mat4f mvp = camera.get_vp();

        shader->use_shader();
        shader->set_mat4f("uProjection", mvp);
        sprite_batch.draw(shader);

        shader_light->use_shader();
        shader_light->set_mat4f("uProjection", mvp);
        shader_light->set_3f("uLightPos", mat::Vec3f{(float)mouse.mouse_x(), (float)mouse.mouse_y(), 0.0f});
        normal_batch.draw(shader_light);

        window.present();

        frame_chrono.end();
        timer.wait();

    }
    
    logger.log(ora::Debug, "Mean time frame : " + std::to_string(frame_chrono.get_mean_time()) + " ms");

    return 0;
}