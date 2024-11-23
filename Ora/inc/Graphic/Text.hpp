#pragma once

#include <string>
#include <vector>
#include <inttypes.h>

#include "Graphic/Font.hpp"

namespace ora {

struct VertexText {
    float x, y, z;
    float u, v;
    float r, g, b;
};

inline void create_text(const std::string& txt, Font& font, uint8_t r, uint8_t g, uint8_t b, std::vector<VertexText>& vertex, std::vector<uint32_t>& index) {
    vertex = std::vector<VertexText>(txt.size() * 4);
    index = std::vector<uint32_t>(txt.size() * 6);

    float current_x(0), current_y(0);
    float red(r/255.0f), green(g/255.0f), blue(b/255.0f);
    for (uint32_t i(0) ; i < txt.size() ; ++i) {
        if (txt[i] == '\n') {
            current_x = 0;
            current_y -= font.height;

        }else{
            const Character& c = font.character[txt[i]];

            float x_(current_x + c.left);
            float y_(current_y - c.bh + c.top);

            vertex[i*4 + 0] = VertexText{x_,         y_,        0, c.u,        c.v + c.h,  red, green, blue}; // Bottom left
            vertex[i*4 + 1] = VertexText{x_ + c.bw,  y_,        0, c.u + c.w,  c.v + c.h,  red, green, blue}; // Bottom right
            vertex[i*4 + 2] = VertexText{x_ + c.bw,  y_ + c.bh, 0, c.u + c.w,  c.v,        red, green, blue}; // Top right
            vertex[i*4 + 3] = VertexText{x_,         y_ + c.bh, 0, c.u,        c.v,        red, green, blue}; // Top left

            index[i*6 + 0] = i*4 + 0;
            index[i*6 + 1] = i*4 + 1;
            index[i*6 + 2] = i*4 + 2;

            index[i*6 + 3] = i*4 + 2;
            index[i*6 + 4] = i*4 + 3;
            index[i*6 + 5] = i*4 + 0;

            current_x += c.advance >> 6;
        }
    }
}

}