#include <iostream>

#include "Engine.hpp"

#include "Math/Math.hpp"

int main(int argc, char** args) {

    eng::Configuration config;
    config.log_displayTXT = false;
    config.log_displayTXTName = "../Engine.log";
    config.win_name = "Engine DEMO";

    eng::Configure(config);

    eng::log::Logger& logger = eng::GetLogger();

    logger.Info("Main", "Program started");

    eng::Window& window = eng::GetWindow();
    eng::Event& event = eng::GetEvent();
    eng::Keyboard& keyboard = eng::GetKeyboard();
    eng::Mouse& mouse = eng::GetMouse();
    eng::Timer& timer = eng::GetTimer();
    eng::Renderer& renderer = eng::GetRenderer();

    logger.Info("Main", "Delta time in ms : " + std::to_string(timer.GetDeltaTime()));

    logger.Info("OpenGL", "Version : " + eng::InfoVersion());
    logger.Info("OpenGL", "Renderer : " + eng::InfoRenderer());
    logger.Info("OpenGL", "Shading language : " + eng::InfoShadingLanguage());
    logger.Info("OpenGL", "Vendor : " + eng::InfoVendor());
    logger.Info("OpenGL", "Number of texture slots : " + std::to_string(eng::GetMaxTextureSlots()));
    logger.Info("OpenGL", "Maximum number of attributes of a vertex : " + std::to_string(eng::GetMaxVertexAttributes()));

    renderer.SetClearColor(0.1f, 0.25f, 0.5f);

    eng::Shader shader("../shader/triangle.vert", "../shader/triangle.frag");
    if (!shader.IsValid()) {
        logger.Error("Main", "Shader unvalid");
    }else{
        logger.Info("Main", "Shader compiled");
    }

    // ==========
    // Test OpenGL - Make a triangle
    // ==========
    struct Vertex {
        float x, y, z; // Position
        float r, g, b; // Color
    };
    std::vector<Vertex> vertices = {
        Vertex{-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f}, // Down left
        Vertex{0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f}, // Dewn right
        Vertex{0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f}, // Top right
        Vertex{-0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 1.0f} // Top Left
    };

    std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    eng::VertexArray vao;
    vao.Bind();
    eng::IndexBuffer ibo(&indices.front(), indices.size()*sizeof(uint32_t));
    eng::VertexBuffer vbo(&vertices.front(), vertices.size()*sizeof(Vertex));

    eng::VertexAttributesLayout layout;
    layout.AddFloat(3); // Position
    layout.AddFloat(3); // Colors

    vao.SetAttributes(vbo, layout);
    // ==========
    // ==========

    while(eng::IsRunning()) {
        renderer.Clear();

        event.Manage();

        if(keyboard.KeyDown(SDL_SCANCODE_ESCAPE)) {
            eng::Quit();
        }

        if(keyboard.KeyDown(SDL_SCANCODE_D)) {
            logger.Info("Main", "D DOWN");
        }
        if(keyboard.KeyUp(SDL_SCANCODE_U)) {
            logger.Info("Main", "U UP");
        }
        if(keyboard.KeyPress(SDL_SCANCODE_P)) {
            // ==========
            // Draw Triangle
            // ==========
            shader.Bind();
            vao.Bind();
            // glDrawArrays(GL_TRIANGLES, 0, vertices.size());
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            // ==========
            // ==========
        }

        if(mouse.MouseDown(eng::MouseButton::MouseLeft)) {
            int32_t x,y;
            mouse.MousePosition(x,y);
            logger.Info("Main", "Mouse position, x : " + std::to_string(x) + ", y : " + std::to_string(y));
        }

        window.Present();
        timer.Loop();
    }

    // ==========
    // Math
    // ==========

    math::Vec3f v1;
    math::Vec3f v2({1.0f, 4.0f, 2.0f});
    math::Vec3f v3({2.0f, 1.5f, 2.0f});
    math::Vec2f v4({2.2f, 3.3f});

    std::cout << v2*2.0f << "\n" << v2+v3 << "\n" << std::endl;

    std::cout << math::merge(math::merge(1.1f, v4), 4.4f) << std::endl;

    // ==========
    // ==========

    logger.Info("Main", "Program ended");

    return 0;
}