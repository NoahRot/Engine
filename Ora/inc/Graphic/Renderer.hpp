#pragma once

#include <glad/glad.h>
#include "Log/Logger.hpp"

namespace ora {

class Renderer {
public:
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    static Renderer& instance();

    void set_blend(bool blending);

    void set_clear_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    void set_cull_face(bool cull_face);

    void set_depth_test(bool depth_test);

    void clear();

private:
    Renderer();

};

}