#include <iostream>

#include "Engine.hpp"

#include "Math/Math.hpp"

int main(int argc, char** args) {

    eng::Configuration config;
    config.log_displayTXT = false;
    config.log_displayTXTName = "../Engine.log";
    config.win_name = "Engine DEMO";

    eng::configure(config);

    eng::log::Logger& logger = eng::get_logger();

    logger.info("Main", "Program started");

    eng::Window& window = eng::get_window();
    eng::Event& event = eng::get_event();
    eng::Keyboard& keyboard = eng::get_keyboard();
    eng::Mouse& mouse = eng::get_mouse();
    eng::Timer& timer = eng::get_timer();
    eng::Renderer& renderer = eng::get_renderer();
    eng::AssetManager& asset_manager = eng::AssetManager::instance();

    logger.info("Main", "Delta time in ms : " + std::to_string(timer.get_delta_time()));

    logger.info("OpenGL", "Version : " + eng::info_version());
    logger.info("OpenGL", "Renderer : " + eng::info_renderer());
    logger.info("OpenGL", "Shading language : " + eng::info_shading_language());
    logger.info("OpenGL", "Vendor : " + eng::info_vendor());
    logger.info("OpenGL", "Number of texture slots : " + std::to_string(eng::get_max_texture_slots()));
    logger.info("OpenGL", "Maximum number of attributes of a vertex : " + std::to_string(eng::get_max_vertex_attributes()));

    renderer.SetClearColor(0.1f, 0.25f, 0.5f);

    eng::Shader shader("../shader/triangle.vert", "../shader/triangle.frag");
    if (!shader.IsValid()) {
        logger.error("Main", "Shader unvalid");
    }else{
        logger.info("Main", "Shader compiled");
    }

    math::Mat4f orthographic = math::Orthographic3<float>(0, config.win_width, 0, config.win_height, 1, -1);
    math::Vec3f vecPosition({100.0f, 100.0f, 0.0f});
    math::Mat4f displacement = math::Translate3<float>(vecPosition);
    math::Mat4f scale = math::Scale3<float>(2.0f);

    math::Matrix<float, 2, 2> m1({
        math::Vec2f({2.0f, 1.5f}),
        math::Vec2f({-3.0f, -1.0f})
    });

    math::Matrix<float, 3, 2> m2({
        math::Vec3f({1.0f, 3.0f, 2.0f}),
        math::Vec3f({-2.5f, 2.0f, -2.0f})
    });

    // ==========
    // Test OpenGL - Make a triangle
    // ==========
    struct Vertex {
        float x, y, z; // Position
        float r, g, b; // Color
        float u, v;    // Texture coord
    };
    std::vector<Vertex> vertices = {
        Vertex{0.0f, 0.0f, 0.0f,        1.0f, 0.0f, 0.0f,   0.0f, 0.0f}, // Down left
        Vertex{100.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f}, // Dewn right
        Vertex{100.0f, 100.0f, 0.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f}, // Top right
        Vertex{0.0f, 100.0f, 0.0f,      0.0f, 1.0f, 1.0f,   0.0f, 1.0f} // Top Left
    };

    std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    float angularVelocity = 0.01f;
    float angle = 0.0f;

    eng::VertexArray vao;
    vao.Bind();
    eng::IndexBuffer ibo(&indices.front(), indices.size()*sizeof(uint32_t));
    eng::VertexBuffer vbo(&vertices.front(), vertices.size()*sizeof(Vertex));

    eng::VertexAttributesLayout layout;
    layout.AddFloat(3); // Position
    layout.AddFloat(3); // Colors
    layout.AddFloat(2); // Texture coord

    vao.SetAttributes(vbo, layout);

    eng::Texture* texture = eng::CreateTexture("../asset/image/image.jpg", false);
    if (texture) {
        logger.debug("Main", "Texture loaded");
    }else{
        logger.debug("Main", "Can't load texture");
    }
    if(!texture->Load("../asset/image/image.jpg", true)) {
        logger.debug("Main", "Texture not overwritten");
    }

    //eng::Music* music = eng::CreateMusic("../asset/music/Sky Corsair.mp3");
    eng::Index music_index = asset_manager.load_asset("../asset/music/Sky Corsair.mp3", eng::AssetType::Music);
    eng::Music music = asset_manager.get_music(music_index);
    //eng::Sound* sound = eng::CreateSound("../asset/sound/but.wav");
    eng::Index sound_index = asset_manager.load_asset("../asset/sound/but.wav", eng::AssetType::Sound);
    eng::Sound_* sound = asset_manager.get_asset<eng::Sound_>(sound_index);
    if (music and sound) {
        logger.debug("Main", "Music and sound loaded successfully");
        music->volume(0.5f);
        music->play();
        sound->volume(0.5f);
    }else{
        logger.debug("Main", "Music can't be loaded");
    }

    eng::Font font = eng::CreateFont("../asset/font/Traffic.ttf", 32);
    if (font) {
        logger.info("Main", "Font created");
    }else{
        logger.error("Main", "Can't load font");
    }
    eng::Text text;
    //text.Generate(font, "Hello world");

    std::vector<Vertex> vert = {
        Vertex{0.0f, 0.0f, 0.0f,        1.0f, 0.0f, 0.0f,   0.0f, 0.0f}, // Down left
        Vertex{20.0f, 0.0f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 0.0f}, // Dewn right
        Vertex{20.0f, 20.0f, 0.0f,      1.0f, 0.0f, 0.0f,   1.0f, 1.0f}, // Top right
        Vertex{0.0f, 20.0f, 0.0f,       1.0f, 0.0f, 0.0f,   0.0f, 1.0f} // Top Left
    };

    std::vector<uint32_t> ind = {
        0, 1, 3,
        1, 2, 3
    };

    eng::VertexArray vao2;
    vao2.Bind();
    eng::IndexBuffer ibo2(&indices.front(), indices.size()*sizeof(uint32_t));
    eng::VertexBuffer vbo2(&vertices.front(), vertices.size()*sizeof(Vertex));
    vao.SetAttributes(vbo2, layout);
    eng::Texture* texture2 = eng::CreateTexture("../asset/image/Saphir_logo_1.png");

    logger.debug("DEBUG", "Text generated");

    // ==========
    // ==========

    while(eng::is_running()) {
        renderer.Clear();

        event.manage();

        if(keyboard.key_down(SDL_SCANCODE_ESCAPE)) {
            eng::quit();
        }

        if(keyboard.key_down(SDL_SCANCODE_D)) {
            logger.info("Main", "D DOWN");
        }
        if(keyboard.key_up(SDL_SCANCODE_U)) {
            logger.info("Main", "U UP");
        }
        if (keyboard.key_down(SDL_SCANCODE_SPACE)) {
            sound->play();
        }
        // ==========
        // Draw Triangle
        // ==========
        angle += angularVelocity;
        math::Mat4f rotation = math::RotateZ(angle);
        math::Vec3f centerPos({-50.0f, -50.0f, 0.0f});
        math::Mat4f center = math::Translate3(centerPos);
        math::Mat4f mvp = orthographic*scale*displacement*rotation*center;
        shader.SetUniformMat4f("u_mvp", mvp);
        shader.Bind();
        vao.Bind();
        texture->Bind(0);
        // glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        math::Vec3f dis({300.0f, 50.0f, 0.0f});
        math::Mat4f disM = math::Translate3(dis);
        mvp = orthographic*scale*disM;
        shader.SetUniformMat4f("u_mvp", mvp);
        shader.Bind();
        vao2.Bind();
        texture2->Bind(0);
        glDrawElements(GL_TRIANGLES, ind.size(), GL_UNSIGNED_INT, 0);

        // ==========
        // ==========

        if(mouse.mouse_down(eng::MouseButton::MouseLeft)) {
            int32_t x,y;
            mouse.mouse_position(x,y);
            logger.info("Main", "Mouse position, x : " + std::to_string(x) + ", y : " + std::to_string(y));
        }

        window.present();
        timer.loop();
    }

    eng::DestroyFont(font);
    eng::DestroyTexture(texture);

    logger.info("Main", "Program ended");

    for (int i(0) ; i < 10 ; ++i) {
        eng::UniqueIndex uuid;
        std::cout << "UUID : " << (uint64_t)uuid << std::endl;
    }
    

    return 0;
}