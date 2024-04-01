#pragma once

#include <iostream>

#include <External/glad/glad.h>

#include "Graphic/VertexArray.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/Camera.hpp"

namespace eng {

class Shader_;
class VertexArray;
class IndexBuffer;

class Renderer2D {
public:
    Renderer2D(const Renderer2D&) = delete;
    Renderer2D& operator=(const Renderer2D&) = delete;

    static Renderer2D& instance();

    ~Renderer2D();

    void set_clear_color(float r, float g, float b, float a = 1.0f);

    void set_blend(bool is_blending);

    void clear();

    void draw_vao(const VertexArray& vao, const IndexBuffer& ibo, Shader_* shader);

private:
    Renderer2D();
};

}