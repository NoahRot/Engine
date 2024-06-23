#pragma once

#include "Asset/AssetManager.hpp"
#include "Core/CoreFnc.hpp"

#include "Tools/Test.hpp"

#include "Graphic/Camera.hpp"

namespace eng::test {

class TestGraphic2D : public Test {
public:
    struct Vertex {
        float x, y, z; // Position
        float r, g, b; // Color
        float u, v;    // Texture coord
    };

public:
    TestGraphic2D()
    : m_asset_manager(eng::get_asset_manager()), m_camera(0, get_window().get_width(), 0, get_window().get_height())
    {}

    void init(const std::string& path_texture, const std::string& path_vertex, const std::string& path_fragment) {
        // Load texture
        m_texture_id = m_asset_manager.load_texture(path_texture, true);
        if (m_texture_id == UNVALID) {
            get_logger().error("TestGraphic2D", "Can't load texture : " + path_texture);
            m_texture = nullptr;
        }else{
            m_texture = m_asset_manager.get_texture(m_texture_id);
        }

        // Load shader
        m_shader_id = m_asset_manager.load_shader(path_vertex, path_fragment);
        if (m_shader_id == UNVALID) {
            get_logger().error("TestGraphic2D", "Can't load shader : " + path_vertex + ", " + path_fragment);
            m_shader = nullptr;
        }else{
            m_shader = m_asset_manager.get_shader(m_shader_id);
        }

        // Load vertices and indices
        std::vector<eng::test::TestGraphic2D::Vertex> vertices = {
            Vertex{0.0f, 0.0f, 0.0f,        1.0f, 0.0f, 0.0f,   0.0f, 0.0f}, // Down left
            Vertex{100.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,   1.0f, 0.0f}, // Dewn right
            Vertex{100.0f, 100.0f, 0.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f}, // Top right
            Vertex{0.0f, 100.0f, 0.0f,      0.0f, 1.0f, 1.0f,   0.0f, 1.0f}  // Top Left
        };

        std::vector<uint32_t> indices = {
            0, 1, 3,
            1, 2, 3
        };

        eng::VertexArray vao;
        vao.Bind();
        eng::IndexBuffer ibo(&indices.front(), indices.size());
        eng::VertexBuffer vbo(&vertices.front(), vertices.size()*sizeof(Vertex));

        eng::VertexAttributesLayout layout;
        layout.AddFloat(3); // Position
        layout.AddFloat(3); // Colors
        layout.AddFloat(2); // Texture coord

        vao.SetAttributes(vbo, layout);
    }

    virtual void update() override {

    }

    virtual void draw() override {

    }

private:
    eng::AssetManager& m_asset_manager;

    eng::Camera2D m_camera;
    
    eng::Index m_texture_id;
    eng::Texture m_texture;

    eng::Index m_shader_id;
    eng::Shader m_shader;
};

}