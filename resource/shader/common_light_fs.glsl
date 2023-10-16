#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform vec3 lightColor;
uniform sampler2D Texture;

void main()
{
    FragColor = vec4(texture(Texture, TexCoords).rgb * lightColor, 1.0);
}