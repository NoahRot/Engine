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

    int32_t texture_id2 = texture_manager.create_texture(100.0f, 100.0f, 0, 255, 127, 255);
    if (texture_id2 < 0) {
        logger.log(ora::Fatal, "Can not load texture2");
        exit(EXIT_FAILURE);
    }
    ora::Texture* texture2 = texture_manager.get_texture(texture_id2);

    // Shader
    ora::ShaderManager shader_manager;
    int32_t shader_id = shader_manager.load_shader("test/asset/triangle.vert", "test/asset/triangle.frag");
    if (shader_id < 0) {
        logger.log(ora::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }
    ora::Shader* shader = shader_manager.get_shader(shader_id);

    // Create a rectangle

    mat::Mat4f mvp = mat::orthographic3<float>(0.0f, window.get_width(), 0.0f, window.get_height(), 1.0f, -1.0f);

    mat::Mat4f model = mat::dot(mat::scale3<float>(2.0f), mat::translate3<float>(mat::Vec3f{100.0f, 100.0f, 0.0f}));

    struct Vertex {
        float x, y, z;
        float r, g, b;
        float u, v;
    };

    std::vector<Vertex> vertices = {
        Vertex{0.0f,    0.0f,   0.0f,       1.0f, 0.0f, 0.0f,   0.0f, 0.0f},
        Vertex{100.0f,  0.0f,   0.0f,       1.0f, 1.0f, 0.0f,   1.0f, 0.0f},
        Vertex{100.0f,  100.0f, 0.0f,       0.0f, 1.0f, 1.0f,   1.0f, 1.0f},
        Vertex{0.0f,    100.0f, 0.0f,       0.0f, 0.0f, 1.0f,   0.0f, 1.0f}
    };

    std::vector<uint32_t> indices = {
        0, 1, 2, // first Triangle
        2, 3, 0  // second Triangle
    };

    auto VBO = ora::create_vbo(vertices);
    auto EBO = ora::create_ibo(indices);

    ora::VertexAttribLayout layout;
    layout.add_float(3); // Add position
    layout.add_float(3); // Add color
    layout.add_float(2); // Add texture

    ora::VertexArray VAO;
    VAO.bind(); // Bind VAO before doing anything else
    VAO.add_vertex_buffer(VBO, layout);
    VAO.set_index_buffer(EBO);
    VAO.unbind();

    while (!event_manager.is_quitting())
    {
        event_manager.manage();

        shader->use_shader();
        shader->set_mat4f("u_mvp", mat::dot(mvp, model));
        texture->bind(0);
        VAO.bind();
        VAO.bind_index();
        glDrawElements(GL_TRIANGLES, VAO.get_index_buffer_size(), GL_UNSIGNED_INT, 0);
        VAO.unbind();

        shader->use_shader();
        shader->set_mat4f("u_mvp", mvp);
        texture2->bind(0);
        VAO.bind();
        VAO.bind_index();
        glDrawElements(GL_TRIANGLES, VAO.get_index_buffer_size(), GL_UNSIGNED_INT, 0);
        VAO.unbind();

        window.present();
        timer.wait();
    }
    

    return 0;
}