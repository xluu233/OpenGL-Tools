#version 330 core

in vec3 vPos;
in vec2 vTexture;
in vec3 vNormal;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    FragPos = vec3(model * vec4(vPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * vNormal;
    TexCoords = vTexture;

    gl_Position = projection * view * model * vec4(vPos, 1.0);
}