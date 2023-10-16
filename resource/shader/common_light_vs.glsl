#version 330 core

in vec3 vPos;
in vec2 vTexture;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = vTexture;

    gl_Position = projection * view * model * vec4(vPos, 1.0);
}