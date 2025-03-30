#include "Graphic/Renderer.hpp"

namespace ora {

Renderer::Renderer() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Logger::instance().log(Info, "Renderer created");
}

Renderer::~Renderer() {
    Logger::instance().log(Info, "Renderer destroyed");
}

Renderer& Renderer::instance() {
    static Renderer s_instance;
    return s_instance;
}

void Renderer::set_blend(bool blending) {
    if (blending) {
        glEnable(GL_BLEND);
    }else{
        glDisable(GL_BLEND);
    }
}

void Renderer::set_clear_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}

void Renderer::set_cull_face(bool cull_face) {
    if (cull_face) {
        glEnable(GL_CULL_FACE);
    }else{
        glDisable(GL_CULL_FACE);
    }
}

void Renderer::set_depth_test(bool depth_test) {
    if (depth_test) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }else{
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

}