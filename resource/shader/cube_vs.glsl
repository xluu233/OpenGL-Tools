#version 330 core

in vec3 vPos;   //顶点数据
in vec2 vTexture;   //输入纹理数据
out vec2 oTexture;  //输出纹理数据

//uniform mat4 mvp_matrix; //可以这样代替mvp矩阵

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    //gl_Position = vec4(vPos, 1.0);
    gl_Position = projection * view * model * vec4(vPos, 1.0);
//    gl_Position = mvp_matrix * vec4(vPos, 1.0);
    oTexture = vTexture;
}
