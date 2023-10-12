//
// Created by xlu on 2023/10/11.
//

#ifndef OPENGL_TOOLS_SomeTRIANGLEWINDOW_H
#define OPENGL_TOOLS_SomeTRIANGLEWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class SomeTriangleWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    SomeTriangleWindow() : m_ebo(QOpenGLBuffer::IndexBuffer),
                           m_vbo(QOpenGLBuffer::VertexBuffer)
    {

    }

    ~SomeTriangleWindow()
    {
    }

protected:

    void initializeGL()
    {
        initializeOpenGLFunctions();
        glEnable(GL_DEPTH_TEST);    //开启深度测试
        glClearColor(0.0,0.0,0.0,0.0);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //shader加载
        initShader();

        //顶点数据
        initVertex();

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

    void initVertex()
    {
        float vertices[] = {
                0.5f, 0.5f, 0.0f,   // 右上角
                0.5f, -0.5f, 0.0f,  // 右下角
                0.0f,0.0f,0.0f, //中心点
                -0.5f, 0.5f, 0.0f,   // 左上角
                -0.5f, -0.5f, 0.0f, // 左下角
        };

        unsigned int indices[] = {
                // 注意索引从0开始!
                // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
                // 这样可以由下标代表顶点组合成矩形
                0, 1, 2, // 第一个三角形
                2, 3, 4  // 第二个三角形
        };

        //颜色数据
        GLfloat colorData[] = {
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
        };

        //创建vao.vbo.ebo
        m_vao.create();
        m_vao.bind();

        m_vbo.create();
        m_vbo.bind();
        //将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
        m_vbo.allocate(vertices,sizeof(vertices));

        m_ebo.create();     //生成EBO对象
        m_ebo.bind();       //EBO绑定到索引缓冲对象
        m_ebo.allocate(indices,sizeof(indices));

        program.setAttributeBuffer("vPos",GL_FLOAT,0,3,sizeof(GLfloat)*3 );
        program.enableAttributeArray("vPos");


//        int m_colAttr = program.attributeLocation("Color");
//        glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorData);
//        glEnableVertexAttribArray(m_colAttr);

//        m_vbo.write(sizeof(vertices),colorData,sizeof(colorData));
//        program.setAttributeBuffer("Color",GL_FLOAT,0,3,sizeof(GLfloat)*3 );
//        program.enableAttributeArray("Color");

        //m_vbo.write(9*sizeof(GLfloat), colorData, 9*sizeof(GLfloat));

    }


    void resizeGL(int w, int h)
    {

    };

    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_vao.bind();           //启用VAO
        program.bind();         //启用Shader
        {
//            glDrawArrays(GL_TRIANGLES,0,3);     //使用以0开始，长度为3的顶点数据来绘制三角形
            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);   //绘制ebo对象
        }

        program.release();      //释放Shader
        m_vao.release();        //释放VAO
        m_vbo.release();
        m_ebo.release();
    };

private:
    //着色器程序
    QOpenGLShaderProgram program;

    QOpenGLVertexArrayObject    m_vao;
    QOpenGLBuffer               m_vbo;
    QOpenGLBuffer               m_ebo;
//    QOpenGLBuffer m_ebo(QOpenGLBuffer::IndexBuffer);
};

#endif
