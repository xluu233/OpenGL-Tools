//
// Created by xlu on 2023/10/11.
//

#include "QGL_Window.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>

QGL_Window::QGL_Window(QWindow *parent) : QWindow(parent) {
    setSurfaceType(QWindow::OpenGLSurface);
}

QGL_Window::~QGL_Window() {
    delete m_device;
}

void QGL_Window::initialize() {
    log("initialize");
}

void QGL_Window::render(QPainter *painter) {
    log("render");
    Q_UNUSED(painter);
}

void QGL_Window::render() {
    log("render2");
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size() * devicePixelRatio());
    m_device->setDevicePixelRatio(devicePixelRatio());

    QPainter painter(m_device);
    render(&painter);
}

void QGL_Window::renderLater() {
    log("renderLater");
    requestUpdate();
}

void QGL_Window::renderNow() {
    if (!isExposed())
        return;

    log("renderNow");

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}

bool QGL_Window::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::UpdateRequest:
            renderNow();
            return true;
        default:
            return QWindow::event(event);
    }
}

void QGL_Window::exposeEvent(QExposeEvent *event) {
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void QGL_Window::setAnimating(bool animating) {
    m_animating = animating;

    if (animating)
        renderLater();
}
