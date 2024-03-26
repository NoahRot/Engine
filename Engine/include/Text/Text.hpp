#pragma once

#include <string>

#include "Text/Character.hpp"
#include "Text/Font.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"

namespace eng {

class Text {
public:
    Text();
    ~Text();

    void Generate(Font font, const std::string& text);

    std::string GetString() { return m_text; }

    float GetRatio() { return m_width/m_height; }

    float GetWidth() { return m_width; }
    float GetHeight() { return m_height; }

    VertexArray& GetVAO() { return *m_vao; }
    VertexBuffer& GetVBO() { return *m_vbo; }
    IndexBuffer& GetIBO() { return *m_ibo; }

private:
    std::string m_text;
    float m_width;
    float m_height;

    VertexArray* m_vao;
    VertexBuffer* m_vbo;
    IndexBuffer* m_ibo;
};

}