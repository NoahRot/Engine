#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coord;
layout (location = 2) in vec3 a_color;

out vec2 out_texture_coord;
out vec3 out_color;

uniform mat4 u_MVP;

void main()
{
    vec4 final_pos = vec4(a_position, 1.0f);
    gl_Position = u_MVP * final_pos;
    out_texture_coord = a_texture_coord;
    out_color = a_color;
}