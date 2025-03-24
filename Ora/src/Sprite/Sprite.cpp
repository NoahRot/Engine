#include "Sprite/Sprite.hpp"

namespace ora {

// ==============================
// SpriteBatch
// ==============================

SpriteBatch::SpriteBatch(Texture* texture, Shader* shader, uint32_t reserve)
: m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr), m_texture(texture), m_normal(nullptr), m_shader(shader)
{
    // Create text layout
    m_sprite_layout.add_float(2); // Position
    m_sprite_layout.add_float(2); // Texture coordinates

    // Reserve space
    m_vertex.reserve(4 * reserve);
    m_index.reserve(6 * reserve);

    // Create vbo and ibo
    m_vbo = create_vbo<SpriteVertex>(4 * reserve, false);
    m_ibo = create_ibo(6 * reserve, false);
    m_vao = create_vao();

    m_vao->bind();
    m_vao->add_vertex_buffer(m_vbo, m_sprite_layout);
    m_vao->set_index_buffer(m_ibo);
    m_vao->unbind();
}

SpriteBatch::SpriteBatch(Texture* texture, Texture* normal, Shader* shader, uint32_t reserve)
: m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr), m_texture(texture), m_normal(normal), m_shader(shader)
{
    // Create text layout
    m_sprite_layout.add_float(2); // Position
    m_sprite_layout.add_float(2); // Texture coordinates

    // Reserve space
    m_vertex.reserve(4 * reserve);
    m_index.reserve(6 * reserve);

    // Create vbo and ibo
    m_vbo = create_vbo<SpriteVertex>(4 * reserve, false);
    m_ibo = create_ibo(6 * reserve, false);
    m_vao = create_vao();

    m_vao->bind();
    m_vao->add_vertex_buffer(m_vbo, m_sprite_layout);
    m_vao->set_index_buffer(m_ibo);
    m_vao->unbind();
}

void SpriteBatch::add_sprite(mat::Vec2f position, mat::Vec2f dimension, mat::Vec2f texture_coord, mat::Vec2f texture_dim) {
    uint32_t vert_index = m_vertex.size();

    m_vertex.push_back(SpriteVertex{position[0],                position[1],                texture_coord[0],                   texture_coord[1]                 });  // Bottom-left
    m_vertex.push_back(SpriteVertex{position[0] + dimension[0], position[1],                texture_coord[0] + texture_dim[0],  texture_coord[1]                 });  // Bottom-right
    m_vertex.push_back(SpriteVertex{position[0] + dimension[0], position[1] + dimension[1], texture_coord[0] + texture_dim[0],  texture_coord[1] + texture_dim[1]});  // Top-right
    m_vertex.push_back(SpriteVertex{position[0],                position[1] + dimension[1], texture_coord[0],                   texture_coord[1] + texture_dim[1]});  // Top-left

    m_index.push_back(vert_index + 0);
    m_index.push_back(vert_index + 1);
    m_index.push_back(vert_index + 2);

    m_index.push_back(vert_index + 2);
    m_index.push_back(vert_index + 3);
    m_index.push_back(vert_index + 0);
}

void SpriteBatch::reset() {
    m_vertex.clear();
    m_index.clear();
}

void SpriteBatch::flush() {
    m_vbo->bind();
    m_vbo->update(m_vertex.data(), m_vertex.size() * sizeof(SpriteVertex));

    m_ibo->bind();
    m_ibo->update(m_index.data(), m_index.size());
}

void SpriteBatch::draw(Shader* shader) {
    shader->use_shader();
    m_texture->bind(0);
    if (m_normal) {
        m_normal->bind(1);
    }
    m_vao->bind();
    m_vao->bind_index();

    glDrawElements(GL_TRIANGLES, m_vao->get_index_buffer_size(), GL_UNSIGNED_INT, 0);

    m_vao->unbind();
}

// ==============================
// Sprite
// ==============================

Sprite::Sprite(Texture* texture)
: m_texture(texture)
{}

void Sprite::add_to_batch(SpriteBatch* batch, mat::Vec2f position, mat::Vec2f dimension) {
    batch->add_sprite(position, dimension, mat::Vec2f{0.0f, 0.0f}, mat::Vec2f{1.0f, 1.0f});
}

// ==============================
// SpriteSheet
// ==============================

SpriteSheet::SpriteSheet(Texture* texture, uint32_t sprite_width, uint32_t sprite_height)
: m_texture(texture), m_sprite_width(sprite_width), m_sprite_height(sprite_height), 
m_texture_width(texture->get_width()), m_texture_height(texture->get_height())
{}

mat::Vec2f SpriteSheet::get_texture_coord(uint32_t column, uint32_t row) {
    return mat::Vec2f{(float)column*m_sprite_width/(float)m_texture_width, (float)row*m_sprite_height/(float)m_texture_height};
}

mat::Vec2f SpriteSheet::get_texture_coord(uint32_t index) {
    float column = index % nbr_column();
    float row = index / nbr_column();
    return mat::Vec2f{column*m_sprite_width/(float)m_texture_width, row*m_sprite_height/(float)m_texture_height};
}

mat::Vec2f SpriteSheet::get_texture_dim() {
    return mat::Vec2f{(float)m_sprite_width/(float)m_texture_width, (float)m_sprite_height/(float)m_texture_height};
}

void SpriteSheet::add_to_batch(SpriteBatch* batch, uint32_t column, uint32_t row, mat::Vec2f position, mat::Vec2f dimension) {
    batch->add_sprite(position, dimension, get_texture_coord(column, row), get_texture_dim());
}

uint32_t SpriteSheet::nbr_column() {
    return m_texture_height / m_sprite_height;
}

uint32_t SpriteSheet::nbr_row() {
    return m_texture_width / m_sprite_width;
}

uint32_t SpriteSheet::get_sprite_width() {
    return m_sprite_width;
}

uint32_t SpriteSheet::get_sprite_height() {
    return m_sprite_height;
}

// ==============================
// SpriteAnimation
// ==============================

SpriteAnimation::SpriteAnimation(SpriteSheet* sprite_sheet, uint32_t start_col, uint32_t start_row, uint32_t end_col, uint32_t end_row, uint32_t frame_time)
: m_sprite_sheet(sprite_sheet), m_id_start(start_row*sprite_sheet->nbr_column() + start_col), 
    m_id_end(end_row*sprite_sheet->nbr_column() + end_col), m_id_current(m_id_start),
    m_frame_time(frame_time), m_current_time(0)
{}

void SpriteAnimation::update(uint32_t dt) {
    m_current_time += dt;
    while(m_current_time > m_frame_time) {
        ++m_id_current;
        if (m_id_current > m_id_end) {
            m_id_current = m_id_start;
        }
        m_current_time -= m_frame_time;
    }
}

void SpriteAnimation::add_to_batch(SpriteBatch* batch, mat::Vec2f position, mat::Vec2f dimension) {
    batch->add_sprite(position, dimension, m_sprite_sheet->get_texture_coord(m_id_current), m_sprite_sheet->get_texture_dim());
} 

}