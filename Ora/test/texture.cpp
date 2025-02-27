#include "Orange.hpp"

#include "program.hpp"

class TestTexture : public TestProgram {
public:
    TestTexture()
    : TestProgram("Texture"), m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr)
    {
        m_texture_1 = m_engine->texture_manager.load_texture("../Application/asset/image/image.jpg", true);
        if (m_texture_1 == ora::UNVALID_32) {
            m_engine->logger.log(ora::LogLevel::Fatal, "Can not load the texture");
            exit(EXIT_FAILURE);
        }

        m_shader_texture = m_engine->shader_manager.load_shader("../Application/shader/test.vert", "../Application/shader/test.frag");
        if (m_shader_texture == ora::UNVALID_32) {
            m_engine->logger.log(ora::LogLevel::Fatal, "Can not load the shader");
            exit(EXIT_FAILURE);
        }

        const ora::Texture& texture_1 = m_engine->texture_manager.get_texture(m_texture_1);
        float width = texture_1.width, height = texture_1.height;

        std::vector<float> vertex = {
            0.0f, 0.0f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
            width, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f, 
            width, height, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f,     1.0f, 1.0f, 
            0.0f, height, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f,     0.0f, 1.0f
        };

        std::vector<uint32_t> index = {
            0, 1, 2, 
            2, 3, 0
        };

        m_vbo = std::make_shared<ora::VertexBuffer>(&vertex.front(), sizeof(float)*vertex.size());
        m_ibo = std::make_shared<ora::IndexBuffer>(index);
        ora::VertexAttribLayout layout;
        layout.add_float(3);
        layout.add_float(4);
        layout.add_float(2);

        m_vao = std::make_shared<ora::VertexArray>();
        m_vao->bind();
        m_vao->add_vertex_buffer(&(*m_vbo), layout);
        m_vao->set_index_buffer(&(*m_ibo));

        m_mvp = mat::orthographic3<float>(0.0f, m_engine->window.get_width(), 0.0f, m_engine->window.get_height(), 1.0f, -1.0f);
        m_disp = mat::translate3<float>(mat::Vec3f{100.0f, 100.0f, 0.0f});

        if (m_vao != nullptr && m_vbo != nullptr && m_ibo != nullptr) {
            m_engine->logger.log(ora::LogLevel::Info, "Buffer completed");
        }else{
            m_engine->logger.log(ora::LogLevel::Error, "Buffer not completed");
        }
    }

    virtual void event() override {
        
    }

    virtual void draw() override {
        m_engine->shader_manager.use_shader(m_shader_texture);
        m_engine->shader_manager.set_unif_mat4f(m_shader_texture, "u_MVP", m_mvp);
        m_engine->texture_manager.bind_texture(m_texture_1, 0);
        m_vao->bind();
        m_vao->bind_index();

        glDrawElements(GL_TRIANGLES, m_vao->get_index_buffer_size(), GL_UNSIGNED_INT, 0);

        m_vao->unbind();
    }

private:
    uint32_t m_texture_1;
    uint32_t m_shader_texture;
    std::shared_ptr<ora::VertexArray> m_vao;
    std::shared_ptr<ora::VertexBuffer> m_vbo;
    std::shared_ptr<ora::IndexBuffer> m_ibo;
    mat::Mat4f m_mvp;
    mat::Mat4f m_disp;
};

int main(int argc, char* argv[]) {

    TestTexture test;

    // Enable blend
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    test.run();

    return 0;
}