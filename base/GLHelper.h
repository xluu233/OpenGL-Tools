//
// Created by xlu on 2023/10/17.
//

#ifndef OPENGL_TOOLS_GLHELPER_H
#define OPENGL_TOOLS_GLHELPER_H

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QImage>
#include <QOpenGLWidget>
#include <QOpenGLVertexArrayObject>
#include <vector>
#include <QKeyEvent>
#include <iostream>
#include <QObject>


#ifdef _DEBUG
#include <QOpenGLDebugLogger>
#endif

#define OPENGL_FUNCTIONS QOpenGLContext::currentContext()->functions()
#define OPENGL_EXTRA_FUNCTIONS QOpenGLContext::currentContext()->extraFunctions()

#define GLFuncName QOpenGLExtraFunctions

#endif //OPENGL_TOOLS_GLHELPER_H
