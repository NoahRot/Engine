#include <iostream>

#include "Engine.hpp"

#include "Math/Math.hpp"

int main(int argc, char** args) {

    eng::Configuration config;
    config.log_displayCMD = true;
    config.log_displayTXT = true;
    config.log_displayTXTName = "../Engine.log";
    config.win_name = "Engine DEMO";

    eng::configure(config);

    eng::log::Logger& logger = eng::get_logger();

    logger.info("Main", "Program started");

    eng::Window&        window          = eng::get_window();
    eng::Event&         event           = eng::get_event();
    eng::Keyboard&      keyboard        = eng::get_keyboard();
    eng::Mouse&         mouse           = eng::get_mouse();
    eng::Timer&         timer           = eng::get_timer();
    eng::Renderer2D&    renderer        = eng::get_renderer_2D();
    eng::AssetManager&  asset_manager   = eng::get_asset_manager();

    logger.info("Main", "Delta time in ms : " + std::to_string(timer.get_delta_time()));

    logger.info("OpenGL", "Version : " + eng::info_version());
    logger.info("OpenGL", "Renderer : " + eng::info_renderer());
    logger.info("OpenGL", "Shading language : " + eng::info_shading_language());
    logger.info("OpenGL", "Vendor : " + eng::info_vendor());
    logger.info("OpenGL", "Number of texture slots : " + std::to_string(eng::get_max_texture_slots()));
    logger.info("OpenGL", "Maximum number of attributes of a vertex : " + std::to_string(eng::get_max_vertex_attributes()));

    renderer.set_clear_color(0.1f, 0.25f, 0.5f);
    renderer.set_blend(true);

    eng::Index shader_index = asset_manager.load_shader("../shader/triangle.vert", "../shader/triangle.frag");
    eng::Shader shader = asset_manager.get_shader(shader_index);

    mat::Vec3f vecPosition({100.0f, 100.0f, 0.0f});
    mat::Mat4f displacement = mat::translate3<float>(vecPosition);
    mat::Mat4f scale = mat::scale3<float>(2.0f);

    eng::Camera2D camera(0, config.win_width, 0, config.win_height);

    // ==========
    // Test OpenGL - Make a triangle
    // ==========

    eng::Index font_index = asset_manager.load_font("../asset/font/OpenSans.ttf", 20);
    eng::Font_* font = asset_manager.get_font(font_index);

    eng::Index texture_index = asset_manager.load_texture("../asset/image/image.jpg");
    eng::Texture texture = asset_manager.get_texture(texture_index);
    //eng::Texture texture = asset_manager.get_texture(font->get_texture_index());
    
    //eng::Index tex_id_2 = asset_manager.load_texture("../asset/image/Saphir_logo_1.png");
    eng::Index tex_id_2 = asset_manager.create_texture(100, 100, eng::ColorBit{255, 0, 0, 255});
    eng::Texture texture2 = asset_manager.get_texture(tex_id_2);

    eng::Text text(font_index);
    text.add_text("Hello ", eng::ColorFloat{1, 0, 0, 1});
    text.add_text("World ", eng::ColorFloat{0, 1, 0, 1});
    text.generate();
    std::vector<eng::VertexText>& txt_vert = text.vertices();
    std::vector<uint32_t>& txt_indi = text.indices();

    eng::VertexArray txt_vao;
    txt_vao.Bind();
    eng::IndexBuffer txt_ibo(&txt_indi.front(), txt_indi.size());
    eng::VertexBuffer txt_vbo(&txt_vert.front(), txt_vert.size()*sizeof(eng::VertexText));
    eng::VertexAttributesLayout txt_layout;
    txt_layout.AddFloat(3); // Position
    txt_layout.AddFloat(2); // Texture coord
    txt_layout.AddFloat(3); // Color
    txt_vao.SetAttributes(txt_vbo, txt_layout);
    eng::Index txt_shader_id = asset_manager.load_shader("../shader/Text.vert", "../shader/Text.frag");
    eng::Shader txt_shader = asset_manager.get_shader(txt_shader_id);

    struct Vertex {
        float x, y, z; // Position
        float r, g, b; // Color
        float u, v;    // Texture coord
    };
    std::vector<Vertex> vertices = {
        Vertex{0.0f, 0.0f, 0.0f,        1.0f, 0.0f, 0.0f,   0.0f, 0.0f}, // Down left
        Vertex{100.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f}, // Dewn right
        Vertex{100.0f, 100.0f, 0.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f}, // Top right
        Vertex{0.0f, 100.0f, 0.0f,      0.0f, 1.0f, 1.0f,   0.0f, 1.0f}  // Top Left
    };

    std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    float angularVelocity = 0.00f;
    float angle = 0.0f;

    eng::VertexArray vao;
    vao.Bind();
    eng::IndexBuffer ibo(&indices.front(), indices.size());
    eng::VertexBuffer vbo(&vertices.front(), vertices.size()*sizeof(Vertex));

    eng::VertexAttributesLayout layout;
    layout.AddFloat(3); // Position
    layout.AddFloat(3); // Colors
    layout.AddFloat(2); // Texture coord

    vao.SetAttributes(vbo, layout);

    logger.debug("DEBUG", "Text generated");

    // ==========
    // ==========

    timer.create_point("event");
    timer.create_point("draw");
    timer.create_point("present");

    while(eng::is_running()) {
        renderer.clear();

        timer.start_point("event");
        event.manage();

        if(keyboard.key_down(SDL_SCANCODE_ESCAPE)) {
            eng::quit();
        }

        mat::Vec3f cam_disp;
        float cam_angle(0);
        float disp(2);
        float angle_disp(M_PI/60);
        if(keyboard.key_press(SDL_SCANCODE_W)) {
            cam_disp[1] -= disp;
        }
        if(keyboard.key_press(SDL_SCANCODE_S)) {
            cam_disp[1] += disp;
        }
        if(keyboard.key_press(SDL_SCANCODE_A)) {
            cam_disp[0] -= disp;
        }
        if(keyboard.key_press(SDL_SCANCODE_D)) {
            cam_disp[0] += disp;
        }
        if(keyboard.key_press(SDL_SCANCODE_Q)) {
            cam_angle += angle_disp;
        }
        if(keyboard.key_press(SDL_SCANCODE_E)) {
            cam_angle -= angle_disp;
        }
        if(keyboard.key_down(SDL_SCANCODE_RETURN)) {
            camera.set_position(mat::Vec3f({0.0f, 0.0f, 0.0f}));
            camera.set_rotation(0.0f);
        }
        camera.move_position(cam_disp);
        camera.move_rotation(cam_angle);

        timer.end_point("event");

        // ==========
        // Draw Triangle
        // ==========

        timer.start_point("draw");
        mat::Mat4f vp = camera.get_view_projection();

        angle += angularVelocity;
        mat::Mat4f rotation = mat::rotateZ(angle);
        mat::Vec3f centerPos({-50.0f, -50.0f, 0.0f});
        mat::Mat4f center = mat::translate3(centerPos);
        //mat::Mat4f mvp = mat::dot(vp, mat::dot(scale, mat::dot(displacement, mat::dot(rotation,center))));
        mat::Mat4f d1 = mat::translate3(mat::Vec3f{-50.0f, -50.0f, 0.0f});
        mat::Mat4f mvp = mat::dot(mat::dot(vp, scale), displacement);
        shader->bind();
        shader->set_uniform_mat4f("u_mvp", mvp);
        texture->bind(0);

        //shader->bind();
        //vao.Bind();
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        renderer.draw_vao(vao, ibo, shader);

        int32_t x, y;
        mouse.mouse_position(x, y);

        mat::Mat4f displacement2 = mat::translate3(mat::Vec3f({(float)x, (float)y, 0.0f}));
        center = mat::translate3(mat::Vec3f({-50.0f, -50.0f, 0.0f}));
        //mvp = mat::dot(mat::dot(vp, displacement2), center);
        mvp = vp;
        shader->set_uniform_mat4f("u_mvp", mvp);
        texture2->bind(0);

        //shader->bind();
        //vao.Bind();
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        renderer.draw_vao(vao, ibo, shader);

        displacement2 = mat::translate3(mat::Vec3f{200.0f, 200.0f, 0.0f});
        mat::Mat4f txt_mvp = vp;
        txt_shader->bind();
        txt_shader->set_uniform_mat4f("u_MVP", txt_mvp);
        text.bind_font();
        renderer.draw_vao(txt_vao, txt_ibo, txt_shader);

        timer.end_point("draw");
        // ==========
        // ==========

        if(mouse.mouse_down(eng::MouseButton::MouseLeft)) {
            int32_t x,y;
            mouse.mouse_position(x,y);
            logger.info("Main", "Mouse position, x : " + std::to_string(x) + ", y : " + std::to_string(y));
        }

        timer.start_point("present");
        window.present();
        timer.end_point("present");

        timer.loop();
    }

    auto time_map = timer.get_map_time_point();
    for (auto element : time_map) {
        std::cout << "TIME | Event " << element.first << ", time " << element.second.get_mean_delta() << std::endl;
    }

    std::cout << "TIME | Event Total, time " << timer.get_total_frame_point().get_mean_delta() << std::endl;
    
    logger.info("Main", "End programm");

    mat::Mat4f m1 = mat::translate3(mat::Vec3f{20.0f, 10.0f, 5.0f});
    math::Mat4f m2 = math::translate3(math::Vec3f({20.0f, 10.0f, 5.0f}));

    std::cout << m1 << std::endl << m2 << std::endl;

    return 0;
}