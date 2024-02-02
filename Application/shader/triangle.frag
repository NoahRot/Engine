#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 textureCoord;

uniform sampler2D ourTexture;

void main()
{
    //FragColor = vertexColor;
    FragColor = texture(ourTexture, textureCoord) * vertexColor;
}