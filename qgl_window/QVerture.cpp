//
// Created by xlu on 2023/10/15.
//
#include "QVerture.h"

void QVerture::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);    //开启深度测试
    glClearColor(0.0,0.0,0.0,0.0);
//    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    makeCurrent();

    m_program = new QOpenGLShaderProgram(this);
    //shader加载
    initShader();

    //顶点数据
    initVertex();

}

void QVerture::initShader() {
    // Compile vertex shader
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shader/3_verture_vs.glsl"))
        close();

    // Compile fragment shader
    if (!m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resource/shader/3_verture_fs.glsl"))
        close();

    // Link shader pipeline
    if (!m_program->link())
        close();

    // Bind shader pipeline for use
    if (!m_program->bind())
        close();
}

void QVerture::initVertex() {

    // 顶点缓存中前三个是顶点坐标, 后两个是纹理坐标, 一个顶点由5个float值组成
    float _vertex[] = {
            //  顶点			纹理
            -1,  1, 0,	0, 1, // 左上
            -1, -1, 0,	0, 0, // 左下
            1, -1, 0,	1, 0, // 右下
            1,  1, 0,	1, 1, // 右上
    };

    //创建vao.vbo.ebo
    m_vao.create();
    m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    //将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
    m_vbo.allocate(_vertex,sizeof(_vertex));

    // 绑定顶点坐标信息, 从0 * sizeof(float)字节开始读取3个float, 因为一个顶点有5个float数据, 所以下一个数据需要偏移5 * sizeof(float)个字节
    m_program->setAttributeBuffer("vPos", GL_FLOAT, 0 * sizeof(float), 3, 5 * sizeof(float));
    m_program->enableAttributeArray("vPos");
    // 绑定纹理坐标信息, 从3 * sizeof(float)字节开始读取2个float, 因为一个顶点有5个float数据, 所以下一个数据需要偏移5 * sizeof(float)个字节
    m_program->setAttributeBuffer("vTexture", GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));
    m_program->enableAttributeArray("vTexture");

    m_texture = new QOpenGLTexture(QImage(":/resource/image/cachemem.png").mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);

    m_vbo.release();
}


void QVerture::resizeGL(int w, int h) {

}

void QVerture::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_vao.bind();                 //启用VAO
    m_program->bind();           //启用Shader
    m_texture->bind();          //激活纹理0,就是片段着色器中的uniform sampler2D uTexture;
    {
        glDrawArrays(GL_TRIANGLE_FAN,0,4);     //绘制矩形
    }
    m_program->release();        //释放Shader
    m_vao.release();            //释放VAO
    m_texture->release();        //释放纹理
}
