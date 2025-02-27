#pragma once

#include <inttypes.h>

namespace eng {

struct Character {
    float u, v, w, h;       // Position and dimension on the texture atlas
    int32_t bw, bh;         // Width and height in pixel
    int32_t left, top;      // Bearing 
    int64_t advance;        // Advance to the next char
};

}