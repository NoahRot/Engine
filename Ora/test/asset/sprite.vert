#version 330 core

layout (location = 0) in vec2 aPos;      // Position (x, y)
layout (location = 1) in vec2 aTexCoord; // Texture UVs

uniform mat4 uProjection; // Orthographic projection matrix

out vec2 TexCoord; // Pass to fragment shader

void main() {
    TexCoord = aTexCoord; // Pass UV coordinates
    gl_Position = uProjection * vec4(aPos, 0.0, 1.0); // Transform position
}