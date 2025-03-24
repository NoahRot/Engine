#version 330 core

in vec2 TexCoord;  // Received from vertex shader

out vec4 FragColor;

uniform sampler2D uTexture; // Texture atlas

void main() {
    FragColor = texture(uTexture, TexCoord);

    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}