#pragma once

namespace eng {

struct ColorBit {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct ColorFloat {
    float r;
    float g;
    float b;
    float a;
};

inline ColorBit color_float_to_bit(const ColorFloat& color) {
    return ColorBit{
        (unsigned char)(color.r * 255), 
        (unsigned char)(color.g * 255), 
        (unsigned char)(color.b * 255), 
        (unsigned char)(color.a * 255)
    };
}

inline ColorFloat color_bit_to_float(const ColorBit& color) {
    return ColorFloat{
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        color.a / 255.0f
    };
}

}