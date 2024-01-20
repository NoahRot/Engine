#include "Graphic/VertexArray.hpp"

namespace eng {

namespace _intern_ {
uint32_t GetStride(uint32_t type) {
    switch(type) {
        case GL_FLOAT:
            return sizeof(float);
        case GL_UNSIGNED_INT:
            return sizeof(unsigned int);
        case GL_INT:
            return sizeof(int);
        case GL_BYTE:
            return sizeof(char);
        case GL_UNSIGNED_BYTE:
            return sizeof(unsigned char);
        default:
            return 0;
    }
}

}



VertexAttributesLayout::VertexAttributesLayout() 
: m_stride(0u)
{}

void VertexAttributesLayout::AddAttribute(int32_t size, GLenum type, bool normalized) {
    // Get the stride of the type (0 if unvalid)
    uint32_t stride = eng::_intern_::GetStride(type);

    // Check if the type is valid
    if (stride == 0) {
        GetLogger().Error("VertexAttributesLayout", "Unvalid type of attribute");
        return;
    }

    // Check if the size is valide
    if (size >= 1 and size <= 4) {
        // Push the new attribute
        m_attributes.push_back(eng::_intern_::VertexAttributes{size, type, normalized, stride*size});
        m_stride += stride*size;
    }else{
        GetLogger().Error("VertexAttributesLayout", "Attribute size too big. size should be between 1 and 4. Current size : " + std::to_string(size));
    }
}

void VertexAttributesLayout::AddFloat(int32_t size, bool normalized) {
    AddAttribute(size, GL_FLOAT, normalized);
}

void VertexAttributesLayout::AddByte(int32_t size, bool normalized) {
    AddAttribute(size, GL_BYTE, normalized);
}

void VertexAttributesLayout::AddUnsignedInt(int32_t size, bool normalized) {
    AddAttribute(size, GL_UNSIGNED_INT, normalized);
}

uint32_t VertexAttributesLayout::Size() const {
    return m_attributes.size();
}

eng::_intern_::VertexAttributes VertexAttributesLayout::Get(uint32_t index) const {
    return m_attributes[index];
}

uint32_t VertexAttributesLayout::Stride() const {
    return m_stride;
}





VertexArray::VertexArray()
: m_index(0)
{
    glGenVertexArrays(1, &m_index);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_index);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_index);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::SetAttributes(const VertexBuffer& vbo, const VertexAttributesLayout& layout) const {
        // Define starting point
        uint32_t startPointer(0u);

        // Check if number of attributes is not too large
        if (GetMaxVertexAttributes() < (int)layout.Size()) {
            GetLogger().Error("VertexArray", "Number of attribute in the layout is too big. Number of attribute in the layout : " + std::to_string(GetMaxVertexAttributes())
            + ". Max number of attribute : " + std::to_string(layout.Size()) + ".");
            return;
        }

        // Binding
        Bind();
        vbo.Bind();

        // Set attributes
        for (uint32_t index(0) ; index < layout.Size() ; ++index) {
            eng::_intern_::VertexAttributes current_element = layout.Get(index);
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, current_element.size, current_element.type, current_element.normalized, layout.Stride(), (const void*)startPointer);

            startPointer += current_element.stride;
        }
    }

}