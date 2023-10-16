//
// Created by xlu on 2023/10/15.
//

#ifndef OPENGL_TOOLS_QVERTURE_H
#define OPENGL_TOOLS_QVERTURE_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class QVerture  : public QOpenGLWindow, protected QOpenGLFunctions{
    Q_OBJECT
public:
    QVerture() : m_vbo(QOpenGLBuffer::VertexBuffer),
                 m_vao(),
                 m_program(nullptr),
                 m_context(nullptr),
                 m_texture(nullptr)
    {
    }

    ~QVerture()
    {
        makeCurrent();
        delete m_texture;
        delete m_program;
        delete m_context;
        doneCurrent();
    };

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    //着色器程序
    QOpenGLShaderProgram        *m_program;
    QOpenGLContext              *m_context;

    QOpenGLVertexArrayObject    m_vao;
    QOpenGLBuffer               m_vbo;
    QOpenGLTexture              *m_texture;

    void initShader();

    void initVertex();
};


#endif //OPENGL_TOOLS_QVERTURE_H
