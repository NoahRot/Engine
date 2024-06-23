#version 330 core

in vec2 out_texture_coord;
in vec3 out_color;

out vec4 color;

uniform sampler2D u_texture;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, out_texture_coord).r);
    color = vec4(out_color.rgb, 1.0) * sampled;
} 