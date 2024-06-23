#include <iostream>

#include "Engine.hpp"

struct VertexFlat {
    float x, y, z;
    float r, g, b;
};

struct Batch {
    std::vector<eng::VertexText> vertex;
    std::vector<uint32_t> indice;
    eng::VertexAttributesLayout layout;
    eng::Shader shader;
    eng::VertexArray* vao;
    eng::VertexBuffer* vbo;
    eng::IndexBuffer* ibo;

    void add_object(const std::vector<eng::VertexText>& vert, std::vector<uint32_t> indi) {
        uint32_t offset(vertex.size()); 
        vertex.insert( vertex.end(), vert.begin(), vert.end() );

        for (auto& i : indi) {
            i += offset;
        }
        indice.insert( indice.end(), indi.begin(), indi.end() );
    }

    void draw(const eng::Camera2D& camera, eng::Font_* font) {
        eng::Renderer2D& renderer = eng::Renderer2D::instance();
        math::Mat4f vp = camera.get_view_projection();

        math::Mat4f txt_mvp = vp;
        shader->bind();
        shader->set_uniform_mat4f("u_MVP", txt_mvp);
        font->bind();
        renderer.draw_vao(*vao, *ibo, shader);
    }

    void clear() {
        if (vao) {
            delete vao;
        }
        if (vbo) {
            delete vbo;
        }
        if (ibo) {
            delete ibo;
        }

        vertex = {};
        indice = {};
    }

    void generate(uint32_t vertex_size) {
        if (vao) {
            delete vao;
        }
        if (vbo) {
            delete vbo;
        }
        if (ibo) {
            delete ibo;
        }

        vao = new eng::VertexArray;
        vao->Bind();
        ibo = new eng::IndexBuffer(&indice.front(), indice.size());
        vbo = new eng::VertexBuffer(&vertex.front(), vertex.size()*vertex_size);

        vao->SetAttributes(*vbo, layout);
    }
};

class Button {
public:
    bool is_clicked() {
        eng::Mouse& mouse = eng::Mouse::instance();
        int32_t x, y;
        mouse.mouse_position(x, y);

        return x > m_position[0] && x < m_position[0]+m_dimension[0] && y > m_position[1] && y < m_position[1]+m_dimension[1];
    }

private:
    math::Vec2i m_position;
    math::Vec2i m_dimension;

    eng::ColorFloat m_color;
};

class UI {
public:
    enum TestList{
        none
    };

public:
    UI(eng::Index font_id, eng::Index shader_id, eng::VertexAttributesLayout layout)
    : m_test(eng::test::TestManager::instance()), m_font(nullptr), m_white{1,1,1,1}
    {
        eng::AssetManager& asset_manager = eng::AssetManager::instance();
        eng::Window& window = eng::Window::instance();

        batch_text.layout = layout;
        batch_text.shader = asset_manager.get_shader(shader_id);

        m_font = asset_manager.get_font(font_id);

        math::Vec2i window_dimension({(int)window.get_width(), (int)window.get_height()});
        int window_boudary = 10;
        int count = 1;
        int font_size = m_font->get_size();

        eng::Text test1(font_id);
        test1.add_text("List of tests:", m_white);
        test1.set_position(math::Vec2i({window_boudary, window_dimension[1]-(window_boudary+font_size)*count}));
        test1.generate();
        count++;

        eng::Text test2(font_id);
        test2.add_text("Test 1", m_white);
        test2.set_position(math::Vec2i({window_boudary, window_dimension[1]-(window_boudary+font_size)*count}));
        test2.generate();
        count++;

        eng::Text test3(font_id);
        test3.add_text("Test 2", m_white);
        test3.set_position(math::Vec2i({window_boudary, window_dimension[1]-(window_boudary+font_size)*count}));
        test3.generate();
        count++;

        batch_text.add_object(test1.vertices(), test1.indices());
        batch_text.add_object(test2.vertices(), test2.indices());
        batch_text.add_object(test3.vertices(), test3.indices());
        batch_text.generate(sizeof(eng::VertexText));
    }

    ~UI() {
        batch_text.clear();
    }

    void draw(const eng::Camera2D& camera) {
        batch_text.draw(camera, m_font);
    }

    void update() {

    }

private:
    eng::test::TestManager& m_test;

    eng::Font_* m_font;
    
    eng::ColorFloat m_white;

    Batch batch_text;
};

int main(int argc, char** args) {

    // Configure engine
    eng::Configuration config;
    config.log_displayCMD = true;
    config.log_displayTXT = true;
    config.log_displayTXTName = "../Test_modules.log";
    config.tex_pixel_art = true;
    config.tim_fps = 60;
    config.win_height = 540;
    config.win_width = 960;
    config.win_name = "Test Modules";

    eng::configure(config);

    // Get the singletons classes of the engine
    eng::log::Logger& logger = eng::get_logger();

    logger.info("Main", "Program started");

    eng::Window&                window          = eng::get_window();
    eng::Event&                 event           = eng::get_event();
    eng::Keyboard&              keyboard        = eng::get_keyboard();
    eng::Mouse&                 mouse           = eng::get_mouse();
    eng::Timer&                 timer           = eng::get_timer();
    eng::Renderer2D&            renderer        = eng::get_renderer_2D();
    eng::AssetManager&          asset_manager   = eng::get_asset_manager();

    // Create 2D camera
    eng::Camera2D camera(0, config.win_width, 0, config.win_height);

    // Load font
    eng::Index font_id = asset_manager.load_font("../asset/font/OpenSans.ttf", 30);
    if (font_id == eng::UNVALID) {
        logger.error("Main", "Can't load font");
        exit(EXIT_FAILURE);
    }

    // Load Shader
    eng::Index txt_shader_id = asset_manager.load_shader("../shader/Text.vert", "../shader/Text.frag");
    if (txt_shader_id == eng::UNVALID) {
        logger.error("Main", "Can't load shader");
        exit(EXIT_FAILURE);
    }

    // Create Text layout
    eng::VertexAttributesLayout txt_layout;
    txt_layout.AddFloat(3); // Position
    txt_layout.AddFloat(2); // Texture coord
    txt_layout.AddFloat(3); // Color

    // Create UI
    UI ui(font_id, txt_shader_id, txt_layout);

    // Set clear color and transparency
    eng::ColorFloat clear_color{0.03f, 0.05f, 0.1f, 1.0f};
    renderer.set_clear_color(clear_color);
    renderer.set_blend(true);

    // Main loop
    while (eng::is_running())
    {
        // Clear
        renderer.clear();

        // Event
        event.manage();
        if (keyboard.key_down(SDL_SCANCODE_ESCAPE)) {
            eng::quit();
        }

        // Update

        // Draw
        ui.draw(camera);

        // Present & loop
        window.present();
        timer.loop();
    }
    
    logger.info("Main", "Program ended");

    return 0;
}