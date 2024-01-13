#include "Graphic/Renderer.hpp"

namespace eng {

Renderer::Renderer(){
    std::cout << "DEBUG : Renderer created" << std::endl;
}

Renderer::~Renderer() {
    std::cout << "DEBUG : Renderer destroyed" << std::endl;
}

Renderer& Renderer::Instance() {
    static Renderer s_instance;
    return s_instance;
}

void Renderer::SetClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

}