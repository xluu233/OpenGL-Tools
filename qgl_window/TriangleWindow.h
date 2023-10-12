//
// Created by xlu on 2023/10/11.
//

#ifndef OPENGL_TOOLS_TRIANGLEWINDOW_H
#define OPENGL_TOOLS_TRIANGLEWINDOW_H

#include "QGL_Window.h"

#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>

class TriangleWindow : public QGL_Window
{
public:
    using QGL_Window::QGL_Window;

    explicit TriangleWindow(){};

    void initialize() override;
    void render() override;

    void log(const QString& str)
    {
        qDebug() << "[TriangleWindow]" << str;
    }

private:
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
};

#endif //OPENGL_TOOLS_TRIANGLEWINDOW_H
