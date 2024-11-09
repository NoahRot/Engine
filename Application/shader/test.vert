#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTextureCoord;

uniform mat4 u_MVP;

out vec4 color;
out vec2 textureCoord;
out vec2 position;
void main()
{
   color = aCol;
   textureCoord = aTextureCoord;
   gl_Position = u_MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}