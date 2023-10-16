//
// Created by xlu on 2023/10/10.
//

#ifndef OPENGL_TOOLS_SIMPLEQGLWIDGET_H
#define OPENGL_TOOLS_SIMPLEQGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class SimpleQGLWidget : public QOpenGLWidget, QOpenGLFunctions{
    Q_OBJECT

public:
    explicit SimpleQGLWidget(QWidget* parent = nullptr) : QOpenGLWidget(parent)
    {
    }

    ~SimpleQGLWidget()
    {
        qDebug() << "SimpleQGLWidget deleted!";
    }

    void initializeGL() override
    {
        initializeOpenGLFunctions();
        glClearColor(0.2f, 0.1f, 0.8f, 0);
    };

    void resizeGL(int w, int h) override
    {
    };

    void paintGL() override
    {
    };

};


#endif //OPENGL_TOOLS_SIMPLEQGLWIDGET_H
