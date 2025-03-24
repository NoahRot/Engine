#pragma once

#include <glad/glad.h>
#include "Graphic/VertexArray.hpp"
#include "Memory/Batching.hpp"
#include "Graphic/Shader.hpp"

namespace ora {

class Renderer {
public:
    Renderer()
    {
        glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void set_blend(bool blending) {
        if (blending) {
            glEnable(GL_BLEND);
        }else{
            glDisable(GL_BLEND);
        }
    }

    void set_clear_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) const {
        glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
    }

    void set_cull_face(bool cull_face) {
        if (cull_face) {
            glEnable(GL_CULL_FACE);
        }else{
            glDisable(GL_CULL_FACE);
        }
    }

    void set_depth_test(bool depth_test) {
        if (depth_test) {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
        }else{
            glDisable(GL_DEPTH_TEST);
        }
    }

    void clear() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void draw(std::shared_ptr<VertexArray> vao) {
        vao->bind();
        vao->bind_index();

        glDrawElements(GL_TRIANGLES, vao->get_index_buffer_size(), GL_UNSIGNED_INT, 0);

        vao->unbind();
    }

private:

};

}