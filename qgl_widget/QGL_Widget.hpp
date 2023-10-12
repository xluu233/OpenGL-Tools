//
// Created by xlu on 2023/10/10.
//

#ifndef OPENGL_TOOLS_QGL_WIDGET_HPP
#define OPENGL_TOOLS_QGL_WIDGET_HPP

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class QGL_Widget : public QOpenGLWidget, QOpenGLFunctions{
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;

    explicit QGL_Widget(QWidget* parent = nullptr) : QOpenGLWidget(parent)
    {
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


#endif //OPENGL_TOOLS_QGL_WIDGET_HPP
