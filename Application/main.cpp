#include <iostream>

#include "Engine.hpp"

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
        float x;
        float y;
        float z;
    };
    std::vector<Vertex> vertices = {
        Vertex{-0.5f, -0.5f, 0.0f}, // Down left
        Vertex{0.5f, -0.5f, 0.0f}, // Dewn right
        Vertex{0.5f, 0.5f, 0.0f}, // Top right
        Vertex{-0.5f, 0.5f, 0.0f} // Top Left
    };

    std::vector<uint32_t> indices = {
        0, 1, 3,
        1, 2, 3
    };

    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    eng::VertexArray vao;
    vao.Bind();
    eng::IndexBuffer ibo(&indices.front(), indices.size()*sizeof(uint32_t));
    eng::VertexBuffer vbo(&vertices.front(), vertices.size()*sizeof(Vertex));

    //glBindVertexArray(VAO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t), &indices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
    // Clear OpenGL stuff
    // ==========
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &IBO);
    // ==========
    // ==========

    logger.Info("Main", "Program ended");

    return 0;
}