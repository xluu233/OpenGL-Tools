#version 330 core

in vec3 vPos;

in vec2 vTexture;   //输入纹理数据，为什么纹理坐标是vec2
out vec2 oTexture;  //输出变量oTexture

void main()
{
    gl_Position = vec4(vPos, 1.0);
    //这里没有对纹理做修改，直接传递给片段着色器
    oTexture = vTexture;
}
