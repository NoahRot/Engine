#include <iostream>
#include <bitset>

#include "Log/Logger.hpp"
#include "Engine/Engine.hpp"
#include "Window/Window.hpp"
#include "Orange.hpp"

int main(int argc, char** args) {
    std::cout << "Hello World" << std::endl;

    ora::Configuration init;
    init.log_file_name = "../orange.log";
    init.win_width = 640;
    init.win_height = 360;
    init.win_title = "Orange - DEMO";

    ora::OrangeEngine eng(init);

    // Create shader
    uint32_t shader = eng.shader_manager.load_shader("../shader/test.vert", "../shader/test.frag");
    if (shader == ora::UNVALID_32) {
        eng.logger.log(ora::Error, "Shader can not compile");
        exit(EXIT_FAILURE);
    }

    // Create triangle
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    float colors[] = {
         1.0f,  0.0f, 0.0f, 1.0,  // top right
         0.5f,  1.0f, 0.0f, 1.0,  // bottom right
         0.0f,  0.0f, 1.0f, 1.0,  // bottom left
         0.0f,  1.0f, 0.0f, 1.0   // top left 
    };

    std::vector<uint32_t> indices_2 = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    ora::VertexBuffer* VBO_Position = new ora::VertexBuffer(vertices, sizeof(vertices));
    ora::VertexBuffer* VBO_Color = new ora::VertexBuffer(colors, sizeof(colors));

    ora::IndexBuffer* EBO = new ora::IndexBuffer(indices_2);

    ora::VertexAttribLayout layout_position;
    if (!layout_position.add_float(3)) {
        std::cout << "Add float to layout 1" << std::endl;
    }

    ora::VertexAttribLayout layout_color;
    if (!layout_color.add_float(4)) {
        std::cout <<  "Add float to layout 2" << std::endl;
    }

    ora::VertexArray VAO;
    VAO.bind(); // Bind VAO before doing anything else
    VAO.add_vertex_buffer(VBO_Position, layout_position);
    VAO.add_vertex_buffer(VBO_Color, layout_color);
    VAO.set_index_buffer(EBO);


    while(!eng.event.is_quitting()) {
        eng.event.manage();

        if (eng.event.keyboard().key_down(SDL_SCANCODE_ESCAPE)) {
            eng.event.quit();
        }

        // Clear window
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        eng.shader_manager.use_shader(shader);
        VAO.bind(); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        VAO.bind_index();
        glDrawElements(GL_TRIANGLES, EBO->size(), GL_UNSIGNED_INT, 0);

        eng.window.present();

        eng.timer.loop();
    }
    
    return 0;
}