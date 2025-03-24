#include "Engine/Configuration.hpp"
#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Time/Timer.hpp"

#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"

#include "Graphic/Shader.hpp"
#include "Graphic/Texture.hpp"

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

    // Event
    ora::EventManager event_manager(&window);
    //const ora::Keyboard& keyboard = event_manager.keyboard();
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
    mat::Vec2f sprite_dimension{16, 16};
    mat::Vec2f total_dimension{64, 64};
    mat::Vec2f origin{100, 100};

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

    mat::Mat4f mvp = mat::orthographic3<float>(0.0f, window.get_width(), 0.0f, window.get_height(), 1.0f, -1.0f);

    while (!event_manager.is_quitting())
    {
        event_manager.manage();

        sprite_batch.reset();
        animation.update(timer.get_delta_time());
        animation.add_to_batch(&sprite_batch, mat::Vec2f{100.0f, 100.0f}, {64.0f, 64.0f});
        sprite_batch.flush();

        normal_batch.reset();
        normal_sphere.add_to_batch(&normal_batch, {300.0f, 100.0f}, {(float)normal_texture->get_width(), (float)normal_texture->get_height()});
        normal_batch.flush();

        shader->use_shader();
        shader->set_mat4f("uProjection", mvp);
        sprite_batch.draw(shader);

        shader_light->use_shader();
        shader_light->set_mat4f("uProjection", mvp);
        shader_light->set_3f("uLightPos", mat::Vec3f{(float)mouse.mouse_x(), (float)mouse.mouse_y(), 0.0f});
        normal_batch.draw(shader_light);

        window.present();
        timer.wait();
    }
    

    return 0;
}