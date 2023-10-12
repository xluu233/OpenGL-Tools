//
// Created by xlu on 2023/10/12.
//

#ifndef OPENGL_TOOLS_VERTEXCUBEWINDOW_HPP
#define OPENGL_TOOLS_VERTEXCUBEWINDOW_HPP

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>

class VertexCubeWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    VertexCubeWindow()
    {

    }

    ~VertexCubeWindow(){}


    void initializeGL() override
    {
        initializeOpenGLFunctions();
        glEnable(GL_DEPTH_TEST);    //开启深度测试
        glClearColor(0.0,0.0,0.0,0.0);

        //创建vao.vbo
        m_vao.create();
        m_vbo.create();

        //shader加载
        initShader();

        // 顶点缓存中前三个是顶点坐标, 后两个是纹理坐标, 一个顶点由5个float值组成
        GLfloat vertexs[] = {
                //顶点						纹理
                // 1
                -1,  1,  1,		0.50, 0.25,	// 左上
                -1, -1,  1,		0.50, 0.50,	// 左下
                1, -1,  1,		0.75, 0.50,	// 右下
                1,  1,  1,		0.75, 0.25,  // 右上
                // 6
                1,  1, -1,		0.00, 0.25,	// 左上
                1, -1, -1,		0.00, 0.50,	// 左下
                -1, -1, -1,		0.25, 0.50,	// 右下
                -1,  1, -1,		0.25, 0.25,	// 右上
                // 2
                1,	 1,  1,		0.75, 0.25,  // 左上
                1,	-1,  1,		0.75, 0.50,	// 左下
                1,	-1, -1,		1.00, 0.50,	// 右下
                1,	 1, -1,		1.00, 0.25,	// 右上
                // 5
                -1,  1, -1,		0.25, 0.25,	// 左上
                -1, -1, -1,		0.25, 0.50,	// 左下
                -1, -1,  1,		0.50, 0.50,	// 右下
                -1,  1,  1,		0.50, 0.25,	// 右上
                // 3
                -1,  1, -1,		0.00, 0.00,	// 左上
                -1,  1,  1,		0.00, 0.25,	// 左下
                1,  1,  1,		0.25, 0.25,  // 右下
                1,  1, -1,		0.25, 0.00,	// 右上
                // 4
                -1, -1,  1,		0.00, 0.50,  // 左上
                -1, -1, -1,		0.00, 0.75,	// 左下
                1, -1, -1,		0.25, 0.75,	// 右下
                1, -1,  1,		0.25, 0.50,	// 右上
        };

        m_vao.bind();
        m_vbo.bind();
        m_vbo.allocate(vertexs,sizeof(vertexs));

        m_view.setToIdentity();
        m_view.lookAt(QVector3D(3, 3, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

        m_model.setToIdentity();
        m_model.rotate(1.0f, 0, 1, 0);

        program.bind();
        program.setAttributeBuffer("vPos",GL_FLOAT,0,3,0);
        program.enableAttributeArray("vPos");

        program.release();
        m_vao.release();
    }


    void initShader()
    {
        // Compile vertex shader
        if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shader/vshader3.glsl"))
            close();

        // Compile fragment shader
        if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resource/shader/fshader3.glsl"))
            close();

        // Link shader pipeline
        if (!program.link())
            close();

        // Bind shader pipeline for use
        if (!program.bind())
            close();
    }


    void paintGL() override
    {

    }

    void resizeGL(int w, int h) override
    {
        m_projection.setToIdentity();
        m_projection.perspective(60, (float)w / h, 0.001, 1000);

        m_view.setToIdentity();
        m_view.lookAt(QVector3D(3, 3, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

        m_model.setToIdentity();
        m_model.rotate(0.1f, 0, 1, 0);

    }

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram program;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model;


};
#endif //OPENGL_TOOLS_VERTEXCUBEWINDOW_HPP
