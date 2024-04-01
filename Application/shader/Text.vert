#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 color; // The color

out vec2 TexCoords;
out vec3 texColor;

uniform mat4 u_MVP;

void main()
{
    vec4 final_pos = vec4(position, 1.0f);
    gl_Position = u_MVP*final_pos;
    TexCoords = texCoord;
    texColor = color;
}