#include "Audio/AudioManager.hpp"
#include "Engine/Configuration.hpp"
#include "Window/Window.hpp"
#include "Event/Event.hpp"
#include "Time/Timer.hpp"

#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"

#include "Graphic/Shader.hpp"

int main(int argc, char* argv[]) {

    // Configuration
    ora::Configuration config;
    config.win_title = "Buffer test";
    config.win_width = 800;
    config.win_height = 600;
    config.log_file_name = "test/log/Log_buffer.log";
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

    // Shader
    ora::ShaderManager shader_manager;
    int32_t shader_id = shader_manager.load_shader("test/asset/Color.vert", "test/asset/Color.frag");
    if (shader_id < 0) {
        logger.log(ora::Fatal, "Can not load shader");
        exit(EXIT_FAILURE);
    }
    ora::Shader* shader = shader_manager.get_shader(shader_id);



    int32_t shader_id2 = shader_manager.load_shader("test/asset/triangle.vert", "test/asset/triangle.frag");
    if (shader_id2 < 0) {
        logger.log(ora::Fatal, "Can not load shader2");
        exit(EXIT_FAILURE);
    }
    ora::Shader* shader2 = shader_manager.get_shader(shader_id2);
    auto map = shader2->get_uniform_map();
    for (auto i : map) {
        std::cout << "UNIFORM : " << i.first << ", ID : " << i.second << std::endl;
    }

    // Create a rectangle

    std::vector<float> vertices = {
        0.5f, 0.5f, 0.0f,  // top right
        0.5f, 0.0f, 0.0f,  // bottom right
        0.0f, 0.0f, 0.0f,  // bottom left
        0.0f, 0.5f, 0.0f   // top left 
    };

    std::vector<float> colors = {
         1.0f,  0.0f, 0.0f, 1.0,  // top right
         0.5f,  1.0f, 0.0f, 1.0,  // bottom right
         0.0f,  0.0f, 1.0f, 1.0,  // bottom left
         0.0f,  1.0f, 0.0f, 1.0   // top left 
    };

    std::vector<uint32_t> indices = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    auto VBO_Position = ora::create_vbo(vertices);
    auto VBO_Color = ora::create_vbo(colors);

    auto EBO = ora::create_ibo(indices);

    ora::VertexAttribLayout layout_position;
    layout_position.add_float(3); // Add position

    ora::VertexAttribLayout layout_color;
    layout_color.add_float(4); // Add color

    ora::VertexArray VAO;
    VAO.bind(); // Bind VAO before doing anything else
    VAO.add_vertex_buffer(VBO_Position, layout_position);
    VAO.add_vertex_buffer(VBO_Color, layout_color);
    VAO.set_index_buffer(EBO);
    VAO.unbind();

    while (!event_manager.is_quitting())
    {
        event_manager.manage();

        shader->use_shader();
        VAO.bind();
        VAO.bind_index();
        glDrawElements(GL_TRIANGLES, VAO.get_index_buffer_size(), GL_UNSIGNED_INT, 0);
        VAO.unbind();

        window.present();
        timer.wait();
    }
    

    return 0;
}