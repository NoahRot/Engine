#pragma once

#include <iostream>

#include <External/glad/glad.h>

namespace eng {

class Renderer {
public:
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    static Renderer& Instance();

    ~Renderer();

    void SetClearColor(float r, float g, float b, float a = 1.0f);

    void Clear();

private:
    Renderer();
};

}