#include "Graphic/Renderer.hpp"

namespace eng {

Renderer2D::Renderer2D(){
    std::cout << "DEBUG : Renderer2D created" << std::endl;
}

Renderer2D::~Renderer2D() {
    std::cout << "DEBUG : Renderer2D destroyed" << std::endl;
}

Renderer2D& Renderer2D::instance() {
    static Renderer2D s_instance;
    return s_instance;
}

void Renderer2D::set_clear_color(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer2D::set_clear_color(const ColorBit& color) {
    glClearColor(color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f);
}

void Renderer2D::set_clear_color(const ColorFloat& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer2D::set_blend(bool is_blending) {
    if (is_blending) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }else{
        glDisable(GL_BLEND);
    }
}

void Renderer2D::set_cull_face(bool cull_face) {
    if (cull_face) {
        glEnable(GL_CULL_FACE);
    }else{
        glDisable(GL_CULL_FACE);
    }
}

void Renderer2D::set_depth_test(bool depth_test) {
    if (depth_test) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }else{
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer2D::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer2D::draw_vao(const VertexArray& vao, const IndexBuffer& ibo, Shader_* shader) {
    shader->bind();
    vao.Bind();
    ibo.Bind();
    glDrawElements(GL_TRIANGLES, ibo.Size(), GL_UNSIGNED_INT, 0);
}

}