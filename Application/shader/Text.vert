#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
out vec2 TexCoords;

uniform mat4 u_MVP;

void main()
{
    vec4 final_pos = vec4(position, 0.0f, 1.0f);
    gl_Position = u_MVP*final_pos;
    TexCoords = texCoord;
}