//
// Created by xlu on 2023/10/11.
//

#ifndef OPENGL_TOOLS_SIMPLETRIANGLEWINDOW_H
#define OPENGL_TOOLS_SIMPLETRIANGLEWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class SimpleTriangleWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    SimpleTriangleWindow()
    {
    }

    ~SimpleTriangleWindow()
    {
    }

protected:

    void initializeGL()
    {
        initializeOpenGLFunctions();
        glEnable(GL_DEPTH_TEST);    //开启深度测试
        glClearColor(0.0,0.0,0.0,0.0);

        //创建vao.vbo
        m_vao.create();
        m_vbo.create();

        //shader加载
        initShader();

        float _vertex[] = {
                0.0,  0.5, 0.0,
                -0.5, -0.5, 0.0,
                0.5, -0.5, 0.0,
        };
        m_vao.bind();
        m_vbo.bind();
        m_vbo.allocate(_vertex,sizeof(_vertex));

        program.bind();
        program.setAttributeBuffer("vPos",GL_FLOAT,0,3,0);
        program.enableAttributeArray("vPos");

        program.release();
        m_vao.release();
    }

    void initShader()
    {
        // Compile vertex shader
        if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shader/vshader.glsl"))
            close();

        // Compile fragment shader
        if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resource/shader/fshader.glsl"))
            close();

        // Link shader pipeline
        if (!program.link())
            close();

        // Bind shader pipeline for use
        if (!program.bind())
            close();
    }

    void resizeGL(int w, int h)
    {

    };

    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_vao.bind();           //启用VAO
        program.bind();         //启用Shader
        glDrawArrays(GL_TRIANGLES,0,3);     //用三个点画一个三角形
        program.release();      //释放Shader
        m_vao.release();        //释放VAO
    };

private:
    //着色器程序
    QOpenGLShaderProgram program;

    QOpenGLVertexArrayObject    m_vao;
    QOpenGLBuffer               m_vbo;
};

#endif //OPENGL_TOOLS_SIMPLETRIANGLEWINDOW_H
