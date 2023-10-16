//
// Created by xlu on 2023/10/16.
//

#ifndef OPENGL_TOOLS_QCUBEWINDOW_H
#define OPENGL_TOOLS_QCUBEWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QVector2D>
#include <QVector3D>
#include <QTimer>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

class QCubeWindow  : public QOpenGLWindow, protected QOpenGLFunctions{
    Q_OBJECT
private:

//    QOpenGLBuffer arrayBuf;     //vbo0
//    QOpenGLBuffer indexBuf;     //vbo1

    QOpenGLVertexArrayObject    m_vao;
    QOpenGLBuffer               m_vbo;

    QOpenGLShaderProgram *program = nullptr;
    QOpenGLTexture *texture = nullptr;

    //lookat矩阵
    QMatrix4x4 m_projection;
    QMatrix4x4 m_view;
    QMatrix4x4 m_model;


//    QVector2D mousePressPosition;
//    QVector3D rotationAxis;
//    qreal angularSpeed = 0;

    //四元数
//    QQuaternion rotation;

//    unsigned int width = 800;
//    unsigned int height = 600;


public:
    QCubeWindow() : m_vbo(QOpenGLBuffer::VertexBuffer),
                    m_vao(),
                    texture(nullptr),
                    program(nullptr),
                    m_model(),
                    m_view(),
                    m_projection()
    {
        qDebug() << "QCubeWindow init";
    }

    ~QCubeWindow()
    {
        qDebug() << "~ QCubeWindow deleted!";
        makeCurrent();
        delete program;
        delete texture;
        doneCurrent();
    }

//    void timerEvent(QTimerEvent *event) override
//    {
//        // Decrease angular speed (friction)
//        angularSpeed *= 0.99;
//
//        // Stop rotation when speed goes below threshold
//        if (angularSpeed < 0.01) {
//            angularSpeed = 0.0;
//        } else {
//            // Update rotation
//            rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
//            // Request an update
//            update();
//        }
//    }

    void initializeGL() override
    {
        initializeOpenGLFunctions();
        glEnable(GL_DEPTH_TEST);    //开启深度测试
        glClearColor(0.0,0.0,0.0,1.0);
//    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        makeCurrent();

        program = new QOpenGLShaderProgram(this);

        initShader();
//        initVertex();
        initVertex2();


        m_model.setToIdentity();
        m_view.setToIdentity();
        m_projection.setToIdentity();
//            float radius = 10.0f;
//            float camX = sin(glfwGetTime()) * radius;
//            float camZ = cos(glfwGetTime()) * radius;
//            m_view.lookAt(QVector3D(camX, 0.0, camZ), QVector3D(0, 0, 0), QVector3D(0, 1, 0));


        m_view.lookAt(QVector3D(3, 3, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
        m_projection.perspective(60, (float)3/2, 0.001, 1000);

    }

    void initShader() {
//        if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shader/cube_vs.glsl"))
//            close();
//
//        if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":resource/shader/cube_fs.glsl"))
//            close();

        if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/resource/shader/3_verture_vs.glsl"))
            close();
        if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resource/shader/3_verture_fs.glsl"))
            close();

        if (!program->link())
            close();

        if (!program->bind())
            close();
    }

    void initVertex() {
        VertexData vertices[] = {
                // Vertex data for face 0
                {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
                {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
                {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
                {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

                // Vertex data for face 1
                {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
                {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
                {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
                {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

                // Vertex data for face 2
                {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
                {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
                {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
                {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

                // Vertex data for face 3
                {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
                {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
                {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
                {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

                // Vertex data for face 4
                {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
                {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
                {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
                {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

                // Vertex data for face 5
                {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
                {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
                {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
                {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
        };

        GLushort indices[] = {
                0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
                4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
                8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
                12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
                16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
                20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
        };

//        arrayBuf.create();
//        indexBuf.create();
//
//        // Transfer vertex data to VBO 0
//        arrayBuf.bind();
//        arrayBuf.allocate(vertices, 24 * sizeof(VertexData));
//
//        // Transfer index data to VBO 1
//        indexBuf.bind();
//        indexBuf.allocate(indices, 34 * sizeof(GLushort));


        texture = new QOpenGLTexture(QImage(":/resource/image/cube.png"));
        texture->setMinificationFilter(QOpenGLTexture::Nearest);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);


//        quintptr offset = 0;
//        program->setAttributeBuffer("vPos", GL_FLOAT, offset, 3, sizeof(VertexData));
//        program->enableAttributeArray("vPos");
//
//        offset += sizeof(QVector3D);
//        program->setAttributeBuffer("vTexture", GL_FLOAT, offset, 2, sizeof(VertexData));
//        program->enableAttributeArray("vTexture");

//        arrayBuf.release();
//        indexBuf.release();


//        m_model.setToIdentity();
//        m_model.rotate(m_angle, 0, 1, 0);
//
//        m_view.setToIdentity();
//        m_view.lookAt(QVector3D(3, 3, 3), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
//
//        m_projection.setToIdentity();
//        m_projection.perspective(60, (float)800/600, 0.001, 1000);
    }

    void initVertex2() {
        // 顶点缓存中前三个是顶点坐标, 后两个是纹理坐标, 一个顶点由5个float值组成
        float _vertex[] = {
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

        //创建vao.vbo.ebo
        m_vbo.create();
        m_vao.create();

        m_vbo.bind();
        m_vao.bind();

        //将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
        m_vbo.allocate(_vertex,sizeof(_vertex));

//        program->bind();
//        program->setAttributeBuffer("vPos", GL_FLOAT, 0 * sizeof(float), 3, sizeof(VertexData));
//        program->enableAttributeArray("vPos");
//
//        program->setAttributeBuffer("vTexture", GL_FLOAT, 3 * sizeof(float), 2, sizeof(VertexData));
//        program->enableAttributeArray("vTexture");

        // 绑定顶点坐标信息, 从0 * sizeof(float)字节开始读取3个float, 因为一个顶点有5个float数据, 所以下一个数据需要偏移5 * sizeof(float)个字节
        program->setAttributeBuffer("vPos", GL_FLOAT, 0 * sizeof(float), 3, 5 * sizeof(float));
        program->enableAttributeArray("vPos");
        // 绑定纹理坐标信息, 从3 * sizeof(float)字节开始读取2个float, 因为一个顶点有5个float数据, 所以下一个数据需要偏移5 * sizeof(float)个字节
        program->setAttributeBuffer("vTexture", GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));
        program->enableAttributeArray("vTexture");

        texture = new QOpenGLTexture(QImage(":/resource/image/cube2.png"));
        texture->setMinificationFilter(QOpenGLTexture::Nearest);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);

        m_vbo.release();
//        m_vao.release();
    }


    void resizeGL(int w, int h) override
    {
        qDebug() << "resizeGL:" << w << " x " << h ;
//        width = w;
//        height = h;
//
//        // Calculate aspect ratio
//        qreal aspect = qreal(width) / qreal(height ? height : 1);
//        // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
//        const qreal zNear = 1.0, zFar = 1000.0, fov = 45.0;
//        // Reset projection
//        m_projection.setToIdentity();
//        // Set perspective projection
//        m_projection.perspective(fov, aspect, zNear, zFar);
    }

    void paintGL() override
    {
        program->bind();
        texture->bind();
        m_vao.bind();

        {
            // 绑定变换矩阵
//            program->setUniformValue("projection", m_projection);
//            program->setUniformValue("view", m_view);
//            program->setUniformValue("model", m_model);

            glDrawArrays(GL_TRIANGLE_FAN,0,4);     //绘制矩形
            // 绘制
//            for (int i = 0; i < 6; ++i)
//            {
//                glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
//            }
            //glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);
        }

        m_vao.release();
        texture->release();
        program->release();
    }


};


#endif //OPENGL_TOOLS_QCUBEWINDOW_H
