#version 330 core

in vec2 TexCoord;  // Received from vertex shader

out vec4 FragColor;

uniform sampler2D uTexture; // Texture atlas
uniform sampler2D uNormal; // Normal map

uniform vec3 uLightPos;

void main() {
    vec4 light_col = vec4(1.0, 1.0, 1.0, 1.0);

    vec3 normal = texture(uNormal, TexCoord).rgb * 2.0 - 1.0;
    vec3 lightDir = normalize(uLightPos - vec3(gl_FragCoord.xy, 0.0));

    float diffuse = max(dot(normal, lightDir), 0.1);

    vec4 texColor = texture(uTexture, TexCoord) * light_col;
    FragColor = texColor * vec4(vec3(diffuse), 1.0);

    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}