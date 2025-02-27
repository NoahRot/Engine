#pragma once

#include <vector>
#include <typeindex>
#include <typeinfo>
#include <iostream>

#include <External/glad/glad.h>

#include "Core/CoreFnc.hpp"
#include "Graphic/VertexBuffer.hpp"

namespace eng {

namespace _intern_ {

/// @brief A structure that represent an attribute
struct VertexAttributes {
    /// @brief The size of the attribute (1,2,3 or 4)
    int32_t size;

    /// @brief The type of variable
    uint32_t type;

    /// @brief If the parameters should be normalized
    bool normalized;

    /// @brief Stride of the attribute in bytes
    uint32_t stride;
};

/// @brief Get the number of bytes for a type
/// @param type The OpenGL type
/// @return The number of bytes of this type
uint32_t GetStride(uint32_t type);

}

/// @brief A class that represent the attributes of the vertices of a vertex buffer
class VertexAttributesLayout {
public:
    /// @brief Constructor
    VertexAttributesLayout();

    /// @brief Add an attribute to the layout
    /// @param size The number of element in the attribute (1, 2, 3 or 4)
    /// @param type The OpenGL type of the variables in this attribute
    /// @param normalized If the parameters has to be normalized
    void AddAttribute(int32_t size, GLenum type, bool normalized = false);

    /// @brief Add a float attribute to the layout
    /// @param size The number of element in the attribute (1, 2, 3 or 4)
    /// @param normalized If the parameters has to be normalized
    void AddFloat(int32_t size, bool normalized = false);

    /// @brief Add a byte attribute to the layout
    /// @param size The number of element in the attribute (1, 2, 3 or 4)
    /// @param normalized If the parameters has to be normalized
    void AddByte(int32_t size, bool normalized = false);

    /// @brief Add an unsigned int attribute to the layout
    /// @param size The number of element in the attribute (1, 2, 3 or 4)
    /// @param normalized If the parameters has to be normalized
    void AddUnsignedInt(int32_t size, bool normalized = false);

    /// @brief Return the number of attributes in the layout
    /// @return The number of attributes in the layout
    uint32_t Size() const;

    /// @brief Get an attribute from the layout
    /// @param index The index of the attribute
    /// @return The attribute
    eng::_intern_::VertexAttributes Get(uint32_t index) const;

    /// @brief Return the stride of the layout (all the attributes are taken in account)
    /// @return The stride (in bytes) of the layout
    uint32_t Stride() const;

private:
    /// @brief The list of attributes
    std::vector<eng::_intern_::VertexAttributes> m_attributes;

    /// @brief The stride of the layout (all attributes are taken in account)
    uint32_t m_stride;
};

/// @brief A class that retresent the vertex array
class VertexArray {
public:
    /// @brief Constructor
    VertexArray();

    /// @brief Destructor
    ~VertexArray();

    /// @brief Bind the vertex array
    void Bind() const;

    /// @brief Unbind the vertex array
    void Unbind() const;

    /// @brief Set the attribute of the vertex buffer
    /// @param vbo The vertex buffer
    /// @param layout The layout that contain the attributes
    void SetAttributes(const VertexBuffer& vbo, const VertexAttributesLayout& layout) const;

private:
    /// @brief The OpenGL index of the vertex array
    uint32_t m_index;
};

}