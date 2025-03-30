#pragma once

#include "mat/Math.hpp"
#include "Graphic/Texture.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/Camera2D.hpp"

namespace ora {

struct SpriteVertex {
    float x, y;
    float u, v;
};

class SpriteBatch {
public:
    SpriteBatch(Texture* texture, Shader* shader, uint32_t reserve);

    SpriteBatch(Texture* texture, Texture* normal, Shader* shader, uint32_t reserve);

    void add_sprite(mat::Vec2f position, mat::Vec2f dimension, mat::Vec2f texture_coord, mat::Vec2f texture_dim);

    void reset();

    void flush();

    void draw(Shader* shader);

private:
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;

    VertexAttribLayout m_sprite_layout;

    Texture* m_texture;
    Texture* m_normal;
    Shader* m_shader;

    std::vector<SpriteVertex> m_vertex;
    std::vector<uint32_t> m_index;
};

class Sprite {
public:
    Sprite(Texture* texture);

    void add_to_batch(SpriteBatch* batch, mat::Vec2f position, mat::Vec2f dimension);

private:
    Texture* m_texture;
};

/* --- Sprite sheet ID --- 
 8  9 10 11
 4  5  6  7
 0  1  2  3
*/

class SpriteSheet {
public:
    SpriteSheet(Texture* texture, uint32_t sprite_width, uint32_t sprite_height);

    mat::Vec2f get_texture_coord(uint32_t column, uint32_t row);

    mat::Vec2f get_texture_coord(uint32_t index);

    mat::Vec2f get_texture_dim();

    void add_to_batch(SpriteBatch* batch, uint32_t column, uint32_t row, mat::Vec2f position, mat::Vec2f dimension);

    uint32_t nbr_column();

    uint32_t nbr_row();

    uint32_t get_sprite_width();

    uint32_t get_sprite_height();

private:
    Texture* m_texture;
    uint32_t m_sprite_width, m_sprite_height;
    uint32_t m_texture_width, m_texture_height;
};

class SpriteAnimation {
public:
    SpriteAnimation(SpriteSheet* sprite_sheet, uint32_t start_col, uint32_t start_row, uint32_t end_col, uint32_t end_row, uint32_t frame_time);

    void update(uint32_t dt);

    void add_to_batch(SpriteBatch* batch, mat::Vec2f position, mat::Vec2f dimension);

private:
    SpriteSheet* m_sprite_sheet;
    uint32_t m_id_start, m_id_end, m_id_current;
    uint32_t m_frame_time, m_current_time;
};



}