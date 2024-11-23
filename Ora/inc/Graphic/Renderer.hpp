#pragma once

#include <glad/glad.h>
#include "Graphic/VertexArray.hpp"
#include "Memory/Batching.hpp"
#include "Graphic/Shader.hpp"

namespace ora {

class Renderer {
public:
    Renderer(ShaderManager* shader_manager)
    : m_shader_manager(shader_manager)
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

    void set_clear_color(float r, float g, float b, float a = 1.0f) const {
        glClearColor(r, g, b, a);
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

    void draw(const VertexArray& vao) {
        vao.bind();
        vao.bind_index();

        glDrawElements(GL_TRIANGLES, vao.get_index_buffer_size(), GL_UNSIGNED_INT, 0);

        vao.unbind();
    }

    template<typename T>
    void draw(const Batch<T>& batch) {
        m_shader_manager->use_shader(batch.get_shader());
        batch.get_vao().bind();
        batch.get_vao().bind_index();

        glDrawElements(GL_TRIANGLES, batch.get_vao().get_index_buffer_size(), GL_UNSIGNED_INT, 0);

        batch.get_vao().unbind();
    }

private:
    ShaderManager* m_shader_manager;
};

}