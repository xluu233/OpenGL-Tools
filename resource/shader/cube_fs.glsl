#version 330 core

in vec2 oTexture;   //从片段着色器中传递过来的纹理数据

uniform sampler2D uTexture;

void main()
{
    gl_FragColor = texture(uTexture, oTexture);
}
