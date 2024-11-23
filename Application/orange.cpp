#include <iostream>
#include <bitset>

#include "Log/Logger.hpp"
#include "Engine/Engine.hpp"
#include "Window/Window.hpp"
#include "Orange.hpp"

#include "Graphic/Transform.hpp"

int main(int argc, char** args) {
    std::cout << "Hello World" << std::endl;

    ora::Configuration init;
    init.log_file_name = "../orange.log";
    init.win_width = 640;
    init.win_height = 360;
    init.win_title = "Orange - DEMO";
    init.tim_fps = 60;

    ora::OrangeEngine eng(init);

    ora::Renderer renderer(&eng.shader_manager);

    // Set clear color
    renderer.set_clear_color(0.05f, 0.1f, 0.2f);

    // Create shader
    uint32_t shader = eng.shader_manager.load_shader("../shader/test.vert", "../shader/test.frag");
    if (shader == ora::UNVALID_32) {
        eng.logger.log(ora::Error, "Shader can not compile");
        exit(EXIT_FAILURE);
    }

    // Load texture
    uint32_t texture = eng.texture_manager.load_texture("../asset/image/image.jpg", true);
    if (texture == ora::UNVALID_32) {
        eng.logger.log(ora::Error, "Can not load texture");
        exit(EXIT_FAILURE);
    }

    // Background
    ora::VertexBuffer* VBO_Background = nullptr;
    ora::IndexBuffer* IBO_Background = nullptr;
    uint32_t shader_Background;

    ora::VertexArray VAO_Background;
    VAO_Background.unbind();
    {
        std::vector<float> vertices = {
            0.0f,                           0.0f,                           0.99f,    // Bottom left
            0.0f,                           (float)eng.window.get_height(), 0.99f,    // Bottom right
            (float)eng.window.get_width(),  (float)eng.window.get_height(), 0.99f,    // Top right
            (float)eng.window.get_width(),  0.0f,                           0.99f,    // Top left
        };

        std::vector<uint32_t> indices = {
            0, 1, 2,
            2, 3, 0
        };

        VBO_Background = new ora::VertexBuffer(&vertices.front(), sizeof(float)*vertices.size());
        IBO_Background = new ora::IndexBuffer(indices);
        ora::VertexAttribLayout layout;
        layout.add_float(3);

        VAO_Background.bind();
        VAO_Background.add_vertex_buffer(VBO_Background, layout);
        VAO_Background.set_index_buffer(IBO_Background);
        VAO_Background.unbind();

        shader_Background = eng.shader_manager.load_shader("../shader/Background.vert", "../shader/Background.frag");
        if (shader_Background == ora::UNVALID_32) {
            eng.logger.log(ora::Error, "Shader can not compile");
            exit(EXIT_FAILURE);
        }
    }

    // Create triangle
    float vertices[] = {
        100.0f, 100.0f, 0.0f,  // top right
        100.0f, 0.0f,   0.0f,  // bottom right
        0.0f,   0.0f,   0.0f,  // bottom left
        0.0f,   100.0f, 0.0f   // top left 
    };

    float colors[] = {
         1.0f,  0.0f, 0.0f, 1.0,  // top right
         0.5f,  1.0f, 0.0f, 1.0,  // bottom right
         0.0f,  0.0f, 1.0f, 1.0,  // bottom left
         0.0f,  1.0f, 0.0f, 1.0   // top left 
    };

    float textureCoord[] = {
        1.0f, 1.0f,     // top right
        1.0f, 0.0f,     // bottom right
        0.0f, 0.0f,     // bottom left
        0.0f, 1.0f      // top left 
    };

    std::vector<uint32_t> indices_2 = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    ora::VertexBuffer* VBO_Position = new ora::VertexBuffer(vertices, sizeof(vertices));
    ora::VertexBuffer* VBO_Color = new ora::VertexBuffer(colors, sizeof(colors));
    ora::VertexBuffer* VBO_texture = new ora::VertexBuffer(textureCoord, sizeof(textureCoord));

    ora::IndexBuffer* EBO = new ora::IndexBuffer(indices_2);

    ora::VertexAttribLayout layout_position;
    if (!layout_position.add_float(3)) {
        std::cout << "Add float to layout 1" << std::endl;
    }

    ora::VertexAttribLayout layout_color;
    if (!layout_color.add_float(4)) {
        std::cout <<  "Add float to layout 2" << std::endl;
    }

    ora::VertexAttribLayout layout_texture;
    if (!layout_texture.add_float(2)) {
        std::cout <<  "Add float to layout 3" << std::endl;
    }

    ora::VertexArray VAO;
    VAO.bind(); // Bind VAO before doing anything else
    VAO.add_vertex_buffer(VBO_Position, layout_position);
    VAO.add_vertex_buffer(VBO_Color, layout_color);
    VAO.add_vertex_buffer(VBO_texture, layout_texture);
    VAO.set_index_buffer(EBO);

    // Sprite transform
    ora::Transform2D transform;
    transform.position = mat::Vec3f{0.0f, 0.0f, 0.0f};
    transform.centre = mat::Vec3f{50.0f, 50.0f, 0.0f};
    transform.rotation = 0.0f;

    // MVP Matrix
    mat::Mat4f mvp = mat::orthographic3<float>(0.0f, eng.window.get_width(), 0.0f, eng.window.get_height(), 1.0f, -1.0f);
    mvp = mat::dot(mvp, mat::scale3<float>(2.0f));

    ora::Camera2D camera(&eng.window, false);

    mat::Vec3f mouse_tmp_position{0.0f, 0.0f, 0.0f};
    mat::Vec3f cam_pos_0{0.0f, 0.0f, 0.0f};

    uint32_t font = eng.font_manager.load_font("../asset/font/OpenSans.ttf", 40);
    if (font == ora::UNVALID_32) {
        eng.logger.log(ora::Error, "Can not load font");
        exit(EXIT_FAILURE);
    }

    VAO.unbind();

    std::vector<ora::VertexText> txt_vertex;
    std::vector<uint32_t> txt_index;

    uint32_t shader_txt = eng.shader_manager.load_shader("../shader/Text.vert", "../shader/Text.frag");
    if (shader_txt == ora::UNVALID_32) {
        eng.logger.log(ora::Error, "Can not load text shader");
        exit(EXIT_FAILURE);
    }

    ora::VertexAttribLayout layout_txt;
    layout_txt.add_float(3);
    layout_txt.add_float(2);
    layout_txt.add_float(3);

    ora::Batch<ora::VertexText> batch_txt;

    ora::create_text("Orange Engine", eng.font_manager.get_font(font), 255, 125, 0, txt_vertex, txt_index);
    batch_txt.add(txt_vertex, txt_index);

    ora::create_text("Batch testing", eng.font_manager.get_font(font), 255, 125, 0, txt_vertex, txt_index);
    for (auto& i : txt_vertex) {
        i.x += 300;
        i.y -= 100;
    }
    batch_txt.add(txt_vertex, txt_index);

    batch_txt.set_shader(shader_txt);
    batch_txt.generate(layout_txt);

    // Enable blend
    renderer.set_blend(true);
    renderer.set_depth_test(true);

    ora::Chrono chrono;
    chrono.set_time_point();

    while(!eng.event.is_quitting()) {

        eng.event.manage();

        if (eng.event.keyboard().key_down(SDL_SCANCODE_ESCAPE)) {
            eng.event.quit();
        }

        if (eng.event.keyboard().key_press(SDL_SCANCODE_W)) {
            transform.position += mat::Vec3f{0.0f, 5.0f, 0.0f};
            //camera.move(mat::Vec3f{0.0f, 5.0f, 0.0f});
        }
        if (eng.event.keyboard().key_press(SDL_SCANCODE_S)) {
            transform.position += mat::Vec3f{0.0f, -5.0f, 0.0f};
            //camera.move(mat::Vec3f{0.0f, -5.0f, 0.0f});
        }
        if (eng.event.keyboard().key_press(SDL_SCANCODE_A)) {
            transform.position += mat::Vec3f{-5.0f, 0.0f, 0.0f};
            //camera.move(mat::Vec3f{-5.0f, 0.0f, 0.0f});
        }
        if (eng.event.keyboard().key_press(SDL_SCANCODE_D)) {
            transform.position += mat::Vec3f{5.0f, 0.0f, 0.0f};
            //camera.move(mat::Vec3f{5.0f, 0.0f, 0.0f});
        }

        if (eng.event.keyboard().key_press(SDL_SCANCODE_Q)) {
            transform.rotation += 0.01*M_PI;
        }
        if (eng.event.keyboard().key_press(SDL_SCANCODE_E)) {
            transform.rotation -= 0.01*M_PI;
        }

        if (eng.event.mouse().button_down(ora::MouseButton::MOUSE_RIGHT)) {
            int x, y;
            eng.event.mouse().mouse_position(x, y);
            mouse_tmp_position[0] = x;
            mouse_tmp_position[1] = y;

            cam_pos_0 = camera.get_position();
        }
        if (eng.event.mouse().button_press(ora::MouseButton::MOUSE_RIGHT)) {
            int x, y;
            eng.event.mouse().mouse_position(x, y);
            mat::Vec3f mouse_current{(float)x, (float)y, 0.0f};

            camera.set_position(cam_pos_0 + mouse_current - mouse_tmp_position);
        }

        if (eng.event.mouse().button_down(ora::MouseButton::MOUSE_LEFT)) {
            int x, y;
            eng.event.mouse().mouse_position(x, y);
            eng.logger.log(ora::Debug, "Mouse position = (" + std::to_string(x) + ", " + std::to_string(y) + ")");
        }

        // Clear window
        renderer.clear();

        // Update
        mat::Mat4f model = ora::model_matrix(transform); 
        mvp = mat::dot(camera.get_proj(), mat::dot(camera.get_view(), model));

        // Draw
        eng.shader_manager.use_shader(shader_Background);
        eng.shader_manager.set_unif_mat4f(shader_Background, "u_Proj", camera.get_proj());
        eng.shader_manager.set_unif_3f(shader_Background, "u_cam_position", camera.get_position());
        renderer.draw(VAO_Background);


        eng.shader_manager.use_shader(shader);
        eng.shader_manager.set_unif_mat4f(shader, "u_MVP", mvp);
        eng.texture_manager.bind_texture(texture, 0);
        renderer.draw(VAO);


        mat::Mat4f displacement_txt = mat::translate3(mat::Vec3f{50.0f, 200.0f, -1.0f});
        eng.shader_manager.use_shader(batch_txt.get_shader());
        eng.shader_manager.set_unif_mat4f(batch_txt.get_shader(), "u_MVP", mat::dot(camera.get_proj(), displacement_txt));
        eng.font_manager.bind_texture(font);
        renderer.draw(batch_txt);
        
        chrono.accumulate();
        
        eng.timer.loop();
        chrono.set_time_point();

        eng.window.present();
        }

    eng.logger.log(ora::LogLevel::Debug, "Mean frame time = " + std::to_string(chrono.get_accumulate_mean()));
    eng.logger.log(ora::LogLevel::Debug, "Delta time = " + std::to_string(eng.timer.get_delta_time()));

    return 0;
}